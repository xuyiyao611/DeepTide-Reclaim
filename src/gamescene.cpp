#include "gamescene.h"

#include "projectpaths.h"

#include <QApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QKeyEvent>
#include <QLoggingCategory>
#include <QPainter>
#include <QPainterPath>
#include <QStandardPaths>
#include <QTimer>
#include <QtMath>
#include <cmath>

Q_LOGGING_CATEGORY(startupLog, "deep_tide.startup")
Q_LOGGING_CATEGORY(resourceLog, "deep_tide.resource")
Q_LOGGING_CATEGORY(inputLog, "deep_tide.input")
Q_LOGGING_CATEGORY(collisionLog, "deep_tide.collision")
Q_LOGGING_CATEGORY(oxygenLog, "deep_tide.oxygen")
Q_LOGGING_CATEGORY(collectLog, "deep_tide.collect")
Q_LOGGING_CATEGORY(settlementLog, "deep_tide.settlement")
Q_LOGGING_CATEGORY(upgradeLog, "deep_tide.upgrade")
Q_LOGGING_CATEGORY(saveLog, "deep_tide.save")

namespace {

constexpr int kTargetFrameMs = 16;
constexpr int kHudPadding = 18;
constexpr float kInputDiagonalFactor = 0.70710678f;
constexpr float kWaterDragFactor = 7.5f;
constexpr float kSpawnXFactor = 0.5f;
constexpr float kSpawnYFactor = 0.42f;
constexpr float kPlayAreaMargin = 36.0f;
constexpr float kTopAreaOffset = 104.0f;
constexpr float kBottomAreaOffset = 82.0f;
constexpr float kBaseOxygenCostPerSecond = 4.2f;
constexpr float kDepthOxygenCostPerSecond = 3.4f;
constexpr float kMoveOxygenCostPerSecond = 0.9f;
constexpr float kMaxDepthMeters = 1200.0f;
constexpr float kCollectRangePadding = 16.0f;
constexpr float kReturnZoneWidthFactor = 0.24f;
constexpr float kReturnZoneHeight = 54.0f;
constexpr float kReturnZoneTopInset = 14.0f;
constexpr int kGlowClusterSellValue = 12;
constexpr float kPlayerBaseHealth = 100.0f;
constexpr float kHitInvulnerabilitySeconds = 0.85f;
constexpr float kHitFlashSeconds = 0.28f;
constexpr float kControlLockSeconds = 0.20f;
constexpr qint64 kStatusMessageDurationMs = 4200;
constexpr int kSaveFormatVersion = 1;

struct CodexEntryDefinition {
    ResourceItem::Type type;
    QString name;
    QString category;
    QString description;
    QString discoveryHint;
    QColor accent;
};

QString resourceTypeKey(const ResourceItem::Type type)
{
    switch (type) {
    case ResourceItem::Type::GlowCluster:
        return QStringLiteral("glow_cluster");
    case ResourceItem::Type::ShellCrystal:
        return QStringLiteral("shell_crystal");
    case ResourceItem::Type::ColdGel:
        return QStringLiteral("cold_gel");
    case ResourceItem::Type::OldPart:
        return QStringLiteral("old_part");
    }

    return QStringLiteral("unknown");
}

ResourceItem::Type resourceTypeFromKey(const QString &key)
{
    if (key == QStringLiteral("shell_crystal")) {
        return ResourceItem::Type::ShellCrystal;
    }
    if (key == QStringLiteral("cold_gel")) {
        return ResourceItem::Type::ColdGel;
    }
    if (key == QStringLiteral("old_part")) {
        return ResourceItem::Type::OldPart;
    }
    return ResourceItem::Type::GlowCluster;
}

QString regionKey(const GameScene::SeaRegionId id)
{
    switch (id) {
    case GameScene::SeaRegionId::CoastalShelf:
        return QStringLiteral("coastal_shelf");
    case GameScene::SeaRegionId::ThermalFault:
        return QStringLiteral("thermal_fault");
    }

    return QStringLiteral("coastal_shelf");
}

GameScene::SeaRegionId regionFromKey(const QString &key)
{
    if (key == QStringLiteral("thermal_fault")) {
        return GameScene::SeaRegionId::ThermalFault;
    }
    return GameScene::SeaRegionId::CoastalShelf;
}

QVector<CodexEntryDefinition> codexEntries()
{
    return {
        {ResourceItem::Type::GlowCluster,
         QStringLiteral("荧团浮体"),
         QStringLiteral("基础可售资源"),
         QStringLiteral("近岸海域最稳定的基础回收物，适合前期刷取积分并试探返航节奏。"),
         QStringLiteral("在近岸浅层回收带靠近上层区域即可首次接触。"),
         QColor(120, 236, 255)},
        {ResourceItem::Type::ShellCrystal,
         QStringLiteral("壳晶石"),
         QStringLiteral("升级材料"),
         QStringLiteral("常用于推进器和回收机械臂的结构强化，是前期最重要的基础材料。"),
         QStringLiteral("近岸海域中层会出现，需要停留采集。"),
         QColor(144, 227, 160)},
        {ResourceItem::Type::ColdGel,
         QStringLiteral("冷凝胶"),
         QStringLiteral("升级材料"),
         QStringLiteral("用于氧气系统和耐压壳体的冷却稳定部件，在热泉区域产量更高。"),
         QStringLiteral("近岸深层与热泉断层采样区都可能发现。"),
         QColor(146, 176, 255)},
        {ResourceItem::Type::OldPart,
         QStringLiteral("旧时代零件"),
         QStringLiteral("关键材料"),
         QStringLiteral("中期海域的重要目标资源，同时也是热泉断层采样区的解锁关键条件。"),
         QStringLiteral("深入近岸最底部或进入热泉断层采样区寻找大型采样点。"),
         QColor(255, 188, 112)},
    };
}

QString keyToName(const int key)
{
    switch (key) {
    case Qt::Key_W:
        return QStringLiteral("W");
    case Qt::Key_A:
        return QStringLiteral("A");
    case Qt::Key_S:
        return QStringLiteral("S");
    case Qt::Key_D:
        return QStringLiteral("D");
    case Qt::Key_Up:
        return QStringLiteral("上");
    case Qt::Key_Down:
        return QStringLiteral("下");
    case Qt::Key_Left:
        return QStringLiteral("左");
    case Qt::Key_Right:
        return QStringLiteral("右");
    case Qt::Key_Space:
        return QStringLiteral("空格");
    case Qt::Key_Escape:
        return QStringLiteral("Esc");
    case Qt::Key_F1:
        return QStringLiteral("F1");
    case Qt::Key_F5:
        return QStringLiteral("F5");
    case Qt::Key_F9:
        return QStringLiteral("F9");
    case Qt::Key_R:
        return QStringLiteral("R");
    case Qt::Key_E:
        return QStringLiteral("E");
    case Qt::Key_M:
        return QStringLiteral("M");
    case Qt::Key_Tab:
        return QStringLiteral("Tab");
    case Qt::Key_Return:
    case Qt::Key_Enter:
        return QStringLiteral("回车");
    default:
        return QStringLiteral("按键(%1)").arg(key);
    }
}

bool isDirectionalKey(const int key)
{
    return key == Qt::Key_W || key == Qt::Key_A || key == Qt::Key_S || key == Qt::Key_D ||
           key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_Left || key == Qt::Key_Right;
}

QVector<ResourceItem::Type> allResourceTypes()
{
    return {
        ResourceItem::Type::GlowCluster,
        ResourceItem::Type::ShellCrystal,
        ResourceItem::Type::ColdGel,
        ResourceItem::Type::OldPart,
    };
}

GameScene::UpgradeType upgradeTypeForKey(const int key)
{
    switch (key) {
    case Qt::Key_1:
        return GameScene::UpgradeType::OxygenTank;
    case Qt::Key_2:
        return GameScene::UpgradeType::Thruster;
    case Qt::Key_3:
        return GameScene::UpgradeType::CargoBay;
    case Qt::Key_4:
        return GameScene::UpgradeType::RecoveryArm;
    case Qt::Key_5:
        return GameScene::UpgradeType::PressureHull;
    default:
        return GameScene::UpgradeType::OxygenTank;
    }
}

bool isUpgradeHotkey(const int key)
{
    return key >= Qt::Key_1 && key <= Qt::Key_5;
}

QString resourceName(ResourceItem::Type type)
{
    return ResourceItem(type, ResourceItem::CollectMode::Instant, QPointF(), 0.0f, 0.0f, 0).displayName();
}

}  // namespace

GameScene::GameScene(QWidget *parent)
    : QWidget(parent),
      m_timer(new QTimer(this))
{
    setFocusPolicy(Qt::StrongFocus);
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAutoFillBackground(false);

    m_assetLayoutReady = ProjectPaths::ensureAssetLayout(&m_assetStatusText);

    qCInfo(startupLog) << "[startup] projectRoot =" << ProjectPaths::resolveProjectRoot();
    qCInfo(resourceLog) << "[resource]" << m_assetStatusText;
    qCInfo(resourceLog) << "[resource] images =" << ProjectPaths::imagesRoot();
    qCInfo(resourceLog) << "[resource] sounds =" << ProjectPaths::soundsRoot();
    qCInfo(resourceLog) << "[resource] maps =" << ProjectPaths::mapsRoot();

    connect(m_timer, &QTimer::timeout, this, &GameScene::tick);
    m_timer->start(kTargetFrameMs);
    m_elapsedTimer.start();

    loadPersistentState(false);
    applyPersistentUpgrades();
    updateRegionUnlocks();
    ensurePlayerSpawned();
    resetResources();
    resetHazards();

    qCInfo(startupLog) << "[startup] GameScene ready. Timer interval =" << kTargetFrameMs << "ms";
}

void GameScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawBackground(painter);
    drawSeaFloor(painter);
    drawReturnZone(painter);
    drawObstacles(painter);
    drawHazards(painter);
    drawResources(painter);
    drawPlayer(painter);
    if (m_showCollisionDebug) {
        drawCollisionDebug(painter);
    }
    drawHud(painter);
    if (m_isSettling) {
        drawSettlementOverlay(painter);
    }
    if (m_showCodexOverlay) {
        drawCodexOverlay(painter);
    }
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        event->accept();
        return;
    }

    if (event->key() == Qt::Key_F1) {
        m_showCollisionDebug = !m_showCollisionDebug;
        qCInfo(collisionLog) << "[collision] debug overlay =" << m_showCollisionDebug;
        update();
        event->accept();
        return;
    }

    if (event->key() == Qt::Key_Tab) {
        m_showCodexOverlay = !m_showCodexOverlay;
        setStatusMessage(m_showCodexOverlay
                             ? QStringLiteral("图鉴终端已打开。游戏暂停，按 Tab 关闭。")
                             : QStringLiteral("图鉴终端已关闭。"));
        update();
        event->accept();
        return;
    }

    if (event->key() == Qt::Key_M) {
        m_soundEnabled = !m_soundEnabled;
        savePersistentState(false);
        setStatusMessage(m_soundEnabled
                             ? QStringLiteral("基础音效反馈已开启。")
                             : QStringLiteral("基础音效反馈已关闭。"));
        if (m_soundEnabled) {
            playFeedbackBeep();
        }
        update();
        event->accept();
        return;
    }

    if (event->key() == Qt::Key_F5) {
        if (savePersistentState(true)) {
            setStatusMessage(QStringLiteral("演示存档已保存。"));
            playFeedbackBeep();
        } else {
            setStatusMessage(QStringLiteral("演示存档保存失败，请检查磁盘写入权限。"));
        }
        update();
        event->accept();
        return;
    }

    if (event->key() == Qt::Key_F9) {
        if (loadPersistentState(true)) {
            m_showCodexOverlay = false;
            resetRunState();
            savePersistentState(false);
            setStatusMessage(QStringLiteral("演示存档已载入，当前进度已切换。"));
            playFeedbackBeep();
        } else {
            setStatusMessage(QStringLiteral("未找到演示存档，请先按 F5 保存一份。"));
        }
        update();
        event->accept();
        return;
    }

    if (m_showCodexOverlay) {
        if (event->key() == Qt::Key_Escape) {
            m_showCodexOverlay = false;
            setStatusMessage(QStringLiteral("图鉴终端已关闭。"));
            update();
        }
        event->accept();
        return;
    }

    if (m_isSettling) {
        if (event->key() == Qt::Key_Left || event->key() == Qt::Key_A) {
            const QVector<SeaRegionDefinition> definitions = regionDefinitions();
            int currentIndex = 0;
            for (int i = 0; i < definitions.size(); ++i) {
                if (definitions.at(i).id == m_selectedRegion) {
                    currentIndex = i;
                    break;
                }
            }
            const int nextIndex = (currentIndex - 1 + definitions.size()) % definitions.size();
            m_selectedRegion = definitions.at(nextIndex).id;
            m_upgradeFeedbackText = regionStatusText(m_selectedRegion);
        } else if (event->key() == Qt::Key_Right || event->key() == Qt::Key_D) {
            const QVector<SeaRegionDefinition> definitions = regionDefinitions();
            int currentIndex = 0;
            for (int i = 0; i < definitions.size(); ++i) {
                if (definitions.at(i).id == m_selectedRegion) {
                    currentIndex = i;
                    break;
                }
            }
            const int nextIndex = (currentIndex + 1) % definitions.size();
            m_selectedRegion = definitions.at(nextIndex).id;
            m_upgradeFeedbackText = regionStatusText(m_selectedRegion);
        } else if (isUpgradeHotkey(event->key())) {
            tryPurchaseUpgrade(upgradeTypeForKey(event->key()));
        } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ||
                   event->key() == Qt::Key_Space || event->key() == Qt::Key_E) {
            tryLaunchSelectedRegion();
        }
        event->accept();
        update();
        return;
    }

    if (event->key() == Qt::Key_R && m_isRunFailed) {
        resetRunState();
        qCInfo(oxygenLog) << "[oxygen] run reset after oxygen failure.";
        event->accept();
        return;
    }

    m_pressedKeys.insert(event->key());
    logInputState("pressed", event->key());

    QWidget::keyPressEvent(event);
    update();
}

void GameScene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
        event->accept();
        return;
    }

    m_pressedKeys.remove(event->key());
    logInputState("released", event->key());

    QWidget::keyReleaseEvent(event);
    update();
}

void GameScene::tick()
{
    const qint64 nowMs = m_elapsedTimer.elapsed();
    const qint64 deltaMs = qMax<qint64>(0, nowMs - m_lastTickMs);
    m_lastDtSeconds = qBound(0.0f, static_cast<float>(deltaMs) / 1000.0f, 0.05f);
    m_totalElapsedMs = nowMs;
    m_lastTickMs = nowMs;

    if (!m_statusText.isEmpty() && m_statusTextExpiresMs > 0 && nowMs >= m_statusTextExpiresMs) {
        m_statusText.clear();
        m_statusTextExpiresMs = 0;
    }

    ensurePlayerSpawned();
    updateDamageState(m_lastDtSeconds);
    processInput(m_lastDtSeconds);
    updatePlayer(m_lastDtSeconds);
    updateOxygen(m_lastDtSeconds);
    updateCollection(m_lastDtSeconds);
    updateRunMetrics(deltaMs);
    updateReturnSequence();
    updateHazards(m_lastDtSeconds);

    update();
}

void GameScene::ensurePlayerSpawned()
{
    if (width() <= 0 || height() <= 0) {
        return;
    }

    if (!m_hasSpawnedPlayer) {
        const QRectF area = playAreaRect();
        m_player.setPosition(QPointF(area.left() + area.width() * kSpawnXFactor,
                                     area.top() + area.height() * kSpawnYFactor));
        m_player.setRadius(28.0f);
        m_player.setMoveSpeed(currentMoveSpeedValue());
        m_player.setMaxOxygen(static_cast<float>(currentMaxOxygenValue()));
        m_player.setOxygen(m_player.maxOxygen());
        m_hasSpawnedPlayer = true;
    }
}

void GameScene::resetRunState()
{
    applyPersistentUpgrades();
    m_pressedKeys.clear();
    m_isRunFailed = false;
    m_isSettling = false;
    m_showCodexOverlay = false;
    m_collectingResourceIndex = -1;
    m_lastSettlement = {};
    m_currentCollectProgress = 0.0f;
    m_lastOxygenCostPerSecond = 0.0f;
    m_runElapsedMs = 0;
    m_runMaxDepthMeters = 0.0f;
    m_upgradeFeedbackText.clear();
    m_lastDamageReason.clear();
    m_playerHealth = m_playerMaxHealth;
    m_damageFlashSeconds = 0.0f;
    m_invulnerabilitySeconds = 0.0f;
    m_controlLockSeconds = 0.0f;
    m_player.setVelocity(QPointF());
    m_player.setOxygen(m_player.maxOxygen());
    m_inventory.reset();
    m_hasSpawnedPlayer = false;
    ensurePlayerSpawned();
    resetResources();
    resetHazards();
}

void GameScene::applyPersistentUpgrades()
{
    m_inventory.setCargoLimit(currentCargoLimitValue());
    m_player.setMoveSpeed(currentMoveSpeedValue());
    m_player.setMaxOxygen(static_cast<float>(currentMaxOxygenValue()));
    m_playerMaxHealth = kPlayerBaseHealth;
    if (m_playerHealth <= 0.0f || m_playerHealth > m_playerMaxHealth) {
        m_playerHealth = m_playerMaxHealth;
    }
    if (!m_isRunFailed) {
        m_player.setOxygen(m_player.maxOxygen());
    }
}

void GameScene::processInput(const float dt)
{
    Q_UNUSED(dt);

    if (m_isRunFailed || m_isSettling || m_showCodexOverlay) {
        m_player.setVelocity(QPointF());
        return;
    }

    if (m_controlLockSeconds > 0.0f) {
        return;
    }

    float xAxis = 0.0f;
    float yAxis = 0.0f;

    if (m_pressedKeys.contains(Qt::Key_A) || m_pressedKeys.contains(Qt::Key_Left)) {
        xAxis -= 1.0f;
    }
    if (m_pressedKeys.contains(Qt::Key_D) || m_pressedKeys.contains(Qt::Key_Right)) {
        xAxis += 1.0f;
    }
    if (m_pressedKeys.contains(Qt::Key_W) || m_pressedKeys.contains(Qt::Key_Up)) {
        yAxis -= 1.0f;
    }
    if (m_pressedKeys.contains(Qt::Key_S) || m_pressedKeys.contains(Qt::Key_Down)) {
        yAxis += 1.0f;
    }

    if (!qFuzzyIsNull(xAxis) && !qFuzzyIsNull(yAxis)) {
        xAxis *= kInputDiagonalFactor;
        yAxis *= kInputDiagonalFactor;
    }

    QPointF velocity = m_player.velocity();
    const float targetSpeed = m_player.moveSpeed();

    if (!qFuzzyIsNull(xAxis) || !qFuzzyIsNull(yAxis)) {
        velocity = QPointF(xAxis * targetSpeed, yAxis * targetSpeed);

        if (qAbs(xAxis) > qAbs(yAxis)) {
            m_player.setFacing(xAxis < 0.0f ? Player::Facing::Left : Player::Facing::Right);
        } else {
            m_player.setFacing(yAxis < 0.0f ? Player::Facing::Up : Player::Facing::Down);
        }
    } else {
        const float damping = qMax(0.0f, 1.0f - kWaterDragFactor * dt);
        velocity *= damping;
        if (qAbs(velocity.x()) < 2.0f) {
            velocity.setX(0.0f);
        }
        if (qAbs(velocity.y()) < 2.0f) {
            velocity.setY(0.0f);
        }
    }

    m_player.setVelocity(velocity);
}

void GameScene::updatePlayer(const float dt)
{
    if (dt <= 0.0f || m_isRunFailed || m_isSettling || m_showCodexOverlay) {
        return;
    }

    const QRectF area = playAreaRect();
    const QVector<QRectF> obstacles = obstacleRects();
    QRectF bounds = m_player.bounds();
    QPointF velocity = m_player.velocity();

    const qreal dx = velocity.x() * dt;
    if (!qFuzzyIsNull(dx)) {
        bounds.translate(dx, 0.0);

        if (bounds.left() < area.left()) {
            bounds.moveLeft(area.left());
            velocity.setX(0.0);
        } else if (bounds.right() > area.right()) {
            bounds.moveRight(area.right());
            velocity.setX(0.0);
        }

        for (const QRectF &obstacle : obstacles) {
            if (!bounds.intersects(obstacle)) {
                continue;
            }
            if (dx > 0.0) {
                bounds.moveRight(obstacle.left());
            } else {
                bounds.moveLeft(obstacle.right());
            }
            velocity.setX(0.0);
        }
    }

    const qreal dy = velocity.y() * dt;
    if (!qFuzzyIsNull(dy)) {
        bounds.translate(0.0, dy);

        if (bounds.top() < area.top()) {
            bounds.moveTop(area.top());
            velocity.setY(0.0);
        } else if (bounds.bottom() > area.bottom()) {
            bounds.moveBottom(area.bottom());
            velocity.setY(0.0);
        }

        for (const QRectF &obstacle : obstacles) {
            if (!bounds.intersects(obstacle)) {
                continue;
            }
            if (dy > 0.0) {
                bounds.moveBottom(obstacle.top());
            } else {
                bounds.moveTop(obstacle.bottom());
            }
            velocity.setY(0.0);
        }
    }

    m_player.setVelocity(velocity);
    m_player.setPosition(bounds.center());
}

void GameScene::updateOxygen(const float dt)
{
    if (dt <= 0.0f || !m_hasSpawnedPlayer || m_isRunFailed || m_isSettling || m_showCodexOverlay) {
        return;
    }

    const float depthRatio = currentDepthRatio();
    const float moveCost = m_player.isMoving() ? kMoveOxygenCostPerSecond : 0.0f;
    m_lastOxygenCostPerSecond = (kBaseOxygenCostPerSecond +
                                 depthRatio * kDepthOxygenCostPerSecond +
                                 moveCost) * currentOxygenEfficiencyMultiplier();

    m_player.setOxygen(m_player.oxygen() - m_lastOxygenCostPerSecond * dt);

    if (m_player.oxygenState() == Player::OxygenState::Empty) {
        m_isRunFailed = true;
        m_player.setVelocity(QPointF());
        m_lastDamageReason = QStringLiteral("氧气耗尽");
        qCWarning(oxygenLog).noquote()
            << QStringLiteral("[oxygen] depleted at depth=%1m after %2ms")
                   .arg(currentDepthMeters(), 0, 'f', 1)
                   .arg(m_totalElapsedMs);
    }
}

