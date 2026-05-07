#pragma once

#include "inventory.h"
#include "player.h"
#include "resourceitem.h"

#include <QElapsedTimer>
#include <QHash>
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

public:
    struct SettlementReport {
        int totalCollected = 0;
        int soldCount = 0;
        int soldValue = 0;
        int retainedCount = 0;
        float deepestDepthMeters = 0.0f;
        qint64 tripDurationMs = 0;
        QString soldSummary;
        QString retainedSummary;
    };

    enum class UpgradeType {
        OxygenTank,
        Thruster,
        CargoBay,
        RecoveryArm,
        PressureHull,
    };

    struct UpgradeDefinition {
        UpgradeType type;
        int hotkey = 0;
        int maxLevel = 0;
        ResourceItem::Type materialType = ResourceItem::Type::ShellCrystal;
        QVector<int> creditCosts;
        QVector<int> materialCosts;
        QString name;
        QString description;
    };

private:
    void ensurePlayerSpawned();
    void resetRunState();
    void applyPersistentUpgrades();
    void processInput(float dt);
    void updatePlayer(float dt);
    void updateOxygen(float dt);
    void resetResources();
    void updateCollection(float dt);
    void updateRunMetrics(qint64 deltaMs);
    void updateReturnSequence();
    int currentCollectableIndex() const;
    void finishCollection(int resourceIndex);
    void settleCurrentRun();
    void tryPurchaseUpgrade(UpgradeType type);
    float currentDepthRatio() const;
    float currentDepthMeters() const;
    QRectF playAreaRect() const;
    QRectF returnZoneRect() const;
    QVector<QRectF> obstacleRects() const;
    QVector<UpgradeDefinition> upgradeDefinitions() const;
    UpgradeDefinition upgradeDefinition(UpgradeType type) const;
    int upgradeLevel(UpgradeType type) const;
    int currentMaxOxygenValue() const;
    int currentCargoLimitValue() const;
    float currentMoveSpeedValue() const;
    float currentCollectionDurationMultiplier() const;
    float currentOxygenEfficiencyMultiplier() const;
    QString formatDuration(qint64 durationMs) const;
    QString formatResourceCount(ResourceItem::Type type, int count) const;
    QString formatMaterialStockSummary() const;
    QString formatUpgradeEffect(UpgradeType type, int level) const;
    QString formatUpgradeStatus(UpgradeType type) const;
    int sellValueForType(ResourceItem::Type type) const;
    bool isRetainedMaterial(ResourceItem::Type type) const;
    void drawBackground(QPainter &painter) const;
    void drawSeaFloor(QPainter &painter) const;
    void drawObstacles(QPainter &painter) const;
    void drawReturnZone(QPainter &painter) const;
    void drawResources(QPainter &painter) const;
    void drawCollisionDebug(QPainter &painter) const;
    void drawPlayer(QPainter &painter) const;
    void drawHud(QPainter &painter) const;
    void drawSettlementOverlay(QPainter &painter) const;
    QString activeInputSummary() const;
    void logInputState(const char *action, int key) const;

    QTimer *m_timer = nullptr;
    QElapsedTimer m_elapsedTimer;
    QSet<int> m_pressedKeys;
    Player m_player;
    Inventory m_inventory;
    QVector<ResourceItem> m_resources;
    bool m_hasSpawnedPlayer = false;
    bool m_isRunFailed = false;
    bool m_isSettling = false;
    bool m_showCollisionDebug = true;
    int m_collectingResourceIndex = -1;
    int m_credits = 0;
    float m_lastDtSeconds = 0.0f;
    float m_currentCollectProgress = 0.0f;
    float m_lastOxygenCostPerSecond = 0.0f;
    float m_runMaxDepthMeters = 0.0f;
    qint64 m_lastTickMs = 0;
    qint64 m_totalElapsedMs = 0;
    qint64 m_runElapsedMs = 0;
    QString m_assetStatusText;
    QString m_upgradeFeedbackText;
    bool m_assetLayoutReady = false;
    QHash<int, int> m_materialStock;
    QHash<int, int> m_upgradeLevels;
    SettlementReport m_lastSettlement;
};
