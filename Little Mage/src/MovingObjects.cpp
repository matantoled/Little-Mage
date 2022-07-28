#pragma once
#include "MovingObjects.h"

MovingObjects::MovingObjects(sf::Vector2f location, Resources::Objects object) 
	:GameObjects(location, object) {

    m_dir = State::Right;
    m_animation.state(State::Right);
	m_prevLocation = getSprite().getPosition();
}
//=========================================================
const sf::Vector2f MovingObjects::getPrevLoc() const {

	return m_prevLocation;
}
//=========================================================
const sf::Vector2f MovingObjects::getPos() const
{
	return m_sprite.getPosition();
}
//=========================================================
void MovingObjects::setPos(sf::Vector2f pos)
{
	m_sprite.setPosition(pos);
}
//=========================================================
const State MovingObjects::getState() const
{
	return m_dir;
}
//=========================================================
void MovingObjects::setPrevLoc(const sf::Vector2f prevLoc) {

	m_prevLocation = prevLoc;
}