void GameScene::resetResources()
{
    const QRectF area = playAreaRect();
    if (m_currentRegion == SeaRegionId::ThermalFault) {
        m_resources = {
            ResourceItem(ResourceItem::Type::GlowCluster, ResourceItem::CollectMode::Instant,
                         QPointF(area.left() + area.width() * 0.22, area.top() + area.height() * 0.16), 14.0f, 0.0f, 1),
            ResourceItem(ResourceItem::Type::GlowCluster, ResourceItem::CollectMode::Instant,
                         QPointF(area.left() + area.width() * 0.60, area.top() + area.height() * 0.20), 14.0f, 0.0f, 1),
            ResourceItem(ResourceItem::Type::GlowCluster, ResourceItem::CollectMode::Instant,
                         QPointF(area.left() + area.width() * 0.80, area.top() + area.height() * 0.32), 14.0f, 0.0f, 1),
            ResourceItem(ResourceItem::Type::ColdGel, ResourceItem::CollectMode::Hold,
                         QPointF(area.left() + area.width() * 0.38, area.top() + area.height() * 0.52), 17.0f, 1.4f, 2),
            ResourceItem(ResourceItem::Type::ColdGel, ResourceItem::CollectMode::Hold,
                         QPointF(area.left() + area.width() * 0.70, area.top() + area.height() * 0.68), 17.0f, 1.5f, 2),
            ResourceItem(ResourceItem::Type::OldPart, ResourceItem::CollectMode::Hold,
                         QPointF(area.left() + area.width() * 0.52, area.top() + area.height() * 0.78), 19.0f, 1.8f, 3),
            ResourceItem(ResourceItem::Type::OldPart, ResourceItem::CollectMode::Hold,
                         QPointF(area.left() + area.width() * 0.86, area.top() + area.height() * 0.84), 19.0f, 2.2f, 3),
        };
        return;
    }

    m_resources = {
        ResourceItem(ResourceItem::Type::GlowCluster, ResourceItem::CollectMode::Instant,
                     QPointF(area.left() + area.width() * 0.18, area.top() + area.height() * 0.18), 14.0f, 0.0f, 1),
        ResourceItem(ResourceItem::Type::GlowCluster, ResourceItem::CollectMode::Instant,
                     QPointF(area.left() + area.width() * 0.53, area.top() + area.height() * 0.14), 14.0f, 0.0f, 1),
        ResourceItem(ResourceItem::Type::ShellCrystal, ResourceItem::CollectMode::Hold,
                     QPointF(area.left() + area.width() * 0.32, area.top() + area.height() * 0.48), 16.0f, 1.2f, 2),
        ResourceItem(ResourceItem::Type::ColdGel, ResourceItem::CollectMode::Hold,
                     QPointF(area.left() + area.width() * 0.72, area.top() + area.height() * 0.54), 17.0f, 1.6f, 2),
        ResourceItem(ResourceItem::Type::OldPart, ResourceItem::CollectMode::Hold,
                     QPointF(area.left() + area.width() * 0.83, area.top() + area.height() * 0.82), 18.0f, 2.1f, 3),
    };
}

void GameScene::resetHazards()
{
    const QRectF area = playAreaRect();
    m_hazardCreatures.clear();
    m_hazardZones.clear();

    HazardCreature ray;
    ray.name = QStringLiteral("电弧鳐");
    ray.radius = 26.0f;
    ray.patrolRange = 120.0f;
    ray.detectRange = 220.0f;
    ray.speed = 155.0f;
    ray.attackRange = 42.0f;

    if (m_currentRegion == SeaRegionId::ThermalFault) {
        HazardCreature rayA = ray;
        rayA.anchor = QPointF(area.left() + area.width() * 0.30, area.top() + area.height() * 0.34);
        rayA.position = rayA.anchor;
        m_hazardCreatures.push_back(rayA);

        HazardCreature rayB = ray;
        rayB.anchor = QPointF(area.left() + area.width() * 0.72, area.top() + area.height() * 0.58);
        rayB.position = rayB.anchor;
        rayB.patrolRange = 140.0f;
        rayB.detectRange = 250.0f;
        rayB.speed = 170.0f;
        m_hazardCreatures.push_back(rayB);

        HazardZone ventA;
        ventA.name = QStringLiteral("热泉喷口");
        ventA.rect = QRectF(area.left() + area.width() * 0.18,
                            area.top() + area.height() * 0.62,
                            120.0,
                            150.0);
        ventA.oxygenDrainPerSecond = 7.0f;
        ventA.damagePerSecond = 12.0f;
        ventA.pushStrength = 140.0f;
        m_hazardZones.push_back(ventA);

        HazardZone ventB;
        ventB.name = QStringLiteral("热泉喷口");
        ventB.rect = QRectF(area.left() + area.width() * 0.66,
                            area.top() + area.height() * 0.42,
                            135.0,
                            155.0);
        ventB.oxygenDrainPerSecond = 7.8f;
        ventB.damagePerSecond = 13.5f;
        ventB.pushStrength = 155.0f;
        m_hazardZones.push_back(ventB);
        return;
    }

    ray.anchor = QPointF(area.left() + area.width() * 0.60, area.top() + area.height() * 0.36);
    ray.position = ray.anchor;
    m_hazardCreatures.push_back(ray);

    HazardZone vent;
    vent.name = QStringLiteral("热泉喷口");
    vent.rect = QRectF(area.left() + area.width() * 0.70,
                       area.top() + area.height() * 0.60,
                       110.0,
                       140.0);
    vent.oxygenDrainPerSecond = 6.5f;
    vent.damagePerSecond = 11.0f;
    vent.pushStrength = 130.0f;
    m_hazardZones.push_back(vent);
}

void GameScene::updateRunMetrics(const qint64 deltaMs)
{
    if (!m_hasSpawnedPlayer || m_isRunFailed || m_isSettling || m_showCodexOverlay || deltaMs <= 0) {
        return;
    }

    m_runElapsedMs += deltaMs;
    m_runMaxDepthMeters = qMax(m_runMaxDepthMeters, currentDepthMeters());
}

void GameScene::updateDamageState(const float dt)
{
    if (dt <= 0.0f) {
        return;
    }

    m_damageFlashSeconds = qMax(0.0f, m_damageFlashSeconds - dt);
    m_invulnerabilitySeconds = qMax(0.0f, m_invulnerabilitySeconds - dt);
    m_controlLockSeconds = qMax(0.0f, m_controlLockSeconds - dt);
}

void GameScene::updateHazards(const float dt)
{
    if (dt <= 0.0f || !m_hasSpawnedPlayer || m_isRunFailed || m_isSettling || m_showCodexOverlay) {
        return;
    }

    updateHazardCreatures(dt);
    updateHazardZones(dt);
}

void GameScene::updateHazardCreatures(const float dt)
{
    const QPointF playerPos = m_player.position();

    for (HazardCreature &creature : m_hazardCreatures) {
        if (creature.cooldownMs > 0) {
            creature.cooldownMs = qMax<qint64>(0, creature.cooldownMs - static_cast<qint64>(dt * 1000.0f));
            creature.state = creature.cooldownMs > 0 ? HazardCreature::State::Cooldown : HazardCreature::State::Patrol;
        }

        const QPointF toPlayer = playerPos - creature.position;
        const float distance = std::hypot(toPlayer.x(), toPlayer.y());

        QPointF velocity;
        if (creature.cooldownMs <= 0 && distance <= creature.detectRange) {
            creature.state = HazardCreature::State::Alert;
            if (distance > 1.0f) {
                velocity = QPointF(toPlayer.x() / distance * creature.speed,
                                   toPlayer.y() / distance * creature.speed);
            }
        } else if (creature.cooldownMs <= 0) {
            creature.state = HazardCreature::State::Patrol;
            const float targetX = creature.anchor.x() + (creature.patrolForward ? creature.patrolRange : -creature.patrolRange);
            const float deltaX = targetX - creature.position.x();
            if (qAbs(deltaX) < 8.0f) {
                creature.patrolForward = !creature.patrolForward;
            }
            velocity = QPointF(creature.patrolForward ? creature.speed * 0.55f : -creature.speed * 0.55f,
                               qSin((m_totalElapsedMs + static_cast<qint64>(creature.anchor.x())) / 260.0) * 18.0);
        }

        creature.velocity = velocity;
        creature.position += velocity * dt;

        if (creature.position.x() < playAreaRect().left() + creature.radius) {
            creature.position.setX(playAreaRect().left() + creature.radius);
            creature.patrolForward = true;
        } else if (creature.position.x() > playAreaRect().right() - creature.radius) {
            creature.position.setX(playAreaRect().right() - creature.radius);
            creature.patrolForward = false;
        }

        const float hitDistance = std::hypot(playerPos.x() - creature.position.x(),
                                             playerPos.y() - creature.position.y());
        if (creature.cooldownMs <= 0 &&
            hitDistance <= creature.attackRange + m_player.radius()) {
            applyDamage(18.0f,
                        6.0f,
                        playerPos - creature.position,
                        160.0f,
                        QStringLiteral("被电弧鳐电击"));
            creature.cooldownMs = 1200;
            creature.state = HazardCreature::State::Cooldown;
        }
    }
}

void GameScene::updateHazardZones(const float dt)
{
    for (const HazardZone &zone : m_hazardZones) {
        if (!zone.rect.intersects(m_player.bounds())) {
            continue;
        }

        m_player.setOxygen(m_player.oxygen() - zone.oxygenDrainPerSecond * dt);
        applyDamage(zone.damagePerSecond * dt,
                    0.0f,
                    QPointF(0.0, -1.0),
                    zone.pushStrength * dt,
                    QStringLiteral("被热泉喷口灼伤"));
    }
}

void GameScene::updateReturnSequence()
{
    if (!m_hasSpawnedPlayer || m_isRunFailed || m_isSettling || m_showCodexOverlay) {
        return;
    }

    if (m_player.bounds().intersects(returnZoneRect())) {
        settleCurrentRun();
    }
}

void GameScene::updateCollection(const float dt)
{
    if (isRunLocked()) {
        m_collectingResourceIndex = -1;
        m_currentCollectProgress = 0.0f;
        return;
    }

    const int resourceIndex = currentCollectableIndex();
    const bool interactHeld = m_pressedKeys.contains(Qt::Key_E);
    const bool isMoving = m_player.isMoving();

    if (resourceIndex < 0) {
        m_collectingResourceIndex = -1;
        m_currentCollectProgress = 0.0f;
        return;
    }

    const ResourceItem &resource = m_resources.at(resourceIndex);
    if (!m_inventory.canStore(resource)) {
        m_collectingResourceIndex = -1;
        m_currentCollectProgress = 0.0f;
        return;
    }

    if (!interactHeld) {
        if (resource.collectMode() == ResourceItem::CollectMode::Hold) {
            m_collectingResourceIndex = -1;
            m_currentCollectProgress = 0.0f;
        }
        return;
    }

    if (resource.collectMode() == ResourceItem::CollectMode::Instant) {
        finishCollection(resourceIndex);
        return;
    }

    if (isMoving) {
        m_collectingResourceIndex = -1;
        m_currentCollectProgress = 0.0f;
        return;
    }

    if (m_collectingResourceIndex != resourceIndex) {
        m_collectingResourceIndex = resourceIndex;
        m_currentCollectProgress = 0.0f;
    }

    m_currentCollectProgress += dt;
    if (m_currentCollectProgress >= resource.collectDurationSeconds() * currentCollectionDurationMultiplier()) {
        finishCollection(resourceIndex);
    }
}

int GameScene::currentCollectableIndex() const
{
    const QRectF expandedPlayerBounds = m_player.bounds().adjusted(-kCollectRangePadding,
                                                                   -kCollectRangePadding,
                                                                   kCollectRangePadding,
                                                                   kCollectRangePadding);

    for (int index = 0; index < m_resources.size(); ++index) {
        if (expandedPlayerBounds.intersects(m_resources.at(index).bounds())) {
            return index;
        }
    }

    return -1;
}

