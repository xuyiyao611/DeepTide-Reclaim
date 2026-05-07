#include "resourceitem.h"

ResourceItem::ResourceItem(const Type type,
                           const CollectMode collectMode,
                           const QPointF &position,
                           const float radius,
                           const float collectDurationSeconds,
                           const int cargoCost)
    : m_type(type),
      m_collectMode(collectMode),
      m_position(position),
      m_radius(radius),
      m_collectDurationSeconds(collectDurationSeconds),
      m_cargoCost(cargoCost)
{
}

ResourceItem::Type ResourceItem::type() const
{
    return m_type;
}

ResourceItem::CollectMode ResourceItem::collectMode() const
{
    return m_collectMode;
}

QPointF ResourceItem::position() const
{
    return m_position;
}

QRectF ResourceItem::bounds() const
{
    return QRectF(m_position.x() - m_radius,
                  m_position.y() - m_radius,
                  m_radius * 2.0,
                  m_radius * 2.0);
}

float ResourceItem::radius() const
{
    return m_radius;
}

float ResourceItem::collectDurationSeconds() const
{
    return m_collectDurationSeconds;
}

int ResourceItem::cargoCost() const
{
    return m_cargoCost;
}

QString ResourceItem::displayName() const
{
    switch (m_type) {
    case Type::GlowCluster:
        return QStringLiteral("荧团浮体");
    case Type::ShellCrystal:
        return QStringLiteral("壳晶矿");
    case Type::ColdGel:
        return QStringLiteral("冷凝胶");
    case Type::OldPart:
        return QStringLiteral("旧时代零件");
    }

    return QStringLiteral("未知资源");
}

QColor ResourceItem::color() const
{
    switch (m_type) {
    case Type::GlowCluster:
        return QColor(128, 243, 255);
    case Type::ShellCrystal:
        return QColor(146, 227, 152);
    case Type::ColdGel:
        return QColor(132, 177, 255);
    case Type::OldPart:
        return QColor(255, 184, 92);
    }

    return QColor(255, 255, 255);
}
