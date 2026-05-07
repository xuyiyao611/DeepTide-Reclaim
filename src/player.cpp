#include "player.h"

#include <QtMath>

void Player::setPosition(const QPointF &position)
{
    m_position = position;
}

void Player::setVelocity(const QPointF &velocity)
{
    m_velocity = velocity;
}

void Player::setRadius(const float radius)
{
    m_radius = radius;
}

void Player::setMoveSpeed(const float moveSpeed)
{
    m_moveSpeed = moveSpeed;
}

void Player::setFacing(const Facing facing)
{
    m_facing = facing;
}

QPointF Player::position() const
{
    return m_position;
}

QPointF Player::velocity() const
{
    return m_velocity;
}

QRectF Player::bounds() const
{
    return QRectF(m_position.x() - m_radius,
                  m_position.y() - m_radius,
                  m_radius * 2.0,
                  m_radius * 2.0);
}

Player::Facing Player::facing() const
{
    return m_facing;
}

float Player::radius() const
{
    return m_radius;
}

float Player::moveSpeed() const
{
    return m_moveSpeed;
}

bool Player::isMoving() const
{
    return !qFuzzyIsNull(m_velocity.x()) || !qFuzzyIsNull(m_velocity.y());
}