void GameScene::finishCollection(const int resourceIndex)
{
    if (resourceIndex < 0 || resourceIndex >= m_resources.size()) {
        return;
    }

    const ResourceItem resource = m_resources.at(resourceIndex);
    if (!m_inventory.add(resource)) {
        qCInfo(collectLog) << "[collect] cargo full, cannot collect" << resource.displayName();
        m_collectingResourceIndex = -1;
        m_currentCollectProgress = 0.0f;
        return;
    }

    qCInfo(collectLog) << "[collect] collected" << resource.displayName()
                       << "| cargo =" << m_inventory.cargoUsed() << "/" << m_inventory.cargoLimit();

    m_discoveredResourceTypes.insert(static_cast<int>(resource.type()));
    m_lifetimeCollectedCounts[static_cast<int>(resource.type())] += 1;
    savePersistentState(false);
    playFeedbackBeep();
    setStatusMessage(QStringLiteral("已采集 %1，图鉴数据已更新。").arg(resource.displayName()));

    m_resources.removeAt(resourceIndex);
    m_collectingResourceIndex = -1;
    m_currentCollectProgress = 0.0f;
}

void GameScene::settleCurrentRun()
{
    SettlementReport report;
    report.totalCollected = m_inventory.totalItemCount();
    report.deepestDepthMeters = m_runMaxDepthMeters;
    report.tripDurationMs = m_runElapsedMs;
    const bool thermalUnlockedBefore = isRegionUnlocked(SeaRegionId::ThermalFault);

    QStringList soldParts;
    QStringList retainedParts;

    for (const ResourceItem::Type type : allResourceTypes()) {
        const int count = m_inventory.count(type);
        if (count <= 0) {
            continue;
        }

        m_discoveredResourceTypes.insert(static_cast<int>(type));

        if (isRetainedMaterial(type)) {
            m_materialStock[static_cast<int>(type)] += count;
            report.retainedCount += count;
            retainedParts.push_back(formatResourceCount(type, count));
        } else {
            const int soldValue = sellValueForType(type) * count;
            m_credits += soldValue;
            m_lifetimeCreditsEarned += soldValue;
            report.soldCount += count;
            report.soldValue += soldValue;
            soldParts.push_back(QStringLiteral("%1（+%2积分）").arg(formatResourceCount(type, count)).arg(soldValue));
        }
    }

    report.soldSummary = soldParts.isEmpty() ? QStringLiteral("无可出售资源") : soldParts.join(QStringLiteral(" / "));
    report.retainedSummary = retainedParts.isEmpty() ? QStringLiteral("无新增材料") : retainedParts.join(QStringLiteral(" / "));

    m_lastSettlement = report;
    m_isSettling = true;
    m_successfulRuns += 1;
    updateRegionUnlocks();
    if (!thermalUnlockedBefore && isRegionUnlocked(SeaRegionId::ThermalFault)) {
        m_selectedRegion = SeaRegionId::ThermalFault;
        m_upgradeFeedbackText = QStringLiteral("已解锁新海域：热泉断层采样区。可用左右方向键切换海域。");
    } else {
        m_selectedRegion = m_currentRegion;
        m_upgradeFeedbackText = QStringLiteral("按左右方向键切换海域，按 1-5 升级，再按回车、空格或 E 出航。");
    }
    m_collectingResourceIndex = -1;
    m_currentCollectProgress = 0.0f;
    m_player.setVelocity(QPointF());
    m_pressedKeys.clear();
    savePersistentState(false);
    playFeedbackBeep();

    qCInfo(settlementLog).noquote()
        << QStringLiteral("[settlement] return success | collected=%1 sold=%2 value=%3 retained=%4 credits=%5")
               .arg(report.totalCollected)
               .arg(report.soldCount)
               .arg(report.soldValue)
               .arg(report.retainedCount)
               .arg(m_credits);
}

void GameScene::tryPurchaseUpgrade(const UpgradeType type)
{
    const UpgradeDefinition definition = upgradeDefinition(type);
    const int currentLevel = upgradeLevel(type);
    if (currentLevel >= definition.maxLevel) {
        m_upgradeFeedbackText = QStringLiteral("%1已达到最高等级。").arg(definition.name);
        setStatusMessage(m_upgradeFeedbackText);
        return;
    }

    const int nextLevel = currentLevel + 1;
    const int creditCost = definition.creditCosts.at(nextLevel - 1);
    const int materialCost = definition.materialCosts.at(nextLevel - 1);
    const int materialStock = m_materialStock.value(static_cast<int>(definition.materialType), 0);

    if (m_credits < creditCost || materialStock < materialCost) {
        m_upgradeFeedbackText = QStringLiteral("升级失败：%1需要%2积分，还缺少%3个%4。")
                                    .arg(definition.name)
                                    .arg(creditCost)
                                    .arg(qMax(0, materialCost - materialStock))
                                    .arg(resourceName(definition.materialType));
        setStatusMessage(m_upgradeFeedbackText);
        return;
    }

    m_credits -= creditCost;
    m_materialStock[static_cast<int>(definition.materialType)] = materialStock - materialCost;
    m_upgradeLevels[static_cast<int>(type)] = nextLevel;
    applyPersistentUpgrades();
    m_upgradeFeedbackText = QStringLiteral("%1已升级到%2级。%3")
                                .arg(definition.name)
                                .arg(nextLevel)
                                .arg(formatUpgradeEffect(type, nextLevel));
    savePersistentState(false);
    playFeedbackBeep();
    setStatusMessage(m_upgradeFeedbackText);

    qCInfo(upgradeLog).noquote()
        << QStringLiteral("[upgrade] %1 -> level %2 | credits=%3")
               .arg(definition.name)
               .arg(nextLevel)
               .arg(m_credits);
}

void GameScene::tryLaunchSelectedRegion()
{
    if (!isRegionUnlocked(m_selectedRegion)) {
        m_upgradeFeedbackText = regionUnlockRequirementText(m_selectedRegion);
        setStatusMessage(m_upgradeFeedbackText);
        return;
    }

    m_currentRegion = m_selectedRegion;
    m_isSettling = false;
    savePersistentState(false);
    resetRunState();
    setStatusMessage(QStringLiteral("已切换到 %1，准备出航。").arg(regionDefinition(m_currentRegion).name));
    qCInfo(settlementLog) << "[settlement] launched region" << regionDefinition(m_currentRegion).name;
}

bool GameScene::loadPersistentState(const bool demoSlot)
{
    QFile file(saveFilePath(demoSlot));
    if (!file.exists()) {
        return false;
    }
    if (!file.open(QIODevice::ReadOnly)) {
        qCWarning(saveLog) << "[save] failed to open" << file.fileName() << "for reading";
        return false;
    }

    const QJsonDocument document = QJsonDocument::fromJson(file.readAll());
    if (!document.isObject()) {
        qCWarning(saveLog) << "[save] invalid json document in" << file.fileName();
        return false;
    }

    const QJsonObject root = document.object();
    m_credits = root.value(QStringLiteral("credits")).toInt(0);
    m_lifetimeCreditsEarned = root.value(QStringLiteral("lifetimeCreditsEarned")).toInt(0);
    m_successfulRuns = root.value(QStringLiteral("successfulRuns")).toInt(0);
    m_soundEnabled = root.contains(QStringLiteral("soundEnabled"))
        ? root.value(QStringLiteral("soundEnabled")).toBool(true)
        : true;

    m_materialStock.clear();
    const QJsonObject materialObject = root.value(QStringLiteral("materialStock")).toObject();
    for (const QString &key : materialObject.keys()) {
        m_materialStock[static_cast<int>(resourceTypeFromKey(key))] = materialObject.value(key).toInt(0);
    }

    m_upgradeLevels.clear();
    const QJsonObject upgradeObject = root.value(QStringLiteral("upgradeLevels")).toObject();
    for (const QString &key : upgradeObject.keys()) {
        m_upgradeLevels[key.toInt()] = upgradeObject.value(key).toInt(0);
    }

    m_lifetimeCollectedCounts.clear();
    const QJsonObject codexObject = root.value(QStringLiteral("lifetimeCollectedCounts")).toObject();
    for (const QString &key : codexObject.keys()) {
        m_lifetimeCollectedCounts[static_cast<int>(resourceTypeFromKey(key))] = codexObject.value(key).toInt(0);
    }

    m_discoveredResourceTypes.clear();
    const QJsonArray discoveredArray = root.value(QStringLiteral("discoveredResourceTypes")).toArray();
    for (const QJsonValue &value : discoveredArray) {
        m_discoveredResourceTypes.insert(static_cast<int>(resourceTypeFromKey(value.toString())));
    }

    m_regionUnlocked.clear();
    const QJsonObject regionObject = root.value(QStringLiteral("regionUnlocked")).toObject();
    for (const QString &key : regionObject.keys()) {
        m_regionUnlocked[static_cast<int>(regionFromKey(key))] = regionObject.value(key).toBool(false);
    }

    m_currentRegion = regionFromKey(root.value(QStringLiteral("currentRegion")).toString());
    m_selectedRegion = regionFromKey(root.value(QStringLiteral("selectedRegion")).toString());

    updateRegionUnlocks();
    if (!isRegionUnlocked(m_currentRegion)) {
        m_currentRegion = SeaRegionId::CoastalShelf;
    }
    if (!isRegionUnlocked(m_selectedRegion)) {
        m_selectedRegion = m_currentRegion;
    }
    applyPersistentUpgrades();

    qCInfo(saveLog) << "[save] loaded" << file.fileName() << "| version =" << root.value(QStringLiteral("version")).toInt(kSaveFormatVersion);
    return true;
}

bool GameScene::savePersistentState(const bool demoSlot) const
{
    const QString path = saveFilePath(demoSlot);
    QDir dir = QFileInfo(path).dir();
    if (!dir.exists() && !dir.mkpath(QStringLiteral("."))) {
        qCWarning(saveLog) << "[save] failed to create save directory" << dir.absolutePath();
        return false;
    }

    QJsonObject root;
    root.insert(QStringLiteral("version"), kSaveFormatVersion);
    root.insert(QStringLiteral("credits"), m_credits);
    root.insert(QStringLiteral("lifetimeCreditsEarned"), m_lifetimeCreditsEarned);
    root.insert(QStringLiteral("successfulRuns"), m_successfulRuns);
    root.insert(QStringLiteral("soundEnabled"), m_soundEnabled);
    root.insert(QStringLiteral("currentRegion"), regionKey(m_currentRegion));
    root.insert(QStringLiteral("selectedRegion"), regionKey(m_selectedRegion));

    QJsonObject materialObject;
    for (const ResourceItem::Type type : allResourceTypes()) {
        materialObject.insert(resourceTypeKey(type), m_materialStock.value(static_cast<int>(type), 0));
    }
    root.insert(QStringLiteral("materialStock"), materialObject);

    QJsonObject upgradeObject;
    for (auto it = m_upgradeLevels.constBegin(); it != m_upgradeLevels.constEnd(); ++it) {
        upgradeObject.insert(QString::number(it.key()), it.value());
    }
    root.insert(QStringLiteral("upgradeLevels"), upgradeObject);

    QJsonObject regionObject;
    for (const SeaRegionDefinition &definition : regionDefinitions()) {
        regionObject.insert(regionKey(definition.id), isRegionUnlocked(definition.id));
    }
    root.insert(QStringLiteral("regionUnlocked"), regionObject);

    QJsonArray discoveredArray;
    for (const ResourceItem::Type type : allResourceTypes()) {
        if (m_discoveredResourceTypes.contains(static_cast<int>(type))) {
            discoveredArray.push_back(resourceTypeKey(type));
        }
    }
    root.insert(QStringLiteral("discoveredResourceTypes"), discoveredArray);

    QJsonObject codexObject;
    for (const ResourceItem::Type type : allResourceTypes()) {
        codexObject.insert(resourceTypeKey(type), m_lifetimeCollectedCounts.value(static_cast<int>(type), 0));
    }
    root.insert(QStringLiteral("lifetimeCollectedCounts"), codexObject);

    QFile file(path);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        qCWarning(saveLog) << "[save] failed to open" << path << "for writing";
        return false;
    }

    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    qCInfo(saveLog) << "[save] wrote" << path;
    return true;
}

