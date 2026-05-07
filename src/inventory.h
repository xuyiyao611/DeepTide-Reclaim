#pragma once

#include "resourceitem.h"

#include <QHash>
#include <QStringList>

class Inventory
{
public:
    void reset();
    void setCargoLimit(int cargoLimit);
    int cargoLimit() const;
    int cargoUsed() const;
    int remainingCapacity() const;
    bool canStore(const ResourceItem &item) const;
    bool add(const ResourceItem &item);
    int count(ResourceItem::Type type) const;
    int totalItemCount() const;
    QString summaryText() const;

private:
    int m_cargoLimit = 10;
    int m_cargoUsed = 0;
    QHash<int, int> m_counts;
};
