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

    struct HazardCreature {
        enum class State {
            Patrol,
            Alert,
            Cooldown,
        };

        QString name;
        QPointF anchor;
        QPointF position;
        QPointF velocity;
        float radius = 24.0f;
        float patrolRange = 80.0f;
        float detectRange = 180.0f;
        float speed = 120.0f;
        float attackRange = 36.0f;
        qint64 cooldownMs = 0;
        bool patrolForward = true;
        State state = State::Patrol;
    };

    struct HazardZone {
        QString name;
        QRectF rect;
        float oxygenDrainPerSecond = 0.0f;
        float damagePerSecond = 0.0f;
        float pushStrength = 0.0f;
    };

private:
    void ensurePlayerSpawned();
    void resetRunState();
    void applyPersistentUpgrades();
    void processInput(float dt);
    void updatePlayer(float dt);
    void updateOxygen(float dt);
    void resetResources();
    void resetHazards();
    void updateCollection(float dt);
    void updateRunMetrics(qint64 deltaMs);
    void updateDamageState(float dt);
    void updateHazards(float dt);
    void updateHazardCreatures(float dt);
    void updateHazardZones(float dt);
    void updateReturnSequence();
    int currentCollectableIndex() const;
    void finishCollection(int resourceIndex);
    void settleCurrentRun();
    void tryPurchaseUpgrade(UpgradeType type);
    void applyDamage(float damage,
                     float oxygenDamage,
                     const QPointF &knockbackDirection,
                     float knockbackStrength,
                     const QString &reason);
    bool isRunLocked() const;
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
    QString hazardStateText(const HazardCreature &creature) const;
    QString failureReasonText() const;
    int sellValueForType(ResourceItem::Type type) const;
    bool isRetainedMaterial(ResourceItem::Type type) const;
    void drawBackground(QPainter &painter) const;
    void drawSeaFloor(QPainter &painter) const;
    void drawObstacles(QPainter &painter) const;
    void drawReturnZone(QPainter &painter) const;
    void drawHazards(QPainter &painter) const;
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
    QVector<HazardCreature> m_hazardCreatures;
    QVector<HazardZone> m_hazardZones;
    bool m_hasSpawnedPlayer = false;
    bool m_isRunFailed = false;
    bool m_isSettling = false;
    bool m_showCollisionDebug = true;
    int m_collectingResourceIndex = -1;
    int m_credits = 0;
    float m_playerHealth = 100.0f;
    float m_playerMaxHealth = 100.0f;
    float m_lastDtSeconds = 0.0f;
    float m_currentCollectProgress = 0.0f;
    float m_lastOxygenCostPerSecond = 0.0f;
    float m_damageFlashSeconds = 0.0f;
    float m_invulnerabilitySeconds = 0.0f;
    float m_controlLockSeconds = 0.0f;
    float m_runMaxDepthMeters = 0.0f;
    qint64 m_lastTickMs = 0;
    qint64 m_totalElapsedMs = 0;
    qint64 m_runElapsedMs = 0;
    QString m_assetStatusText;
    QString m_upgradeFeedbackText;
    QString m_lastDamageReason;
    bool m_assetLayoutReady = false;
    QHash<int, int> m_materialStock;
    QHash<int, int> m_upgradeLevels;
    SettlementReport m_lastSettlement;
};