QString GameScene::saveFilePath(const bool demoSlot) const
{
    const QString root = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    const QString filename = demoSlot
        ? QStringLiteral("demo_save.json")
        : QStringLiteral("autosave.json");
    return QDir(root).filePath(filename);
}

void GameScene::setStatusMessage(const QString &message)
{
    m_statusText = message;
    m_statusTextExpiresMs = (m_elapsedTimer.isValid() ? m_elapsedTimer.elapsed() : 0) + kStatusMessageDurationMs;
}

void GameScene::playFeedbackBeep() const
{
    if (m_soundEnabled) {
        QApplication::beep();
    }
}

int GameScene::lifetimeCollectedCount(const ResourceItem::Type type) const
{
    return m_lifetimeCollectedCounts.value(static_cast<int>(type), 0);
}

void GameScene::applyDamage(const float damage,
                            const float oxygenDamage,
                            const QPointF &knockbackDirection,
                            const float knockbackStrength,
                            const QString &reason)
{
    if (m_isRunFailed || m_isSettling || m_showCodexOverlay) {
        return;
    }

    if (damage > 0.0f && m_invulnerabilitySeconds > 0.0f) {
        return;
    }

    if (oxygenDamage > 0.0f) {
        m_player.setOxygen(m_player.oxygen() - oxygenDamage);
    }

    if (damage > 0.0f) {
        m_playerHealth = qMax(0.0f, m_playerHealth - damage);
        m_invulnerabilitySeconds = kHitInvulnerabilitySeconds;
        m_controlLockSeconds = kControlLockSeconds;
        m_damageFlashSeconds = kHitFlashSeconds;
        m_collectingResourceIndex = -1;
        m_currentCollectProgress = 0.0f;
        m_lastDamageReason = reason;
        playFeedbackBeep();
        setStatusMessage(QStringLiteral("危险：%1").arg(reason));
    }

    const float length = std::hypot(knockbackDirection.x(), knockbackDirection.y());
    if (length > 0.001f && knockbackStrength > 0.0f) {
        const QPointF normalized(knockbackDirection.x() / length, knockbackDirection.y() / length);
        m_player.setVelocity(normalized * knockbackStrength);
    }

    if (m_playerHealth <= 0.0f || m_player.oxygenState() == Player::OxygenState::Empty) {
        m_isRunFailed = true;
        m_player.setVelocity(QPointF());
    }
}

bool GameScene::isRunLocked() const
{
    return m_isRunFailed || m_isSettling || m_showCodexOverlay || m_controlLockSeconds > 0.0f;
}

QVector<GameScene::SeaRegionDefinition> GameScene::regionDefinitions() const
{
    return {
        {SeaRegionId::CoastalShelf,
         QStringLiteral("近岸浅层回收带"),
         QStringLiteral("新手海域，资源稳定，危险较少。"),
         QStringLiteral("荧团浮体 / 壳晶石"),
         QStringLiteral("单只电弧鳐、单个热泉喷口"),
         1200.0f,
         0,
         0,
         ResourceItem::Type::GlowCluster,
         QColor(6, 29, 64),
         QColor(10, 53, 94),
         QColor(3, 13, 28),
         QColor(26, 44, 41)},
        {SeaRegionId::ThermalFault,
         QStringLiteral("热泉断层采样区"),
         QStringLiteral("中期海域，收益更高，危险更密集。"),
         QStringLiteral("冷凝胶 / 旧时代零件"),
         QStringLiteral("双电弧鳐、双热泉喷口"),
         1800.0f,
         36,
         2,
         ResourceItem::Type::OldPart,
         QColor(20, 18, 54),
         QColor(60, 28, 73),
         QColor(22, 7, 16),
         QColor(68, 32, 28)},
    };
}

GameScene::SeaRegionDefinition GameScene::regionDefinition(const SeaRegionId id) const
{
    const QVector<SeaRegionDefinition> definitions = regionDefinitions();
    for (const SeaRegionDefinition &definition : definitions) {
        if (definition.id == id) {
            return definition;
        }
    }
    return definitions.first();
}

bool GameScene::isRegionUnlocked(const SeaRegionId id) const
{
    if (id == SeaRegionId::CoastalShelf) {
        return true;
    }
    return m_regionUnlocked.value(static_cast<int>(id), false);
}

void GameScene::updateRegionUnlocks()
{
    m_regionUnlocked[static_cast<int>(SeaRegionId::CoastalShelf)] = true;

    const SeaRegionDefinition thermalFault = regionDefinition(SeaRegionId::ThermalFault);
    const bool unlocked = m_lifetimeCreditsEarned >= thermalFault.unlockLifetimeCredits &&
                          m_successfulRuns >= thermalFault.unlockSuccessfulRuns &&
                          m_discoveredResourceTypes.contains(static_cast<int>(thermalFault.unlockKeyResource));
    m_regionUnlocked[static_cast<int>(SeaRegionId::ThermalFault)] = unlocked;
}

QString GameScene::regionUnlockRequirementText(const SeaRegionId id) const
{
    const SeaRegionDefinition definition = regionDefinition(id);
    if (isRegionUnlocked(id)) {
        return QStringLiteral("%1已解锁，可直接进入。").arg(definition.name);
    }

    QStringList missing;
    if (m_lifetimeCreditsEarned < definition.unlockLifetimeCredits) {
        missing.push_back(QStringLiteral("累计积分还差%1").arg(definition.unlockLifetimeCredits - m_lifetimeCreditsEarned));
    }
    if (m_successfulRuns < definition.unlockSuccessfulRuns) {
        missing.push_back(QStringLiteral("成功返航次数还差%1").arg(definition.unlockSuccessfulRuns - m_successfulRuns));
    }
    if (!m_discoveredResourceTypes.contains(static_cast<int>(definition.unlockKeyResource))) {
        missing.push_back(QStringLiteral("尚未带回关键资源：%1").arg(resourceName(definition.unlockKeyResource)));
    }

    return QStringLiteral("%1未解锁：%2").arg(definition.name, missing.join(QStringLiteral("；")));
}

float GameScene::currentRegionDepthCap() const
{
    return regionDefinition(m_currentRegion).recommendedDepthMeters;
}

float GameScene::currentDepthRatio() const
{
    const QRectF area = playAreaRect();
    if (area.height() <= 0.0) {
        return 0.0f;
    }

    const float depth = static_cast<float>((m_player.position().y() - area.top()) / area.height());
    return qBound(0.0f, depth, 1.0f);
}

float GameScene::currentDepthMeters() const
{
    return currentDepthRatio() * currentRegionDepthCap();
}

QRectF GameScene::playAreaRect() const
{
    return QRectF(kPlayAreaMargin,
                  kTopAreaOffset,
                  qMax(0.0, width() - kPlayAreaMargin * 2.0),
                  qMax(0.0, height() - kTopAreaOffset - kBottomAreaOffset));
}

QRectF GameScene::returnZoneRect() const
{
    const QRectF area = playAreaRect();
    if (area.isEmpty()) {
        return {};
    }

    const qreal zoneWidth = qMax(180.0, area.width() * kReturnZoneWidthFactor);
    return QRectF(area.center().x() - zoneWidth * 0.5,
                  area.top() + kReturnZoneTopInset,
                  zoneWidth,
                  kReturnZoneHeight);
}

QVector<QRectF> GameScene::obstacleRects() const
{
    const QRectF area = playAreaRect();
    if (area.isEmpty()) {
        return {};
    }

    const qreal left = area.left();
    const qreal top = area.top();
    const qreal w = area.width();
    const qreal h = area.height();

    if (m_currentRegion == SeaRegionId::ThermalFault) {
        return {
            QRectF(left + w * 0.10, top + h * 0.28, 96.0, h * 0.22),
            QRectF(left + w * 0.34, top + h * 0.48, 210.0, 56.0),
            QRectF(left + w * 0.58, top + h * 0.20, 88.0, h * 0.30),
            QRectF(left + w * 0.74, top + h * 0.70, 150.0, 38.0),
            QRectF(left + w * 0.82, top + h * 0.42, 90.0, h * 0.16),
        };
    }

    return {
        QRectF(left + w * 0.12, top + h * 0.22, 78.0, h * 0.24),
        QRectF(left + w * 0.38, top + h * 0.56, 160.0, 46.0),
        QRectF(left + w * 0.66, top + h * 0.30, 72.0, h * 0.34),
        QRectF(left + w * 0.78, top + h * 0.68, 120.0, 34.0),
    };
}

QVector<GameScene::UpgradeDefinition> GameScene::upgradeDefinitions() const
{
    return {
        {UpgradeType::OxygenTank, 1, 3, ResourceItem::Type::ColdGel, {24, 42, 66}, {1, 2, 3},
         QStringLiteral("压缩气瓶"),
         QStringLiteral("提高最大氧气容量，延长单次下潜时间。")},
        {UpgradeType::Thruster, 2, 3, ResourceItem::Type::ShellCrystal, {20, 36, 58}, {1, 2, 3},
         QStringLiteral("推进器"),
         QStringLiteral("提高移动速度，返航更稳更快。")},
        {UpgradeType::CargoBay, 3, 3, ResourceItem::Type::OldPart, {18, 30, 48}, {1, 2, 3},
         QStringLiteral("货舱扩容"),
         QStringLiteral("提高单次出航可携带的资源上限。")},
        {UpgradeType::RecoveryArm, 4, 3, ResourceItem::Type::ShellCrystal, {22, 38, 60}, {1, 2, 2},
         QStringLiteral("回收机械臂"),
         QStringLiteral("缩短长按采集重型资源所需时间。")},
        {UpgradeType::PressureHull, 5, 3, ResourceItem::Type::ColdGel, {26, 44, 68}, {1, 2, 3},
         QStringLiteral("耐压壳体"),
         QStringLiteral("降低整次出航过程中的氧气消耗。")},
    };
}

GameScene::UpgradeDefinition GameScene::upgradeDefinition(const UpgradeType type) const
{
    const QVector<UpgradeDefinition> definitions = upgradeDefinitions();
    for (const UpgradeDefinition &definition : definitions) {
        if (definition.type == type) {
            return definition;
        }
    }
    return definitions.first();
}

int GameScene::upgradeLevel(const UpgradeType type) const
{
    return m_upgradeLevels.value(static_cast<int>(type), 0);
}

int GameScene::currentMaxOxygenValue() const
{
    return 100 + upgradeLevel(UpgradeType::OxygenTank) * 25;
}

int GameScene::currentCargoLimitValue() const
{
    return 10 + upgradeLevel(UpgradeType::CargoBay) * 2;
}

float GameScene::currentMoveSpeedValue() const
{
    return 240.0f + static_cast<float>(upgradeLevel(UpgradeType::Thruster) * 30);
}

float GameScene::currentCollectionDurationMultiplier() const
{
    switch (upgradeLevel(UpgradeType::RecoveryArm)) {
    case 1:
        return 0.88f;
    case 2:
        return 0.76f;
    case 3:
        return 0.64f;
    default:
        return 1.0f;
    }
}

float GameScene::currentOxygenEfficiencyMultiplier() const
{
    switch (upgradeLevel(UpgradeType::PressureHull)) {
    case 1:
        return 0.92f;
    case 2:
        return 0.84f;
    case 3:
        return 0.76f;
    default:
        return 1.0f;
    }
}

