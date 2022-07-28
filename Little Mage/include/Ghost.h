#pragma once
#include "Enemy.h"


class Ghost : public Enemy {

public:
	Ghost(sf::Vector2f location, Resources::Objects object);
	virtual ~Ghost() = default;

	Ghost(const Ghost&) = default;
	Ghost& operator=(const Ghost&) = default;
	Ghost(Ghost&&) = default;
	Ghost& operator=(Ghost&&) = default;

	void update(sf::Time delta) override;
	void changeDir();
	void changeAnimState(State state);
	const sf::Vector2f findNewLoc(const sf::Keyboard::Key key, const float dt) const;

private:

};

