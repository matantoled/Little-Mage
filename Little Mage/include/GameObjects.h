#pragma once
#include "Resources.h"
#include "Animation.h"


class GameObjects {

public:
	GameObjects(sf::Vector2f location, Resources::Objects object);
	virtual ~GameObjects() = default;

	GameObjects(const GameObjects&) = default;
	GameObjects& operator=(const GameObjects&) = default;
	GameObjects(GameObjects&&) = default;
	GameObjects& operator=(GameObjects&&) = default;

	void draw(sf::RenderTarget& target);
	void setCurrPos(sf::Vector2f loc);
	sf::Sprite getSprite() const;
	void state(sf::Keyboard::Key key);
	const bool getIsDead() const;
	void setIsDead(bool status);

protected:
	sf::Sprite m_sprite;
	State m_dir = State::Stay;
	Animation m_animation;
	bool m_isDead = false;

};