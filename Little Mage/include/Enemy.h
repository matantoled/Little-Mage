#pragma once
#include "MovingObjects.h"


class Enemy : public MovingObjects {

public:
    using MovingObjects::MovingObjects;
    virtual ~Enemy() = default;

    Enemy(const Enemy&) = default;
    Enemy& operator=(const Enemy&) = default;
    Enemy(Enemy&&) = default;
    Enemy& operator=(Enemy&&) = default;

    void handleEnemyDeath();
    const bool getWasShot() const;
    void setWasShot(bool status);

private:
    bool m_wasShot = false;

};