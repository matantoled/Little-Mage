#pragma once
#include "MovingObjects.h"


class Player : public MovingObjects {

public:
	Player(sf::Vector2f location, Resources::Objects object);
	virtual ~Player() = default;

	Player(const Player&) = default;
	Player& operator=(const Player&) = default;
	Player(Player&&) = default;
	Player& operator=(Player&&) = default;

	void movePlayerDown();
	void movePlayer(sf::Time delta);
	void setOnGround(bool status);
	void handlePlayerDeath();
	void setPlayerState(State state);
	const bool getHaveKey() const;
	void setHaveKey(bool status);
	void setEnterDoor(bool status);
	void setRightDir(bool status);
	void setDt(float dt);
	void updateAnimation(const sf::Time delta);
	void update(const sf::Time delta) override;
	const bool getEnterDoor() const;
	const bool getRightDir() const;

	const sf::Clock& getPlayerClock() const;
	const sf::Vector2f getStartPos() const;

private:

	void updateDir();
	const sf::Vector2f findNewLoc(const sf::Keyboard::Key key, const float dt) const;

	sf::Time m_elapsed;
	sf::Vector2f m_startPos;

	bool m_haveKey = false;
	bool m_enterDoor = false;
	bool m_pressJump = false;
	bool m_onGround = false;
	bool m_rightDir = true;
	float m_dt = 1;

};
