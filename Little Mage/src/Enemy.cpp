#pragma once
#include "Enemy.h"


//=========================================================
void Enemy::handleEnemyDeath() {

    m_clock.restart();
    m_dir = State::Stay;
    m_animation.state(m_dir);
    m_wasShot = true;
}

//=========================================================
const bool Enemy::getWasShot() const
{
    return m_wasShot;
}
//=========================================================
void Enemy::setWasShot(bool status)
{
    m_wasShot = status;
}