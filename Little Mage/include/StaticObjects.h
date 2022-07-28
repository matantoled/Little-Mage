#pragma once
#include "GameObjects.h"


class StaticObjects : public GameObjects {

public:
	using GameObjects::GameObjects;
	virtual ~StaticObjects() = default;

	StaticObjects(const StaticObjects&) = default;
	StaticObjects& operator=(const StaticObjects&) = default;
	StaticObjects(StaticObjects&&) = default;
	StaticObjects& operator=(StaticObjects&&) = default;

	void update(const sf::Time delta) { m_animation.update(delta); }

private:

};
