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
        return QStringLiteral("Up");
    case Qt::Key_Down:
        return QStringLiteral("Down");
    case Qt::Key_Left:
        return QStringLiteral("Left");
    case Qt::Key_Right:
        return QStringLiteral("Right");
    case Qt::Key_Space:
        return QStringLiteral("Space");
    case Qt::Key_Escape:
        return QStringLiteral("Esc");
    case Qt::Key_F1:
        return QStringLiteral("F1");
    case Qt::Key_R:
        return QStringLiteral("R");
    default:
        return QStringLiteral("Key(%1)").arg(key);
    }
}

bool isDirectionalKey(const int key)
{
    return key == Qt::Key_W || key == Qt::Key_A || key == Qt::Key_S || key == Qt::Key_D ||
           key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_Left || key == Qt::Key_Right;
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
    ensurePlayerSpawned();

    qCInfo(startupLog) << "[startup] GameScene ready. Timer interval =" << kTargetFrameMs << "ms";
}

void GameScene::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    drawBackground(painter);
    drawSeaFloor(painter);
    drawObstacles(painter);
    drawPlayer(painter);
    if (m_showCollisionDebug) {
        drawCollisionDebug(painter);
    }
    drawHud(painter);
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
        m_player.setMoveSpeed(240.0f);
        m_player.setMaxOxygen(100.0f);
        m_player.setOxygen(m_player.maxOxygen());
        m_hasSpawnedPlayer = true;
    }
}

void GameScene::resetRunState()
{
    m_pressedKeys.clear();
    m_isRunFailed = false;
    m_lastOxygenCostPerSecond = 0.0f;
    m_player.setVelocity(QPointF());
    m_player.setOxygen(m_player.maxOxygen());
    m_hasSpawnedPlayer = false;
    ensurePlayerSpawned();
}

void GameScene::processInput(const float dt)
{
    Q_UNUSED(dt);

    if (m_isRunFailed) {
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
    if (dt <= 0.0f || m_isRunFailed) {
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
            qCInfo(collisionLog).noquote()
                << QStringLiteral("[collision] horizontal hit obstacle at (%1, %2, %3, %4)")
                       .arg(obstacle.left(), 0, 'f', 1)
                       .arg(obstacle.top(), 0, 'f', 1)
                       .arg(obstacle.width(), 0, 'f', 1)
                       .arg(obstacle.height(), 0, 'f', 1);
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
            qCInfo(collisionLog).noquote()
                << QStringLiteral("[collision] vertical hit obstacle at (%1, %2, %3, %4)")
                       .arg(obstacle.left(), 0, 'f', 1)
                       .arg(obstacle.top(), 0, 'f', 1)
                       .arg(obstacle.width(), 0, 'f', 1)
                       .arg(obstacle.height(), 0, 'f', 1);
        }
    }

    m_player.setVelocity(velocity);
    m_player.setPosition(bounds.center());
}

void GameScene::updateOxygen(const float dt)
{
    if (dt <= 0.0f || !m_hasSpawnedPlayer || m_isRunFailed) {
        return;
    }

    const float depthRatio = currentDepthRatio();
    const float moveCost = m_player.isMoving() ? kMoveOxygenCostPerSecond : 0.0f;
    m_lastOxygenCostPerSecond = kBaseOxygenCostPerSecond +
                                depthRatio * kDepthOxygenCostPerSecond +
                                moveCost;

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
                      width(), height() * 0.8);
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

