#pragma once
#include <fstream>
#include "Resources.h"
#include "Player.h"
#include "Wall.h"
#include "Ghost.h"
#include "Fire.h"
#include "Door.h"
#include "Key.h"
#include "Bullet.h"
#include "Spikes.h"
#include "Monster.h"


class Board {

public:
	Board();
	virtual ~Board() = default;

	Board(const Board&) = default;
	Board& operator=(const Board&) = default;
	Board(Board&&) = default;
	Board& operator=(Board&&) = default;

	void moveObjects(const sf::Time dt);
	void setBoard(const int LevelNum);
	void handleIfPressCtrl();
	void setWinGame(const bool win);
	void drawObjects(sf::RenderWindow& window) const;
	void playerDir(const sf::Keyboard::Key key) const;
	const bool getWinLevel() const;
	const bool getWinGame() const;
	const int getTime() const;
	const sf::Vector2f getPlayerPos() const;
	const bool getPlayerkey() const;

private:
	void collisions();
	void eraseIfDead();
	void initObjects();
	void movePlayer(const sf::Time delta);
	void updateAnimation(const sf::Time dt);
	void setPlayerPos(sf::Vector2f pos);
	void readLevelFile(std::ifstream& file);
	void createObject(const ObjectType type, const sf::Vector2f location);
	const sf::Vector2f findLocation(const int row, const int col) const;

	std::unique_ptr<Player> m_player;
	std::vector<std::unique_ptr<StaticObjects>> m_staticObjects; //store static objects
	std::vector<std::unique_ptr<MovingObjects>> m_movingObjects; //store moving objects
	sf::Clock m_createBullet;

	int m_rows = DEFAULT_ROWS;		//num of rows in board
	int m_cols = DEFAULT_COLS;		//num of cols in board
	int m_timeLevel = 0;			//time for current level
	bool m_winLevel = false;		//if win level
	bool m_winGame = false;			//if win game

};
