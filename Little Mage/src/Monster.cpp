#pragma once
#include "Monster.h"

//=========================================================

Monster::Monster(sf::Vector2f location, Resources::Objects object) : Enemy( location, object) {

    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, 0);
    m_sprite.move(0, 1);
}

//=========================================================

void Monster::changeDir() {
    m_clock.restart();
    if (m_dir == State::Right) {
        m_dir = State::Left;
    }
    else {
        m_dir = State::Right;
    }
    m_animation.state(m_dir);
}

//=========================================================
void Monster::update(sf::Time delta)
{
    if (getWasShot() and m_clock.getElapsedTime().asSeconds() >= (TIME_FOR_DEATH_GHOST_ANIMATION - 0.2)) {
        m_isDead = true;
        return;
    }   
    if (m_clock.getElapsedTime().asSeconds() >= 1.8)
    {
        if (m_dir == State::Ctrl) {
            changeDir();
        }
        m_clock.restart();
    }
    
    m_prevLocation = m_sprite.getPosition();
    m_sprite.move(toVector(m_dir) * delta.asSeconds() * MonsterSpeed);
    m_animation.update(delta);
}

void Monster::setLeftGround(bool status)
{
    m_leftGround = status;
}

void Monster::setRightGround(bool status)
{
    m_rightGround = status;
}

void Monster::setdir()
{
    if (!m_leftGround and !m_rightGround) {
        m_sprite.setPosition(m_prevLocation);
        changeDir();
    }
}

//=========================================================
void Monster::changeAnimState(State state) {
    m_clock.restart();

    m_dir = State::Ctrl;
    if (state == State::Right) {
        m_sprite.setScale(SCALE_TO_THE_LEFT);
    }
    else if (state == State::Left) {
        m_sprite.setScale(SCALE_TO_THE_RIGHT);
    }
    m_animation.state(m_dir);
}