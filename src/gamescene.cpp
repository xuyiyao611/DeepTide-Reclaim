#include "gamescene.h"

#include "projectpaths.h"

#include <QKeyEvent>
#include <QLoggingCategory>
#include <QPainter>
#include <QPainterPath>
#include <QTimer>
#include <QtMath>

Q_LOGGING_CATEGORY(startupLog, "deep_tide.startup")
Q_LOGGING_CATEGORY(resourceLog, "deep_tide.resource")
Q_LOGGING_CATEGORY(inputLog, "deep_tide.input")
Q_LOGGING_CATEGORY(collisionLog, "deep_tide.collision")
Q_LOGGING_CATEGORY(oxygenLog, "deep_tide.oxygen")
Q_LOGGING_CATEGORY(collectLog, "deep_tide.collect")
Q_LOGGING_CATEGORY(settlementLog, "deep_tide.settlement")
Q_LOGGING_CATEGORY(upgradeLog, "deep_tide.upgrade")

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
    case Qt::Key_R:
        return QStringLiteral("R");
    case Qt::Key_E:
        return QStringLiteral("E");
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

    applyPersistentUpgrades();
    ensurePlayerSpawned();
    resetResources();

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
    drawResources(painter);
    drawPlayer(painter);
    if (m_showCollisionDebug) {
        drawCollisionDebug(painter);
    }
    drawHud(painter);
    if (m_isSettling) {
        drawSettlementOverlay(painter);
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

    if (m_isSettling) {
        if (isUpgradeHotkey(event->key())) {
            tryPurchaseUpgrade(upgradeTypeForKey(event->key()));
        } else if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter ||
                   event->key() == Qt::Key_Space || event->key() == Qt::Key_E) {
            m_isSettling = false;
            resetRunState();
            qCInfo(settlementLog) << "[settlement] settlement closed, next run started.";
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

    ensurePlayerSpawned();
    processInput(m_lastDtSeconds);
    updatePlayer(m_lastDtSeconds);
    updateOxygen(m_lastDtSeconds);
    updateCollection(m_lastDtSeconds);
    updateRunMetrics(deltaMs);
    updateReturnSequence();

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
    m_collectingResourceIndex = -1;
    m_lastSettlement = {};
    m_currentCollectProgress = 0.0f;
    m_lastOxygenCostPerSecond = 0.0f;
    m_runElapsedMs = 0;
    m_runMaxDepthMeters = 0.0f;
    m_upgradeFeedbackText.clear();
    m_player.setVelocity(QPointF());
    m_player.setOxygen(m_player.maxOxygen());
    m_inventory.reset();
    m_hasSpawnedPlayer = false;
    ensurePlayerSpawned();
    resetResources();
}

void GameScene::applyPersistentUpgrades()
{
    m_inventory.setCargoLimit(currentCargoLimitValue());
    m_player.setMoveSpeed(currentMoveSpeedValue());
    m_player.setMaxOxygen(static_cast<float>(currentMaxOxygenValue()));
    if (!m_isRunFailed) {
        m_player.setOxygen(m_player.maxOxygen());
    }
}

void GameScene::processInput(const float dt)
{
    Q_UNUSED(dt);

    if (m_isRunFailed || m_isSettling) {
        m_player.setVelocity(QPointF());
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
    if (dt <= 0.0f || m_isRunFailed || m_isSettling) {
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
    if (dt <= 0.0f || !m_hasSpawnedPlayer || m_isRunFailed || m_isSettling) {
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
        qCWarning(oxygenLog).noquote()
            << QStringLiteral("[oxygen] depleted at depth=%1m after %2ms")
                   .arg(currentDepthMeters(), 0, 'f', 1)
                   .arg(m_totalElapsedMs);
    }
}

void GameScene::resetResources()
{
    const QRectF area = playAreaRect();
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

void GameScene::updateRunMetrics(const qint64 deltaMs)
{
    if (!m_hasSpawnedPlayer || m_isRunFailed || m_isSettling || deltaMs <= 0) {
        return;
    }

    m_runElapsedMs += deltaMs;
    m_runMaxDepthMeters = qMax(m_runMaxDepthMeters, currentDepthMeters());
}

void GameScene::updateReturnSequence()
{
    if (!m_hasSpawnedPlayer || m_isRunFailed || m_isSettling) {
        return;
    }

    if (m_player.bounds().intersects(returnZoneRect())) {
        settleCurrentRun();
    }
}

void GameScene::updateCollection(const float dt)
{
    if (m_isRunFailed || m_isSettling) {
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

    QStringList soldParts;
    QStringList retainedParts;

    for (const ResourceItem::Type type : allResourceTypes()) {
        const int count = m_inventory.count(type);
        if (count <= 0) {
            continue;
        }

        if (isRetainedMaterial(type)) {
            m_materialStock[static_cast<int>(type)] += count;
            report.retainedCount += count;
            retainedParts.push_back(formatResourceCount(type, count));
        } else {
            const int soldValue = sellValueForType(type) * count;
            m_credits += soldValue;
            report.soldCount += count;
            report.soldValue += soldValue;
            soldParts.push_back(QStringLiteral("%1（+%2积分）").arg(formatResourceCount(type, count)).arg(soldValue));
        }
    }

    report.soldSummary = soldParts.isEmpty() ? QStringLiteral("无可出售资源") : soldParts.join(QStringLiteral(" / "));
    report.retainedSummary = retainedParts.isEmpty() ? QStringLiteral("无新增材料") : retainedParts.join(QStringLiteral(" / "));

    m_lastSettlement = report;
    m_isSettling = true;
    m_upgradeFeedbackText = QStringLiteral("按 1-5 购买升级，然后按回车、空格或 E 开启下一轮出航。");
    m_collectingResourceIndex = -1;
    m_currentCollectProgress = 0.0f;
    m_player.setVelocity(QPointF());
    m_pressedKeys.clear();

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

    qCInfo(upgradeLog).noquote()
        << QStringLiteral("[upgrade] %1 -> level %2 | credits=%3")
               .arg(definition.name)
               .arg(nextLevel)
               .arg(m_credits);
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
    return currentDepthRatio() * kMaxDepthMeters;
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
    QLinearGradient gradient(rect().topLeft(), rect().bottomLeft());
    gradient.setColorAt(0.0, QColor(6, 29, 64));
    gradient.setColorAt(0.35, QColor(10, 53, 94));
    gradient.setColorAt(1.0, QColor(3, 13, 28));
    painter.fillRect(rect(), gradient);

    painter.setPen(Qt::NoPen);
    for (int i = 0; i < 12; ++i) {
        const int x = (i * width()) / 11;
        const int bob = static_cast<int>((m_totalElapsedMs / 35 + i * 13) % 28);
        painter.setBrush(QColor(122, 216, 255, 35));
        painter.drawEllipse(QPointF(x, 90 + bob), 4.0, 4.0);
    }
}

void GameScene::drawSeaFloor(QPainter &painter) const
{
    QPainterPath floorPath;
    floorPath.moveTo(0.0, height() * 0.82);
    floorPath.cubicTo(width() * 0.25, height() * 0.74,
                      width() * 0.65, height() * 0.92,
                      width(), height() * 0.80);
    floorPath.lineTo(width(), height());
    floorPath.lineTo(0.0, height());
    floorPath.closeSubpath();

    painter.fillPath(floorPath, QColor(26, 44, 41));
    painter.setPen(QPen(QColor(86, 126, 118), 2));
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

    if (m_isRunFailed) {
        painter.setPen(QPen(QColor(255, 112, 112), 3));
        painter.drawEllipse(QPointF(centerX, baseY + bob), 88.0, 42.0);
    }
}

void GameScene::drawHud(QPainter &painter) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 110));
    painter.drawRoundedRect(QRect(kHudPadding, kHudPadding, 446, 318), 14, 14);

    painter.setPen(QColor(237, 247, 255));
    QFont titleFont = painter.font();
    titleFont.setPointSize(15);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(QRect(kHudPadding + 16, kHudPadding + 14, 410, 28),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("深潮回收站 / P6 升级系统"));

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);

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

    const QRect oxygenBarRect(kHudPadding + 16, kHudPadding + 52, 388, 18);
    painter.setBrush(QColor(23, 37, 49, 220));
    painter.setPen(QPen(QColor(154, 211, 236), 1));
    painter.drawRoundedRect(oxygenBarRect, 8, 8);

    const int fillWidth = static_cast<int>((oxygenBarRect.width() - 4) * m_player.oxygenRatio());
    painter.setPen(Qt::NoPen);
    painter.setBrush(oxygenFillColor);
    painter.drawRoundedRect(QRect(oxygenBarRect.left() + 2,
                                  oxygenBarRect.top() + 2,
                                  fillWidth,
                                  oxygenBarRect.height() - 4),
                            6,
                            6);

    painter.setPen(QColor(237, 247, 255));
    painter.drawText(QRect(oxygenBarRect.left(), oxygenBarRect.top() - 20, oxygenBarRect.width(), 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("氧气：%1 / %2")
                         .arg(m_player.oxygen(), 0, 'f', 1)
                         .arg(m_player.maxOxygen(), 0, 'f', 1));

    QString interactionText = QStringLiteral("附近资源：无");
    const int activeResourceIndex = currentCollectableIndex();
    if (activeResourceIndex >= 0) {
        const ResourceItem &resource = m_resources.at(activeResourceIndex);
        interactionText = QStringLiteral("附近资源：%1 / %2")
                              .arg(resource.displayName(),
                                   resource.collectMode() == ResourceItem::CollectMode::Instant
                                       ? QStringLiteral("按 E 回收")
                                       : QStringLiteral("按住 E 采集"));
    }

    const QStringList lines = {
        QStringLiteral("刷新频率：QTimer %1 ms").arg(kTargetFrameMs),
        QStringLiteral("本轮时长：%1 / 帧间隔 %2 s").arg(formatDuration(m_runElapsedMs)).arg(m_lastDtSeconds, 0, 'f', 3),
        QStringLiteral("当前深度：%1 m / 最深 %2 m").arg(currentDepthMeters(), 0, 'f', 1).arg(m_runMaxDepthMeters, 0, 'f', 1),
        QStringLiteral("玩家位置：(%1, %2)").arg(m_player.position().x(), 0, 'f', 1).arg(m_player.position().y(), 0, 'f', 1),
        QStringLiteral("玩家速度：(%1, %2)").arg(m_player.velocity().x(), 0, 'f', 1).arg(m_player.velocity().y(), 0, 'f', 1),
        QStringLiteral("氧气消耗：%1 / 秒").arg(m_lastOxygenCostPerSecond, 0, 'f', 2),
        QStringLiteral("货舱：%1 / %2").arg(m_inventory.cargoUsed()).arg(m_inventory.cargoLimit()),
        QStringLiteral("本轮背包：%1").arg(m_inventory.summaryText()),
        QStringLiteral("累计积分：%1").arg(m_credits),
        QStringLiteral("长期材料：%1").arg(formatMaterialStockSummary()),
        interactionText,
        QStringLiteral("当前输入：%1").arg(activeInputSummary()),
        QStringLiteral("返航方式：进入顶部中间的返航回收区"),
        QStringLiteral("升级入口：返航结算后按 1-5 购买升级"),
    };

    int y = kHudPadding + 86;
    for (const QString &line : lines) {
        painter.drawText(QRect(kHudPadding + 16, y, 412, 20), Qt::AlignLeft | Qt::AlignVCenter, line);
        y += 22;
    }

    painter.setBrush(QColor(0, 0, 0, 105));
    painter.drawRoundedRect(QRect(width() - 328, kHudPadding, 310, 252), 14, 14);
    painter.setPen(QColor(184, 227, 246));
    painter.drawText(QRect(width() - 310, kHudPadding + 16, 270, 20),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("P6 验证点"));

    const QStringList checklist = {
        QStringLiteral("1. 存活返航后会打开结算与升级面板"),
        QStringLiteral("2. 升级会消耗积分和长期材料"),
        QStringLiteral("3. 升级后下一轮属性立即生效"),
        QStringLiteral("4. 升满后不能继续购买"),
        QStringLiteral("5. 结算与升级界面不会继续耗氧"),
    };

    y = kHudPadding + 42;
    for (const QString &item : checklist) {
        painter.drawText(QRect(width() - 310, y, 272, 18), Qt::AlignLeft | Qt::AlignVCenter, item);
        y += 20;
    }

    if (activeResourceIndex >= 0) {
        const ResourceItem &resource = m_resources.at(activeResourceIndex);
        if (resource.collectMode() == ResourceItem::CollectMode::Hold) {
            const float duration = qMax(0.001f, resource.collectDurationSeconds() * currentCollectionDurationMultiplier());
            const float progressRatio = qBound(0.0f, m_currentCollectProgress / duration, 1.0f);
            const QRect progressRect(width() - 310, kHudPadding + 146, 250, 14);

            painter.setPen(QPen(QColor(144, 186, 193), 1));
            painter.setBrush(QColor(23, 37, 49, 220));
            painter.drawRoundedRect(progressRect, 6, 6);

            painter.setPen(Qt::NoPen);
            painter.setBrush(QColor(104, 225, 173));
            painter.drawRoundedRect(QRect(progressRect.left() + 2,
                                          progressRect.top() + 2,
                                          static_cast<int>((progressRect.width() - 4) * progressRatio),
                                          progressRect.height() - 4),
                                    5,
                                    5);

            painter.setPen(QColor(230, 243, 247));
            painter.drawText(QRect(width() - 310, kHudPadding + 166, 270, 20),
                             Qt::AlignLeft | Qt::AlignVCenter,
                             QStringLiteral("采集进度：%1%").arg(static_cast<int>(progressRatio * 100.0f)));
        }
    } else if (m_inventory.remainingCapacity() <= 0) {
        painter.setPen(QColor(255, 149, 149));
        painter.drawText(QRect(width() - 310, kHudPadding + 146, 272, 36),
                         Qt::TextWordWrap,
                         QStringLiteral("货舱已满：可以直接返航完成本轮结算。"));
    }

    if (m_player.oxygenState() == Player::OxygenState::Warning) {
        painter.setPen(QColor(255, 210, 94));
        painter.drawText(QRect(width() - 310, kHudPadding + 190, 272, 18),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("低氧预警：建议尽快上浮返航。"));
    } else if (m_player.oxygenState() == Player::OxygenState::Danger) {
        painter.setPen(QColor(255, 105, 105));
        painter.drawText(QRect(width() - 310, kHudPadding + 190, 272, 18),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("危险：氧气极低，返航优先级最高。"));
    } else if (m_isRunFailed) {
        painter.setPen(QColor(255, 105, 105));
        painter.drawText(QRect(width() - 310, kHudPadding + 190, 272, 42),
                         Qt::TextWordWrap,
                         QStringLiteral("任务失败：氧气耗尽，本轮货物丢失。\n按 R 重新开始本轮出航。"));
    } else if (m_isSettling) {
        painter.setPen(QColor(148, 241, 188));
        painter.drawText(QRect(width() - 310, kHudPadding + 190, 272, 42),
                         Qt::TextWordWrap,
                         QStringLiteral("返航成功：已进入结算与升级阶段。\n按 1-5 升级，按回车、空格或 E 出航。"));
    }

    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 120));
    painter.drawRoundedRect(QRect(kHudPadding, height() - 136, 650, 110), 14, 14);

    painter.setPen(QColor(238, 247, 255));
    painter.drawText(QRect(kHudPadding + 16, height() - 126, 620, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("当前长期属性"));

    const QString returnState = m_isSettling
        ? QStringLiteral("已返航：可以购买升级，再按回车、空格或 E 开启下一轮。")
        : (m_player.bounds().intersects(returnZoneRect()) && !m_isRunFailed
               ? QStringLiteral("已进入返航区：正在准备结算。")
               : QStringLiteral("目标：保持存活并进入顶部中间返航回收区。"));
    const QString persistentState = QStringLiteral("积分：%1 | 材料：%2")
                                        .arg(m_credits)
                                        .arg(formatMaterialStockSummary());
    const QString runState = QStringLiteral("货舱上限：%1 | 最大氧气：%2 | 移动速度：%3")
                                 .arg(currentCargoLimitValue())
                                 .arg(currentMaxOxygenValue())
                                 .arg(currentMoveSpeedValue(), 0, 'f', 0);
    const QString ruleState = QStringLiteral("采集耗时倍率：x%1 | 氧气消耗倍率：x%2")
                                  .arg(currentCollectionDurationMultiplier(), 0, 'f', 2)
                                  .arg(currentOxygenEfficiencyMultiplier(), 0, 'f', 2);

    painter.drawText(QRect(kHudPadding + 16, height() - 100, 620, 18), Qt::AlignLeft | Qt::AlignVCenter, returnState);
    painter.drawText(QRect(kHudPadding + 16, height() - 78, 620, 18), Qt::AlignLeft | Qt::AlignVCenter, persistentState);
    painter.drawText(QRect(kHudPadding + 16, height() - 56, 620, 18), Qt::AlignLeft | Qt::AlignVCenter, runState);
    painter.drawText(QRect(kHudPadding + 16, height() - 34, 620, 18), Qt::AlignLeft | Qt::AlignVCenter, ruleState);
}

void GameScene::drawSettlementOverlay(QPainter &painter) const
{
    painter.save();
    painter.fillRect(rect(), QColor(1, 8, 18, 168));

    const QRect panel(width() / 2 - 380, height() / 2 - 220, 760, 440);
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
                     QStringLiteral("返航结算与升级终端"));

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
        QStringLiteral("累计积分：%1").arg(m_credits),
        QStringLiteral("材料库存：%1").arg(formatMaterialStockSummary()),
    };

    int y = panel.top() + 96;
    for (const QString &line : settlementLines) {
        painter.drawText(QRect(panel.left() + 28, y, 320, 24),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         line);
        y += 28;
    }

    painter.setPen(QColor(199, 232, 244));
    painter.drawText(QRect(panel.left() + 382, panel.top() + 62, 320, 22),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("升级终端"));

    y = panel.top() + 96;
    for (const UpgradeDefinition &definition : upgradeDefinitions()) {
        painter.setPen(QColor(236, 246, 252));
        painter.drawText(QRect(panel.left() + 382, y, 320, 22),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("[%1] %2").arg(definition.hotkey).arg(definition.name));

        painter.setPen(QColor(164, 205, 221));
        painter.drawText(QRect(panel.left() + 382, y + 20, 340, 20),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         definition.description);
        painter.drawText(QRect(panel.left() + 382, y + 40, 340, 20),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         formatUpgradeStatus(definition.type));
        y += 70;
    }

    painter.setPen(QColor(146, 226, 180));
    painter.drawText(QRect(panel.left() + 28, panel.bottom() - 70, panel.width() - 56, 24),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     m_upgradeFeedbackText.isEmpty()
                         ? QStringLiteral("按 1-5 购买升级，然后按回车、空格或 E 开启下一轮出航。")
                         : m_upgradeFeedbackText);

    painter.setPen(QColor(141, 203, 224));
    painter.drawText(QRect(panel.left() + 28, panel.bottom() - 42, panel.width() - 56, 24),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("可见升级效果：氧气上限、移动速度、货舱容量、采集效率、氧气消耗。"));
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
