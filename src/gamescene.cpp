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

namespace {

constexpr int kTargetFrameMs = 16;
constexpr int kHudPadding = 18;
constexpr float kInputDiagonalFactor = 0.70710678f;
constexpr float kWaterDragFactor = 7.5f;
constexpr float kSpawnXFactor = 0.5f;
constexpr float kSpawnYFactor = 0.42f;

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
    drawPlayer(painter);
    drawHud(painter);
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    if (event->isAutoRepeat()) {
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

    update();
}

void GameScene::ensurePlayerSpawned()
{
    if (width() <= 0 || height() <= 0) {
        return;
    }

    if (!m_hasSpawnedPlayer) {
        m_player.setPosition(QPointF(width() * kSpawnXFactor, height() * kSpawnYFactor));
        m_player.setRadius(28.0f);
        m_player.setMoveSpeed(240.0f);
        m_hasSpawnedPlayer = true;
    }
}

void GameScene::processInput(const float dt)
{
    Q_UNUSED(dt);

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
    if (dt <= 0.0f) {
        return;
    }

    QPointF nextPosition = m_player.position() + m_player.velocity() * dt;
    const float margin = m_player.radius() + 24.0f;

    nextPosition.setX(qBound(margin, static_cast<float>(nextPosition.x()), static_cast<float>(width()) - margin));
    nextPosition.setY(qBound(margin, static_cast<float>(nextPosition.y()), static_cast<float>(height()) - margin));
    m_player.setPosition(nextPosition);
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
}

void GameScene::drawHud(QPainter &painter) const
{
    painter.setPen(Qt::NoPen);
    painter.setBrush(QColor(0, 0, 0, 110));
    painter.drawRoundedRect(QRect(kHudPadding, kHudPadding, 420, 170), 14, 14);

    painter.setPen(QColor(237, 247, 255));
    QFont titleFont = painter.font();
    titleFont.setPointSize(15);
    titleFont.setBold(true);
    painter.setFont(titleFont);
    painter.drawText(QRect(kHudPadding + 16, kHudPadding + 14, 380, 28),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("深潮回收站 / P1 玩家移动"));

    QFont bodyFont = painter.font();
    bodyFont.setPointSize(10);
    bodyFont.setBold(false);
    painter.setFont(bodyFont);

    const QPointF playerPosition = m_player.position();
    const QPointF playerVelocity = m_player.velocity();

    const QStringList lines = {
        QStringLiteral("定时刷新：QTimer %1 ms").arg(kTargetFrameMs),
        QStringLiteral("累计运行：%1 ms / dt %.3f s").arg(m_lastTickMs).arg(m_lastDtSeconds, 0, 'f', 3),
        QStringLiteral("资源检查：%1").arg(m_assetLayoutReady ? QStringLiteral("通过") : QStringLiteral("异常")),
        QStringLiteral("玩家位置：(%1, %2)").arg(playerPosition.x(), 0, 'f', 1).arg(playerPosition.y(), 0, 'f', 1),
        QStringLiteral("玩家速度：(%1, %2)").arg(playerVelocity.x(), 0, 'f', 1).arg(playerVelocity.y(), 0, 'f', 1),
        QStringLiteral("当前输入：%1").arg(activeInputSummary()),
        QStringLiteral("提示：点击窗口后按 WASD / 方向键，观察潜水器移动"),
    };

    int y = kHudPadding + 52;
    for (const QString &line : lines) {
        painter.drawText(QRect(kHudPadding + 16, y, 390, 20), Qt::AlignLeft | Qt::AlignVCenter, line);
        y += 22;
    }

    painter.setBrush(QColor(0, 0, 0, 105));
    painter.drawRoundedRect(QRect(width() - 308, kHudPadding, 290, 138), 14, 14);
    painter.setPen(QColor(184, 227, 246));
    painter.drawText(QRect(width() - 290, kHudPadding + 16, 250, 20),
                     Qt::AlignLeft | Qt::AlignVCenter,
                     QStringLiteral("P1 验证点"));

    const QStringList checklist = {
        QStringLiteral("1. 玩家能持续移动"),
        QStringLiteral("2. 松开按键能停下"),
        QStringLiteral("3. 斜向输入可预测"),
        QStringLiteral("4. HUD 显示位置速度"),
        QStringLiteral("5. 出生点稳定一致"),
    };

    y = kHudPadding + 42;
    for (const QString &item : checklist) {
        painter.drawText(QRect(width() - 290, y, 252, 18), Qt::AlignLeft | Qt::AlignVCenter, item);
        y += 20;
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
