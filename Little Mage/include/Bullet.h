#pragma once
#include "MovingObjects.h"


class Bullet : public MovingObjects {

public:
	Bullet(sf::Vector2f location, Resources::Objects object, bool rightDir);
    virtual ~Bullet() = default;

    Bullet(const Bullet&) = default;
    Bullet& operator=(const Bullet&) = default;
    Bullet(Bullet&&) = default;
    Bullet& operator=(Bullet&&) = default;

	void update(sf::Time delta) override;

private:

};