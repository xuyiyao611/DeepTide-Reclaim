#pragma once

#include <QPointF>
#include <QRectF>

class Player
{
public:
    enum class OxygenState {
        Safe,
        Warning,
        Danger,
        Empty,
    };

    enum class Facing {
        Left,
        Right,
        Up,
        Down,
    };

    void setPosition(const QPointF &position);
    void setVelocity(const QPointF &velocity);
    void setRadius(float radius);
    void setMoveSpeed(float moveSpeed);
    void setFacing(Facing facing);
    void setOxygen(float oxygen);
    void setMaxOxygen(float maxOxygen);

    QPointF position() const;
    QPointF velocity() const;
    QRectF bounds() const;
    Facing facing() const;
    float radius() const;
    float moveSpeed() const;
    float oxygen() const;
    float maxOxygen() const;
    float oxygenRatio() const;
    OxygenState oxygenState() const;
    bool isMoving() const;

private:
    QPointF m_position {0.0, 0.0};
    QPointF m_velocity {0.0, 0.0};
    float m_radius = 28.0f;
    float m_moveSpeed = 240.0f;
    float m_oxygen = 100.0f;
    float m_maxOxygen = 100.0f;
    Facing m_facing = Facing::Right;
};
