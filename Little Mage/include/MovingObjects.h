#pragma once
#include "GameObjects.h"


class MovingObjects : public GameObjects {

public:
	MovingObjects(sf::Vector2f location, Resources::Objects object);
	virtual ~MovingObjects() = default;

	MovingObjects(const MovingObjects&) = default;
	MovingObjects& operator=(const MovingObjects&) = default;
	MovingObjects(MovingObjects&&) = default;
	MovingObjects& operator=(MovingObjects&&) = default;

	const sf::Vector2f getPrevLoc() const;
	const sf::Vector2f getPos() const;
	const State getState() const;
	void setPrevLoc(const sf::Vector2f prevLoc);
	void setPos(sf::Vector2f pos);

	virtual void update(const sf::Time delta) { m_animation.update(delta); }

protected:
	sf::Vector2f m_prevLocation;	//to store previos location
	sf::Clock m_clock;
	
};