#pragma once
#include "Enemy.h"


class Monster : public Enemy {

public:
    Monster(sf::Vector2f location, Resources::Objects object);

    Monster(const Monster&) = default;
    Monster& operator=(const Monster&) = default;
    Monster(Monster&&) = default;
    Monster& operator=(Monster&&) = default;

    void changeDir();
    void update(sf::Time delta) override;
    void setLeftGround(bool status);
    void setRightGround(bool status);
    void setdir();
    void changeAnimState(State state);

private:
    bool m_leftGround = false, m_rightGround = false;

};
