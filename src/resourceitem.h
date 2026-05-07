#pragma once

#include <QColor>
#include <QPointF>
#include <QRectF>
#include <QString>

class ResourceItem
{
public:
    enum class Type {
        GlowCluster,
        ShellCrystal,
        ColdGel,
        OldPart,
    };

    enum class CollectMode {
        Instant,
        Hold,
    };

    ResourceItem() = default;
    ResourceItem(Type type,
                 CollectMode collectMode,
                 const QPointF &position,
                 float radius,
                 float collectDurationSeconds,
                 int cargoCost);

    Type type() const;
    CollectMode collectMode() const;
    QPointF position() const;
    QRectF bounds() const;
    float radius() const;
    float collectDurationSeconds() const;
    int cargoCost() const;
    QString displayName() const;
    QColor color() const;

private:
    Type m_type = Type::GlowCluster;
    CollectMode m_collectMode = CollectMode::Instant;
    QPointF m_position {0.0, 0.0};
    float m_radius = 12.0f;
    float m_collectDurationSeconds = 0.0f;
    int m_cargoCost = 1;
};