QString GameScene::formatDuration(const qint64 durationMs) const
{
    const qint64 totalSeconds = qMax<qint64>(0, durationMs / 1000);
    const qint64 minutes = totalSeconds / 60;
    const qint64 seconds = totalSeconds % 60;
    return QStringLiteral("%1:%2")
        .arg(minutes, 2, 10, QChar('0'))
        .arg(seconds, 2, 10, QChar('0'));
}

QString GameScene::formatResourceCount(const ResourceItem::Type type, const int count) const
{
    return QStringLiteral("%1x%2").arg(resourceName(type)).arg(count);
}

QString GameScene::formatMaterialStockSummary() const
{
    QStringList parts;
    for (const ResourceItem::Type type : allResourceTypes()) {
        const int count = m_materialStock.value(static_cast<int>(type), 0);
        if (count > 0) {
            parts.push_back(formatResourceCount(type, count));
        }
    }
    return parts.isEmpty() ? QStringLiteral("无长期材料") : parts.join(QStringLiteral(" / "));
}

QString GameScene::formatUpgradeEffect(const UpgradeType type, const int level) const
{
    switch (type) {
    case UpgradeType::OxygenTank:
        return QStringLiteral("最大氧气 %1").arg(100 + level * 25);
    case UpgradeType::Thruster:
        return QStringLiteral("移动速度 %1").arg(240 + level * 30);
    case UpgradeType::CargoBay:
        return QStringLiteral("货舱上限 %1").arg(10 + level * 2);
    case UpgradeType::RecoveryArm: {
        const float multiplier = level == 1 ? 0.88f : (level == 2 ? 0.76f : 0.64f);
        return QStringLiteral("采集耗时倍率 x%1").arg(multiplier, 0, 'f', 2);
    }
    case UpgradeType::PressureHull: {
        const float multiplier = level == 1 ? 0.92f : (level == 2 ? 0.84f : 0.76f);
        return QStringLiteral("氧气消耗倍率 x%1").arg(multiplier, 0, 'f', 2);
    }
    }
    return QStringLiteral("无效果");
}

QString GameScene::formatUpgradeStatus(const UpgradeType type) const
{
    const UpgradeDefinition definition = upgradeDefinition(type);
    const int currentLevel = upgradeLevel(type);
    if (currentLevel >= definition.maxLevel) {
        return QStringLiteral("%1级 / 已满级 | %2")
            .arg(currentLevel)
            .arg(formatUpgradeEffect(type, currentLevel));
    }

    const int nextLevel = currentLevel + 1;
    const int creditCost = definition.creditCosts.at(nextLevel - 1);
    const int materialCost = definition.materialCosts.at(nextLevel - 1);
    return QStringLiteral("%1级 -> %2级 | %3积分 + %4个%5 | %6")
        .arg(currentLevel)
        .arg(nextLevel)
        .arg(creditCost)
        .arg(materialCost)
        .arg(resourceName(definition.materialType))
        .arg(formatUpgradeEffect(type, nextLevel));
}

QString GameScene::hazardStateText(const HazardCreature &creature) const
{
    switch (creature.state) {
    case HazardCreature::State::Patrol:
        return QStringLiteral("巡逻");
    case HazardCreature::State::Alert:
        return QStringLiteral("追击");
    case HazardCreature::State::Cooldown:
        return QStringLiteral("冷却");
    }

    return QStringLiteral("未知");
}

QString GameScene::failureReasonText() const
{
    if (!m_lastDamageReason.isEmpty()) {
        return m_lastDamageReason;
    }
    return QStringLiteral("未知原因");
}

QString GameScene::regionStatusText(const SeaRegionId id) const
{
    const SeaRegionDefinition definition = regionDefinition(id);
    if (isRegionUnlocked(id)) {
        return QStringLiteral("%1：已解锁，可直接出航。").arg(definition.name);
    }
    return regionUnlockRequirementText(id);
}

int GameScene::sellValueForType(const ResourceItem::Type type) const
{
    switch (type) {
    case ResourceItem::Type::GlowCluster:
        return kGlowClusterSellValue;
    case ResourceItem::Type::ShellCrystal:
    case ResourceItem::Type::ColdGel:
    case ResourceItem::Type::OldPart:
        return 0;
    }
    return 0;
}

bool GameScene::isRetainedMaterial(const ResourceItem::Type type) const
{
    return type == ResourceItem::Type::ShellCrystal ||
           type == ResourceItem::Type::ColdGel ||
           type == ResourceItem::Type::OldPart;
}

void GameScene::drawBackground(QPainter &painter) const
{
    const SeaRegionDefinition region = regionDefinition(m_currentRegion);
    QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
    gradient.setColorAt(0.0, region.topColor);
    gradient.setColorAt(0.35, region.midColor);
    gradient.setColorAt(1.0, region.bottomColor);
    painter.fillRect(rect(), gradient);

    painter.setPen(Qt::NoPen);
    for (int i = 0; i < 12; ++i) {
        const int x = (i * width()) / 11;
        const int bob = static_cast<int>((m_totalElapsedMs / 35 + i * 13) % 28);
        painter.setBrush(m_currentRegion == SeaRegionId::ThermalFault
                             ? QColor(255, 181, 118, 35)
                             : QColor(122, 216, 255, 35));
        painter.drawEllipse(QPointF(x, 90 + bob), 4.0, 4.0);
    }
}

void GameScene::drawSeaFloor(QPainter &painter) const
{
    const SeaRegionDefinition region = regionDefinition(m_currentRegion);
    QPainterPath floorPath;
    floorPath.moveTo(0.0, height() * 0.82);
    floorPath.cubicTo(width() * 0.25, height() * 0.74,
                      width() * 0.65, height() * 0.92,
                      width(), height() * 0.80);
    floorPath.lineTo(width(), height());
    floorPath.lineTo(0.0, height());
    floorPath.closeSubpath();

    painter.fillPath(floorPath, region.floorColor);
    painter.setPen(QPen(m_currentRegion == SeaRegionId::ThermalFault ? QColor(184, 121, 93) : QColor(86, 126, 118), 2));
    painter.drawPath(floorPath);
}

void GameScene::drawObstacles(QPainter &painter) const
{
    painter.setPen(QPen(QColor(144, 186, 193), 2));
    const QVector<QRectF> obstacles = obstacleRects();
    for (int index = 0; index < obstacles.size(); ++index) {
        const QRectF &rect = obstacles.at(index);
        painter.setBrush(index % 2 == 0 ? QColor(67, 88, 93) : QColor(79, 102, 109));
        painter.drawRoundedRect(rect, 10.0, 10.0);

        painter.setBrush(QColor(128, 206, 220, 120));
        painter.drawEllipse(QPointF(rect.center().x(), rect.top() + 12.0), 6.0, 6.0);
    }
}

void GameScene::drawReturnZone(QPainter &painter) const
{
    const QRectF zone = returnZoneRect();
    if (zone.isEmpty()) {
        return;
    }

    painter.save();
    const bool active = m_player.bounds().intersects(zone) && !m_isRunFailed;
    painter.setPen(QPen(active ? QColor(255, 245, 168) : QColor(158, 232, 255), 2));
    painter.setBrush(active ? QColor(255, 245, 168, 70) : QColor(99, 210, 240, 50));
    painter.drawRoundedRect(zone, 14.0, 14.0);
    painter.setPen(QColor(236, 248, 255));
    painter.drawText(zone.adjusted(0.0, 8.0, 0.0, 0.0),
                     Qt::AlignTop | Qt::AlignHCenter,
                     QStringLiteral("返航回收区"));
    painter.restore();
}