void GameScene::drawCollisionDebug(QPainter &painter) const
{
    painter.save();
    painter.setBrush(Qt::NoBrush);

    painter.setPen(QPen(QColor(255, 223, 125, 200), 2, Qt::DashLine));
    painter.drawRect(playAreaRect());

    painter.setPen(QPen(QColor(255, 114, 114, 220), 2, Qt::DashLine));
    const QVector<QRectF> obstacles = obstacleRects();
    for (const QRectF &rect : obstacles) {
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
    const qreal bob = m_player.isMoving() ? qSin(static_cast<qreal>(m_totalElapsedMs) / 180.0) * 4.0 : qSin(static_cast<qreal>(m_totalElapsedMs) / 320.0) * 2.0;
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
    painter.drawRoundedRect(QRect(kHudPadding, kHudPadding, 420, 272), 14, 14);

    painter.setPen(QColor(237, 247, 255));
    QFont titleFont = painter.font();
    titleFont.setPointSize(15);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(QRect(kHudPadding + 16, kHudPadding + 14, 380, 28),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("深潮回收站 / P3 氧气系统"));

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);

    const QPointF playerPosition = m_player.position();
    const QPointF playerVelocity = m_player.velocity();
    const QRectF area = playAreaRect();
    const QVector<QRectF> obstacles = obstacleRects();

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
    painter.drawRoundedRect(QRect(oxygenBarRect.left() + 2, oxygenBarRect.top() + 2, fillWidth, oxygenBarRect.height() - 4), 6, 6);

    painter.setPen(QColor(237, 247, 255));
    painter.drawText(QRect(oxygenBarRect.left(), oxygenBarRect.top() - 20, oxygenBarRect.width(), 18),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("氧气：%1 / %2").arg(m_player.oxygen(), 0, 'f', 1).arg(m_player.maxOxygen(), 0, 'f', 1));

    const QStringList lines = {
        QStringLiteral("定时刷新：QTimer %1 ms").arg(kTargetFrameMs),
        QStringLiteral("累计运行：%1 ms / dt %.3f s").arg(m_lastTickMs).arg(m_lastDtSeconds, 0, 'f', 3),
        QStringLiteral("当前深度：%1 m / %2 m").arg(currentDepthMeters(), 0, 'f', 1).arg(kMaxDepthMeters, 0, 'f', 0),
        QStringLiteral("玩家位置：(%1, %2)").arg(playerPosition.x(), 0, 'f', 1).arg(playerPosition.y(), 0, 'f', 1),
        QStringLiteral("玩家速度：(%1, %2)").arg(playerVelocity.x(), 0, 'f', 1).arg(playerVelocity.y(), 0, 'f', 1),
        QStringLiteral("氧气消耗：%1 / 秒").arg(m_lastOxygenCostPerSecond, 0, 'f', 2),
        QStringLiteral("障碍数量：%1 / 调试框：%2").arg(obstacles.size()).arg(m_showCollisionDebug ? QStringLiteral("开(F1)") : QStringLiteral("关(F1)")),
        QStringLiteral("当前输入：%1").arg(activeInputSummary()),
        QStringLiteral("提示：越深耗氧越快，氧气耗尽后按 R 重置"),
    };

    int y = kHudPadding + 86;
    for (const QString &line : lines) {
        painter.drawText(QRect(kHudPadding + 16, y, 390, 20), Qt::AlignLeft | Qt::AlignVCenter, line);
        y += 22;
    }

    painter.setBrush(QColor(0, 0, 0, 105));
    painter.drawRoundedRect(QRect(width() - 308, kHudPadding, 290, 164), 14, 14);
    painter.setPen(QColor(184, 227, 246));
    painter.drawText(QRect(width() - 290, kHudPadding + 16, 250, 20),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("P3 验证点"));

    const QStringList checklist = {
        QStringLiteral("1. 氧气持续下降"),
        QStringLiteral("2. 深度影响耗氧"),
        QStringLiteral("3. 低氧颜色预警"),
        QStringLiteral("4. 耗尽后进入失败"),
        QStringLiteral("5. R 可重置出航"),
    };

    y = kHudPadding + 42;
    for (const QString &item : checklist) {
        painter.drawText(QRect(width() - 290, y, 252, 18), Qt::AlignLeft | Qt::AlignVCenter, item);
        y += 20;
    }

    if (m_player.oxygenState() == Player::OxygenState::Warning) {
        painter.setPen(QColor(255, 210, 94));
        painter.drawText(QRect(width() - 290, kHudPadding + 126, 252, 18),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("低氧预警：建议尽快返航"));
    } else if (m_player.oxygenState() == Player::OxygenState::Danger) {
        painter.setPen(QColor(255, 105, 105));
        painter.drawText(QRect(width() - 290, kHudPadding + 126, 252, 18),
                         Qt::AlignLeft | Qt::AlignVCenter,
                         QStringLiteral("危险：氧气极低"));
    } else if (m_isRunFailed) {
        painter.setPen(QColor(255, 105, 105));
        painter.drawText(QRect(width() - 290, kHudPadding + 126, 252, 36),
                         Qt::TextWordWrap,
                         QStringLiteral("任务失败：氧气耗尽\n按 R 重新开始本次出航"));
    }
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
    return active.isEmpty() ? QStringLiteral("无方向输入") : active.join(", ");
}

void GameScene::logInputState(const char *action, const int key) const
{
    qCInfo(inputLog).noquote()
        << QStringLiteral("[input] %1 %2 | active = %3")
               .arg(QString::fromLatin1(action), keyToName(key), activeInputSummary());
}
