#pragma once

#include "player.h"

#include <QElapsedTimer>
#include <QRectF>
#include <QSet>
#include <QVector>
#include <QWidget>

class QKeyEvent;
class QPaintEvent;
class QTimer;

class GameScene : public QWidget
{
    Q_OBJECT

public:
    explicit GameScene(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

private slots:
    void tick();

private:
    void ensurePlayerSpawned();
    void processInput(float dt);
    void updatePlayer(float dt);
    QRectF playAreaRect() const;
    QVector<QRectF> obstacleRects() const;
    void drawBackground(QPainter &painter) const;
    void drawSeaFloor(QPainter &painter) const;
    void drawObstacles(QPainter &painter) const;
    void drawCollisionDebug(QPainter &painter) const;
    void drawPlayer(QPainter &painter) const;
    void drawHud(QPainter &painter) const;
    QString activeInputSummary() const;
    void logInputState(const char *action, int key) const;

    QTimer *m_timer = nullptr;
    QElapsedTimer m_elapsedTimer;
    QSet<int> m_pressedKeys;
    Player m_player;
    bool m_hasSpawnedPlayer = false;
    bool m_showCollisionDebug = true;
    float m_lastDtSeconds = 0.0f;
    qint64 m_lastTickMs = 0;
    qint64 m_totalElapsedMs = 0;
    QString m_assetStatusText;
    bool m_assetLayoutReady = false;
};