void GameScene::drawHazards(QPainter &painter) const
{
    painter.save();

    for (const HazardZone &zone : m_hazardZones) {
        QLinearGradient gradient(zone.rect.topLeft(), zone.rect.bottomRight());
        gradient.setColorAt(0.0, QColor(255, 150, 84, 110));
        gradient.setColorAt(1.0, QColor(255, 73, 31, 170));
        painter.setPen(QPen(QColor(255, 214, 184), 2, Qt::DashLine));
        painter.setBrush(gradient);
        painter.drawRoundedRect(zone.rect, 18.0, 18.0);
        painter.setPen(QColor(255, 238, 220));
        painter.drawText(zone.rect.adjusted(0, 8, 0, 0), Qt::AlignTop | Qt::AlignHCenter, zone.name);

        for (int i = 0; i < 4; ++i) {
            const qreal x = zone.rect.left() + 18.0 + i * 22.0;
            const qreal offset = qSin((m_totalElapsedMs + i * 90) / 180.0) * 10.0;
            painter.setBrush(QColor(255, 237, 196, 120));
            painter.drawEllipse(QPointF(x, zone.rect.bottom() - 18.0 - offset), 6.0, 10.0);
        }
    }

    for (const HazardCreature &creature : m_hazardCreatures) {
        const bool alert = creature.state == HazardCreature::State::Alert;
        painter.setPen(QPen(alert ? QColor(255, 238, 180) : QColor(183, 238, 255), 2));
        painter.setBrush(alert ? QColor(255, 98, 66) : QColor(70, 185, 222));
        painter.drawEllipse(creature.position, creature.radius, creature.radius * 0.72);

        painter.setBrush(QColor(255, 244, 168, 180));
        painter.drawEllipse(QPointF(creature.position.x() + creature.radius * 0.35,
                                    creature.position.y() - creature.radius * 0.18),
                            5.0,
                            5.0);

        painter.setPen(QPen(QColor(255, 206, 103, alert ? 180 : 90), 1, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(creature.position, creature.detectRange, creature.detectRange);

        painter.setPen(QColor(235, 247, 255));
        painter.drawText(QRectF(creature.position.x() - 72.0,
                                creature.position.y() - creature.radius - 30.0,
                                144.0,
                                20.0),
                         Qt::AlignCenter,
                         QStringLiteral("%1 / %2").arg(creature.name, hazardStateText(creature)));
    }

    painter.restore();
}

void GameScene::drawResources(QPainter &painter) const
{
    const int activeIndex = currentCollectableIndex();

    for (int index = 0; index < m_resources.size(); ++index) {
        const ResourceItem &resource = m_resources.at(index);
        const QPointF center = resource.position();
        const bool isActive = index == activeIndex;

        painter.setPen(QPen(isActive ? QColor(255, 255, 255) : QColor(173, 234, 243), isActive ? 2 : 1));
        painter.setBrush(resource.color());
        painter.drawEllipse(center, resource.radius(), resource.radius());

        if (resource.collectMode() == ResourceItem::CollectMode::Hold) {
            painter.setBrush(QColor(255, 255, 255, 55));
            painter.drawRect(QRectF(center.x() - 4.0, center.y() - resource.radius() - 10.0, 8.0, 20.0));
        }

        if (isActive) {
            painter.setPen(QPen(QColor(255, 239, 168), 2));
            painter.setBrush(Qt::NoBrush);
            painter.drawEllipse(center, resource.radius() + 8.0, resource.radius() + 8.0);
        }
    }
}

void GameScene::drawCollisionDebug(QPainter &painter) const
{
    painter.save();
    painter.setBrush(Qt::NoBrush);

    painter.setPen(QPen(QColor(255, 223, 125, 200), 2, Qt::DashLine));
    painter.drawRect(playAreaRect());

    painter.setPen(QPen(QColor(114, 224, 255, 220), 2, Qt::DashLine));
    painter.drawRect(returnZoneRect());

    painter.setPen(QPen(QColor(255, 114, 114, 220), 2, Qt::DashLine));
    for (const QRectF &rect : obstacleRects()) {
        painter.drawRect(rect);
    }

    painter.setPen(QPen(QColor(255, 128, 72, 220), 2, Qt::DashLine));
    for (const HazardZone &zone : m_hazardZones) {
        painter.drawRect(zone.rect);
    }

    painter.setPen(QPen(QColor(88, 255, 192, 220), 2, Qt::DashLine));
    painter.drawRect(m_player.bounds());
    painter.restore();
}

void GameScene::drawPlayer(QPainter &painter) const
{
    const QPointF center = m_player.position();
    const qreal centerX = center.x();
    const qreal baseY = center.y();
    const qreal bob = m_player.isMoving()
        ? qSin(static_cast<qreal>(m_totalElapsedMs) / 180.0) * 4.0
        : qSin(static_cast<qreal>(m_totalElapsedMs) / 320.0) * 2.0;
    const QRectF bodyRect(centerX - 70.0, baseY - 26.0 + bob, 140.0, 52.0);

    QColor bodyColor(242, 176, 59);
    switch (m_player.facing()) {
    case Player::Facing::Left:
        bodyColor = QColor(230, 160, 74);
        break;
    case Player::Facing::Right:
        bodyColor = QColor(242, 176, 59);
        break;
    case Player::Facing::Up:
        bodyColor = QColor(255, 198, 87);
        break;
    case Player::Facing::Down:
        bodyColor = QColor(224, 151, 53);
        break;
    }

    painter.setPen(QPen(QColor(190, 238, 255), 2));
    painter.setBrush(bodyColor);
    painter.drawRoundedRect(bodyRect, 26.0, 26.0);

    painter.setBrush(QColor(46, 85, 112));
    painter.drawEllipse(QRectF(centerX - 18.0, baseY - 14.0 + bob, 36.0, 28.0));

    painter.setBrush(QColor(255, 228, 170));
    painter.drawRect(QRectF(centerX + 48.0, baseY - 10.0 + bob, 18.0, 20.0));

    painter.setBrush(QColor(100, 205, 245));
    painter.drawEllipse(QPointF(centerX - 56.0, baseY + bob), 7.0, 7.0);

    if (m_player.isMoving()) {
        painter.setPen(Qt::NoPen);
        painter.setBrush(QColor(148, 222, 255, 110));
        painter.drawEllipse(QPointF(centerX - 82.0, baseY + bob), 12.0, 6.0);
        painter.drawEllipse(QPointF(centerX - 95.0, baseY + bob), 8.0, 4.0);
    }

    if (m_damageFlashSeconds > 0.0f) {
        painter.setPen(QPen(QColor(255, 102, 102), 4));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPointF(centerX, baseY + bob), 92.0, 46.0);
    } else if (m_invulnerabilitySeconds > 0.0f) {
        painter.setPen(QPen(QColor(255, 215, 121, 180), 2, Qt::DashLine));
        painter.setBrush(Qt::NoBrush);
        painter.drawEllipse(QPointF(centerX, baseY + bob), 88.0, 42.0);
    }

    if (m_isRunFailed) {
        painter.setPen(QPen(QColor(255, 112, 112), 3));
        painter.drawEllipse(QPointF(centerX, baseY + bob), 88.0, 42.0);
    }
}

void GameScene::drawHud(QPainter &painter) const
{
    const SeaRegionDefinition currentRegion = regionDefinition(m_currentRegion);
    const SeaRegionDefinition thermalFault = regionDefinition(SeaRegionId::ThermalFault);
    const bool thermalUnlocked = isRegionUnlocked(SeaRegionId::ThermalFault);
    const bool thermalKeyDiscovered =
        m_discoveredResourceTypes.contains(static_cast<int>(thermalFault.unlockKeyResource));
    QString interactionText = QStringLiteral("附近资源：无可交互目标");
    const int activeResourceIndex = currentCollectableIndex();
    if (activeResourceIndex >= 0) {
        const ResourceItem &resource = m_resources.at(activeResourceIndex);
        interactionText = QStringLiteral("附近资源：%1，%2")
                              .arg(resource.displayName(),
                                   resource.collectMode() == ResourceItem::CollectMode::Instant
                                       ? QStringLiteral("按 E 立即回收")
                                       : QStringLiteral("按住 E 持续采集"));
    }

    const QString unlockProgress = thermalUnlocked
        ? QStringLiteral("热泉断层采样区已解锁，可在返航终端中切换。")
        : QStringLiteral("热泉断层采样区解锁进度：累计收益 %1/%2，成功返航 %3/%4，关键资源 %5")
              .arg(m_lifetimeCreditsEarned)
              .arg(thermalFault.unlockLifetimeCredits)
              .arg(m_successfulRuns)
              .arg(thermalFault.unlockSuccessfulRuns)
              .arg(thermalKeyDiscovered ? QStringLiteral("已带回旧时代零件")
                                        : QStringLiteral("尚未带回旧时代零件"));

    QString cautionText;
    QColor cautionColor(164, 214, 229);
    if (!m_statusText.isEmpty()) {
        cautionText = m_statusText;
        cautionColor = QColor(160, 238, 191);
    } else if (m_isRunFailed) {
        cautionText = QStringLiteral("任务失败：%1。按 R 重新开始本轮出航。").arg(failureReasonText());
        cautionColor = QColor(255, 126, 126);
    } else if (m_isSettling) {
        cautionText = QStringLiteral("已返航：按左右键切换海域，按 1-5 升级，按回车、空格或 E 出航。");
        cautionColor = QColor(148, 241, 188);
    } else if (m_player.oxygenState() == Player::OxygenState::Danger) {
        cautionText = QStringLiteral("危险：氧气极低，建议立即返航。");
        cautionColor = QColor(255, 109, 109);
    } else if (m_player.oxygenState() == Player::OxygenState::Warning) {
        cautionText = QStringLiteral("低氧预警：继续下潜前请确认返航路线。");
        cautionColor = QColor(255, 210, 94);
    } else {
        cautionText = QStringLiteral("状态正常：保持存活，完成采集后进入顶部返航回收区。");
    }

    QColor oxygenFillColor(78, 208, 255);
    switch (m_player.oxygenState()) {
    case Player::OxygenState::Safe:
        oxygenFillColor = QColor(78, 208, 255);
        break;
    case Player::OxygenState::Warning:
        oxygenFillColor = QColor(255, 205, 78);
        break;
    case Player::OxygenState::Danger:
        oxygenFillColor = QColor(255, 94, 94);
        break;
    case Player::OxygenState::Empty:
        oxygenFillColor = QColor(133, 33, 33);
        break;
    }

    QFont titleFont = painter.font();
    titleFont.setPointSize(15);
    titleFont.setBold(true);
    QFont sectionFont = painter.font();
    sectionFont.setPointSize(11);
    sectionFont.setBold(true);
    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);

    const QRect leftPanel(kHudPadding, kHudPadding, 392, 212);
    const QRect rightPanel(width() - 360, kHudPadding, 342, 252);
    const QRect bottomPanel(kHudPadding, height() - 142, 790, 116);

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(3, 14, 27, 160));
    painter.drawRoundedRect(leftPanel, 16, 16);
    painter.drawRoundedRect(rightPanel, 16, 16);
    painter.drawRoundedRect(bottomPanel, 16, 16);

    painter.setFont(titleFont);
    painter.setPen(QColor(238, 247, 255));
    painter.drawText(QRect(leftPanel.left() + 16, leftPanel.top() + 14, 320, 28),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("深潮回收站 / P9 完成度打磨"));

    painter.setFont(bodyFont);
    painter.setPen(QColor(184, 227, 246));
    painter.drawText(QRect(leftPanel.left() + 16, leftPanel.top() + 44, 340, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("%1 | %2").arg(currentRegion.name, currentRegion.subtitle));

    const QRect healthBarRect(leftPanel.left() + 16, leftPanel.top() + 78, 320, 16);
    const QRect oxygenBarRect(leftPanel.left() + 16, leftPanel.top() + 114, 320, 16);
    painter.setBrush(QColor(24, 39, 56, 220));
    painter.setPen(QPen(QColor(234, 167, 167), 1));
    painter.drawRoundedRect(healthBarRect, 8, 8);
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(255, 108, 108));
    painter.drawRoundedRect(QRect(healthBarRect.left() + 2,
                                  healthBarRect.top() + 2,
                                  static_cast<int>((healthBarRect.width() - 4) * (m_playerHealth / qMax(1.0f, m_playerMaxHealth))),
                                  healthBarRect.height() - 4),
                            6,
                            6);
    painter.setPen(QColor(237, 247, 255));
    painter.drawText(QRect(healthBarRect.left(), healthBarRect.top() - 20, 200, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("艇体：%1 / %2").arg(m_playerHealth, 0, 'f', 1).arg(m_playerMaxHealth, 0, 'f', 1));

    painter.setBrush(QColor(24, 39, 56, 220));
    painter.setPen(QPen(QColor(154, 211, 236), 1));
    painter.drawRoundedRect(oxygenBarRect, 8, 8);
    painter.setPen(Qt::NoPen);
    painter.setBrush(oxygenFillColor);
    painter.drawRoundedRect(QRect(oxygenBarRect.left() + 2,
                                  oxygenBarRect.top() + 2,
                                  static_cast<int>((oxygenBarRect.width() - 4) * m_player.oxygenRatio()),
                                  oxygenBarRect.height() - 4),
                            6,
                            6);
    painter.setPen(QColor(237, 247, 255));
    painter.drawText(QRect(oxygenBarRect.left(), oxygenBarRect.top() - 20, 240, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("氧气：%1 / %2").arg(m_player.oxygen(), 0, 'f', 1).arg(m_player.maxOxygen(), 0, 'f', 1));

    const QStringList leftLines = {
        QStringLiteral("深度：%1 米 / 本轮最深 %2 米").arg(currentDepthMeters(), 0, 'f', 1).arg(m_runMaxDepthMeters, 0, 'f', 1),
        QStringLiteral("货舱：%1 / %2 | 当前背包：%3").arg(m_inventory.cargoUsed()).arg(m_inventory.cargoLimit()).arg(m_inventory.summaryText()),
        QStringLiteral("积分：%1 | 累计收益：%2 | 成功返航：%3").arg(m_credits).arg(m_lifetimeCreditsEarned).arg(m_successfulRuns),
        QStringLiteral("长期材料：%1").arg(formatMaterialStockSummary()),
    };

    int y = leftPanel.top() + 148;
    for (const QString &line : leftLines) {
        painter.drawText(QRect(leftPanel.left() + 16, y, 356, 18), Qt::AlignLeft | Qt::AlignVCenter, line);
        y += 20;
    }

    painter.setFont(sectionFont);
    painter.setPen(QColor(238, 247, 255));
    painter.drawText(QRect(rightPanel.left() + 16, rightPanel.top() + 14, 220, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("任务终端"));
    painter.setFont(bodyFont);
    painter.setPen(QColor(173, 216, 228));
    painter.drawText(QRect(rightPanel.left() + 16, rightPanel.top() + 44, 304, 40),
                     Qt::TextWordWrap,
                     QStringLiteral("主资源：%1\n主要危险：%2").arg(currentRegion.mainResource, currentRegion.mainHazard));
    painter.drawText(QRect(rightPanel.left() + 16, rightPanel.top() + 92, 304, 40),
                     Qt::TextWordWrap,
                     interactionText);
    painter.drawText(QRect(rightPanel.left() + 16, rightPanel.top() + 140, 304, 56),
                     Qt::TextWordWrap,
                     unlockProgress);
    painter.drawText(QRect(rightPanel.left() + 16, rightPanel.top() + 202, 304, 36),
                     Qt::TextWordWrap,
                     QStringLiteral("图鉴发现：%1 / %2 | 音效：%3")
                         .arg(m_discoveredResourceTypes.size())
                         .arg(allResourceTypes().size())
                         .arg(m_soundEnabled ? QStringLiteral("开启") : QStringLiteral("关闭")));

    painter.setFont(sectionFont);
    painter.setPen(QColor(238, 247, 255));
    painter.drawText(QRect(bottomPanel.left() + 16, bottomPanel.top() + 12, 220, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("状态与快捷入口"));

    painter.setFont(bodyFont);
    painter.setPen(cautionColor);
    painter.drawText(QRect(bottomPanel.left() + 16, bottomPanel.top() + 40, bottomPanel.width() - 32, 24),
                     Qt::TextWordWrap,
                     cautionText);
    painter.setPen(QColor(226, 239, 247));
    painter.drawText(QRect(bottomPanel.left() + 16, bottomPanel.top() + 68, bottomPanel.width() - 32, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("返航：进入顶部中间返航回收区 | 调试：F1 切换碰撞框 | 输入：%1").arg(activeInputSummary()));
    painter.drawText(QRect(bottomPanel.left() + 16, bottomPanel.top() + 90, bottomPanel.width() - 32, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("图鉴：Tab | 音效：M | 保存演示存档：F5 | 载入演示存档：F9"));
}

void GameScene::drawSettlementOverlay(QPainter &painter) const
{
    const SeaRegionDefinition selectedRegion = regionDefinition(m_selectedRegion);
    const SeaRegionDefinition thermalFault = regionDefinition(SeaRegionId::ThermalFault);
    const bool selectedUnlocked = isRegionUnlocked(m_selectedRegion);
    const bool thermalKeyDiscovered =
        m_discoveredResourceTypes.contains(static_cast<int>(thermalFault.unlockKeyResource));
    const QString selectedStatus = selectedUnlocked
        ? QStringLiteral("状态：已解锁。按回车、空格或 E 可直接出航。")
        : regionUnlockRequirementText(m_selectedRegion);
    const QString thermalProgress = QStringLiteral("热泉海域进度：累计收益 %1/%2 | 成功返航 %3/%4 | 关键资源 %5")
        .arg(m_lifetimeCreditsEarned)
        .arg(thermalFault.unlockLifetimeCredits)
        .arg(m_successfulRuns)
        .arg(thermalFault.unlockSuccessfulRuns)
        .arg(thermalKeyDiscovered ? QStringLiteral("已带回旧时代零件") : QStringLiteral("尚未带回旧时代零件"));
    const QString terminalStatus = m_statusText.isEmpty() ? thermalProgress : m_statusText;

    painter.save();
    painter.fillRect(rect(), QColor(1, 8, 18, 168));

    const QRect panel(width() / 2 - 410, height() / 2 - 235, 820, 470);
    painter.setPen(QPen(QColor(169, 227, 245), 2));
    painter.setBrush(QColor(8, 24, 39, 236));
    painter.drawRoundedRect(panel, 18, 18);

    QFont titleFont = painter.font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.setPen(QColor(242, 248, 255));
    painter.drawText(panel.adjusted(24, 20, -24, 0),
                     Qt::AlignTop | Qt::AlignHCenter,
                     QStringLiteral("返航结算 / 海域调度 / 升级终端 / P9"));

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);

    painter.setPen(QColor(199, 232, 244));
    painter.drawText(QRect(panel.left() + 28, panel.top() + 62, 250, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("本轮结算"));

    const QStringList settlementLines = {
        QStringLiteral("出航时长：%1").arg(formatDuration(m_lastSettlement.tripDurationMs)),
        QStringLiteral("最深下潜：%1 米").arg(m_lastSettlement.deepestDepthMeters, 0, 'f', 1),
        QStringLiteral("采集总数：%1").arg(m_lastSettlement.totalCollected),
        QStringLiteral("出售资源：%1").arg(m_lastSettlement.soldSummary),
        QStringLiteral("出售收益：+%1 积分").arg(m_lastSettlement.soldValue),
        QStringLiteral("保留材料：%1").arg(m_lastSettlement.retainedSummary),
        QStringLiteral("当前积分：%1").arg(m_credits),
        QStringLiteral("累计收益：%1").arg(m_lifetimeCreditsEarned),
        QStringLiteral("成功返航：%1").arg(m_successfulRuns),
        QStringLiteral("材料库存：%1").arg(formatMaterialStockSummary()),
    };

    int y = panel.top() + 96;
    for (const QString &line : settlementLines) {
        painter.drawText(QRect(panel.left() + 28, y, 330, 24),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         line);
        y += 28;
    }

    painter.setPen(QColor(199, 232, 244));
    painter.drawText(QRect(panel.left() + 380, panel.top() + 62, 360, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("海域选择"));

    painter.setPen(QPen(QColor(117, 194, 214), 1));
    painter.setBrush(QColor(16, 43, 59, 180));
    const QRect regionBox(panel.left() + 380, panel.top() + 92, 390, 152);
    painter.drawRoundedRect(regionBox, 14, 14);

    painter.setPen(QColor(242, 248, 255));
    painter.drawText(regionBox.adjusted(16, 14, -16, 0),
                     Qt::AlignTop | Qt::AlignLeft,
                     QStringLiteral("[左/右] %1").arg(selectedRegion.name));
    painter.setPen(QColor(165, 213, 227));
    painter.drawText(regionBox.adjusted(16, 40, -16, 0),
                     Qt::AlignTop | Qt::AlignLeft,
                     selectedRegion.subtitle);
    painter.drawText(regionBox.adjusted(16, 64, -16, 0),
                     Qt::AlignTop | Qt::AlignLeft,
                     QStringLiteral("主资源：%1 | 主要危险：%2")
                         .arg(selectedRegion.mainResource, selectedRegion.mainHazard));
    painter.drawText(regionBox.adjusted(16, 88, -16, 0),
                     Qt::AlignTop | Qt::AlignLeft,
                     QStringLiteral("推荐深度：%1 米").arg(selectedRegion.recommendedDepthMeters, 0, 'f', 0));
    painter.drawText(QRect(regionBox.left() + 16, regionBox.top() + 112, regionBox.width() - 32, 28),
                     Qt::AlignLeft | Qt::AlignTop | Qt::TextWordWrap,
                     selectedStatus);

    painter.setPen(QColor(199, 232, 244));
    painter.drawText(QRect(panel.left() + 380, panel.top() + 258, 360, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("升级终端"));

    y = panel.top() + 288;
    for (const UpgradeDefinition &definition : upgradeDefinitions()) {
        painter.setPen(QColor(236, 246, 252));
        painter.drawText(QRect(panel.left() + 380, y, 360, 22),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("[%1] %2").arg(definition.hotkey).arg(definition.name));

        painter.setPen(QColor(164, 205, 221));
        painter.drawText(QRect(panel.left() + 380, y + 20, 370, 20),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         definition.description);
        painter.drawText(QRect(panel.left() + 380, y + 40, 370, 20),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         formatUpgradeStatus(definition.type));
        y += 42;
    }

    painter.setPen(QColor(146, 226, 180));
    painter.drawText(QRect(panel.left() + 28, panel.bottom() - 78, panel.width() - 56, 26),
                     Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,
                     m_upgradeFeedbackText.isEmpty()
                         ? QStringLiteral("按左右键切换海域，按 1-5 购买升级，然后按回车、空格或 E 开启下一轮出航。")
                         : m_upgradeFeedbackText);

    painter.setPen(QColor(141, 203, 224));
    painter.drawText(QRect(panel.left() + 28, panel.bottom() - 48, panel.width() - 56, 24),
                     Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWordWrap,
                     terminalStatus);
    painter.drawText(QRect(panel.left() + 28, panel.bottom() - 24, panel.width() - 56, 20),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("图鉴：Tab | 演示存档：F5 保存、F9 载入 | 音效开关：M"));
    painter.restore();
}

void GameScene::drawCodexOverlay(QPainter &painter) const
{
    painter.save();
    painter.fillRect(rect(), QColor(1, 9, 19, 185));

    const QRect panel(width() / 2 - 430, height() / 2 - 250, 860, 500);
    painter.setPen(QPen(QColor(164, 225, 242), 2));
    painter.setBrush(QColor(8, 25, 40, 242));
    painter.drawRoundedRect(panel, 20, 20);

    QFont titleFont = painter.font();
    titleFont.setPointSize(18);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.setPen(QColor(242, 248, 255));
    painter.drawText(QRect(panel.left() + 24, panel.top() + 20, panel.width() - 48, 28),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("资源图鉴与演示存档终端"));

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);
    painter.setPen(QColor(166, 210, 225));
    painter.drawText(QRect(panel.left() + 24, panel.top() + 56, panel.width() - 48, 20),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("已发现 %1 / %2 项资源 | 当前积分 %3 | 长期材料 %4")
                         .arg(m_discoveredResourceTypes.size())
                         .arg(allResourceTypes().size())
                         .arg(m_credits)
                         .arg(formatMaterialStockSummary()));

    const QVector<CodexEntryDefinition> entries = codexEntries();
    int y = panel.top() + 94;
    for (const CodexEntryDefinition &entry : entries) {
        const bool discovered = m_discoveredResourceTypes.contains(static_cast<int>(entry.type));
        const int count = lifetimeCollectedCount(entry.type);
        const int stock = m_materialStock.value(static_cast<int>(entry.type), 0);
        const QRect card(panel.left() + 24, y, panel.width() - 48, 78);

        painter.setPen(QPen(discovered ? entry.accent : QColor(91, 124, 139), 1));
        painter.setBrush(discovered ? QColor(15, 43, 58, 200) : QColor(14, 28, 39, 175));
        painter.drawRoundedRect(card, 14, 14);

        painter.setPen(discovered ? QColor(242, 248, 255) : QColor(164, 184, 195));
        painter.drawText(QRect(card.left() + 16, card.top() + 12, 220, 20),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("%1 | %2").arg(entry.name, entry.category));
        painter.setPen(QColor(177, 214, 227));
        painter.drawText(QRect(card.left() + 16, card.top() + 34, card.width() - 32, 18),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         discovered ? entry.description : entry.discoveryHint);
        painter.drawText(QRect(card.left() + 16, card.top() + 54, card.width() - 32, 16),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("图鉴状态：%1 | 累计收集：%2 | 长期库存：%3")
                             .arg(discovered ? QStringLiteral("已发现") : QStringLiteral("未发现"))
                             .arg(count)
                             .arg(stock));
        y += 88;
    }

    painter.setPen(QColor(144, 203, 223));
    painter.drawText(QRect(panel.left() + 24, panel.bottom() - 62, panel.width() - 48, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("热键：Tab 关闭图鉴 | F5 保存演示存档 | F9 载入演示存档 | M 切换音效"));
    painter.drawText(QRect(panel.left() + 24, panel.bottom() - 38, panel.width() - 48, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("当前音效：%1 | 自动存档：%2")
                         .arg(m_soundEnabled ? QStringLiteral("开启") : QStringLiteral("关闭"))
                         .arg(saveFilePath(false)));
    painter.drawText(QRect(panel.left() + 24, panel.bottom() - 18, panel.width() - 48, 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("演示存档位置：%1").arg(saveFilePath(true)));

    painter.restore();
}

QString GameScene::activeInputSummary() const
{
    QStringList active;
    for (const int key : m_pressedKeys) {
        if (isDirectionalKey(key)) {
            active.push_back(keyToName(key));
        }
    }

    active.sort();
    return active.isEmpty() ? QStringLiteral("无方向输入") : active.join(QStringLiteral("、"));
}

void GameScene::logInputState(const char *action, const int key) const
{
    qCInfo(inputLog).noquote()
        << QStringLiteral("[input] %1 %2 | active = %3")
               .arg(QString::fromLatin1(action), keyToName(key), activeInputSummary());
}
