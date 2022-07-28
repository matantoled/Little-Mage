#pragma once
#include "GameObjects.h"
#include <optional>
#include "Key.h"

namespace
{
	std::optional<State> toState(sf::Keyboard::Key key)
	{
		switch (key)
		{
		case sf::Keyboard::Left:
			return State::Left;
		case sf::Keyboard::Right:
			return State::Right;
		case sf::Keyboard::Up:
			return State::Up;
		case sf::Keyboard::Space:
			return State::Stay;
		case sf::Keyboard::LControl:
			return State::Ctrl;
		default:
			return {};
		}
	}
} // end namespace


//=========================================================
GameObjects::GameObjects(sf::Vector2f location, Resources::Objects object) :
	m_animation(Resources::instance().animationData(object), State::Stay, m_sprite)
{
	m_sprite.setPosition(location);
}
//=========================================================
void GameObjects::draw(sf::RenderTarget& target)
{
	target.draw(m_sprite);
}
//=========================================================
void GameObjects::setCurrPos(sf::Vector2f loc) {

	m_sprite.setPosition(loc);
}
//=========================================================
void GameObjects::state(sf::Keyboard::Key key)
{
	if (auto dir = toState(key))
	{
		if (!m_isDead) {
			m_dir = *dir;
			m_animation.state(*dir);
		}
	}
}
//=========================================================
const bool GameObjects::getIsDead() const
{
	return m_isDead;
}
//=========================================================
void GameObjects::setIsDead(bool status)
{
	m_isDead = status;
}
//=========================================================
sf::Sprite GameObjects::getSprite() const {

	return m_sprite;
}
//=========================================================
