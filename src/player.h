#pragma once

#include <QPointF>
#include <QRectF>

class Player
{
public:
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

    QPointF position() const;
    QPointF velocity() const;
    QRectF bounds() const;
    Facing facing() const;
    float radius() const;
    float moveSpeed() const;
    bool isMoving() const;

private:
    QPointF m_position {0.0, 0.0};
    QPointF m_velocity {0.0, 0.0};
    float m_radius = 28.0f;
    float m_moveSpeed = 240.0f;
    Facing m_facing = Facing::Right;
};
