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

void Player::setOxygen(const float oxygen)
{
    m_oxygen = qBound(0.0f, oxygen, m_maxOxygen);
}

void Player::setMaxOxygen(const float maxOxygen)
{
    m_maxOxygen = qMax(1.0f, maxOxygen);
    m_oxygen = qBound(0.0f, m_oxygen, m_maxOxygen);
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

float Player::oxygen() const
{
    return m_oxygen;
}

float Player::maxOxygen() const
{
    return m_maxOxygen;
}

float Player::oxygenRatio() const
{
    return m_maxOxygen > 0.0f ? m_oxygen / m_maxOxygen : 0.0f;
}

Player::OxygenState Player::oxygenState() const
{
    if (m_oxygen <= 0.0f) {
        return OxygenState::Empty;
    }

    const float ratio = oxygenRatio();
    if (ratio <= 0.10f) {
        return OxygenState::Danger;
    }
    if (ratio <= 0.25f) {
        return OxygenState::Warning;
    }
    return OxygenState::Safe;
}

bool Player::isMoving() const
{
    return !qFuzzyIsNull(m_velocity.x()) || !qFuzzyIsNull(m_velocity.y());
}
