#include "inventory.h"

void Inventory::reset()
{
    m_cargoUsed = 0;
    m_counts.clear();
}

void Inventory::setCargoLimit(const int cargoLimit)
{
    m_cargoLimit = qMax(1, cargoLimit);
    m_cargoUsed = qMin(m_cargoUsed, m_cargoLimit);
}

int Inventory::cargoLimit() const
{
    return m_cargoLimit;
}

int Inventory::cargoUsed() const
{
    return m_cargoUsed;
}

int Inventory::remainingCapacity() const
{
    return m_cargoLimit - m_cargoUsed;
}

bool Inventory::canStore(const ResourceItem &item) const
{
    return m_cargoUsed + item.cargoCost() <= m_cargoLimit;
}

bool Inventory::add(const ResourceItem &item)
{
    if (!canStore(item)) {
        return false;
    }

    m_cargoUsed += item.cargoCost();
    m_counts[static_cast<int>(item.type())] += 1;
    return true;
}

int Inventory::count(const ResourceItem::Type type) const
{
    return m_counts.value(static_cast<int>(type), 0);
}

int Inventory::totalItemCount() const
{
    int total = 0;
    for (auto it = m_counts.constBegin(); it != m_counts.constEnd(); ++it) {
        total += it.value();
    }
    return total;
}

QString Inventory::summaryText() const
{
    QStringList parts;

    const int glow = count(ResourceItem::Type::GlowCluster);
    const int shell = count(ResourceItem::Type::ShellCrystal);
    const int gel = count(ResourceItem::Type::ColdGel);
    const int oldPart = count(ResourceItem::Type::OldPart);

    if (glow > 0) {
        parts.push_back(QStringLiteral("荧团浮体x%1").arg(glow));
    }
    if (shell > 0) {
        parts.push_back(QStringLiteral("壳晶石x%1").arg(shell));
    }
    if (gel > 0) {
        parts.push_back(QStringLiteral("冷凝胶x%1").arg(gel));
    }
    if (oldPart > 0) {
        parts.push_back(QStringLiteral("旧时代零件x%1").arg(oldPart));
    }

    return parts.isEmpty() ? QStringLiteral("空背包") : parts.join(QStringLiteral(" / "));
}
