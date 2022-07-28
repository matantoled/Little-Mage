#pragma once
#include "Bullet.h"


Bullet::Bullet(sf::Vector2f location, Resources::Objects object, bool rightDir)
    : MovingObjects(location, object)
{
    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    if (rightDir) {
        m_animation.state(State::Right);
        m_dir = State::Right;
    }
    else {
        m_sprite.setScale(SCALE_TO_THE_LEFT);
        m_sprite.setPosition({ m_sprite.getPosition().x - BULLET_OFFSET_TO_LEFT_X,  m_sprite.getPosition().y });
        m_animation.state(State::Left);
        m_dir = State::Left;
    }
    Resources::instance().playSound(SoundType::ShootSound);
}

void Bullet::update(sf::Time delta)
{
    m_sprite.move(toVector(m_dir) * delta.asSeconds() * BULLET_SPEED);
    m_animation.update(delta);
}