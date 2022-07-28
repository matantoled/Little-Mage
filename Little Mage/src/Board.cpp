#pragma once
#include "Board.h"
#include"CollisionHandling.h"
#include <sstream>


Board::Board()
{

}
//=========================================================
void Board::initObjects() {

	m_staticObjects.clear();
	m_movingObjects.clear();
}
//=========================================================
void Board::setBoard(const int levelNum) {

	initObjects();	//reset all objects

	// set level name
	std::string levelName = LEVEL_NAME;
	levelName += std::to_string(levelNum);
	levelName += FILE_EXTENSION;
	
	std::ifstream file = std::ifstream(levelName);	//open level file
	if (file)
		readLevelFile(file);
	else
		m_winGame = true;		// no more levels to read

	m_winLevel = false;		//for next level/game
}
//=========================================================
void Board::readLevelFile(std::ifstream& file) {

	auto line = std::string();			// to reads lines from the file

	try {
		if (!std::getline(file, line)) {
			throw std::runtime_error("Can't read from file");
		}

		auto readSize = std::istringstream(line);
		readSize >> m_rows >> m_cols >> m_timeLevel;

		// read the level from the file and create the objects
		for (int i = 0; i < m_rows; i++) {
			if (!std::getline(file, line)) {
				throw std::runtime_error("Can't read the line from file");
			}
			for (int j = 0; j < line.size(); j++)
				createObject(ObjectType(line[j]), findLocation(i, j));
		}
	}
	catch (std::runtime_error& exception) {
		std::cerr << "Exception: " << exception.what() << '\n';
		exit(EXIT_FAILURE);
	}
}
//=========================================================
const sf::Vector2f Board::findLocation(const int row, const int col) const {

	sf::Vector2f location;
	location.x = OBJECTSIZE_X * col;
	location.y = OBJECTSIZE_Y * row;
	return location;
}
//=========================================================
void Board::createObject(const ObjectType type, const sf::Vector2f location) {

	switch (type)
	{
		// characters
	case ObjectType::PlayerChar:
		m_player = std::make_unique<Player>(location, Resources::Player);
		break;
	case ObjectType::GhostChar:
		m_movingObjects.emplace_back(std::make_unique<Ghost>(location, Resources::Ghost));
		break;
		// static objects
	case ObjectType::WallChar:
		m_staticObjects.emplace_back(std::make_unique<Wall>(location, Resources::Wall));
		break;
	case ObjectType::FireChar:
		m_staticObjects.emplace_back(std::make_unique<Fire>(location, Resources::Fire));
		break;
	case ObjectType::DoorChar:
		m_staticObjects.emplace_back(std::make_unique<Door>(location, Resources::Door));
		break;
	case ObjectType::KeyChar:
		m_staticObjects.emplace_back(std::make_unique<Key>(location, Resources::Key));
		break;
	case ObjectType::BulletChar:
		m_movingObjects.emplace_back(std::make_unique<Bullet>(location, Resources::Bullet, m_player->getRightDir()));
		m_createBullet.restart();
		break;
	case ObjectType::SpikesChar:
		m_staticObjects.emplace_back(std::make_unique<Spikes>(location, Resources::Spikes));
		break;
	case ObjectType::MonsterChar:
		m_movingObjects.emplace_back(std::make_unique<Monster>(location, Resources::Monster));
		break;
	}
}
//=========================================================
void Board::handleIfPressCtrl()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		// if press over then 1.2 sec : create bullet
		if (m_createBullet.getElapsedTime().asSeconds() > TIME_FOR_CREATE_A_BULLET) {
			createObject(ObjectType::BulletChar, { getPlayerPos().x + OFFSET_X_FOR_BULLET, getPlayerPos().y + OFFSET_Y_FOR_BULLET });
		}
	}
	else {
		m_createBullet.restart();
	}
}
//=========================================================
void Board::moveObjects(const sf::Time dt) {

	m_player->setPrevLoc(m_player->getSprite().getPosition());
	
	movePlayer(dt);
	m_player->setDt(dt.asSeconds());
	collisions();
	eraseIfDead();
	updateAnimation(dt);
}
//=========================================================
bool collide(GameObjects& a, GameObjects& b)
{
	return a.getSprite().getGlobalBounds().intersects(b.getSprite().getGlobalBounds());
}
//=========================================================
void Board::collisions() {

	// collide player with static objects
	for (auto& staticObject : m_staticObjects) {
		if (collide(*m_player, *staticObject))
			processCollision(*m_player, *staticObject);
	}

	// collide player with moving objects
	for (auto& movingObjects : m_movingObjects) {
		if (collide(*m_player, *movingObjects))
			processCollision(*m_player, *movingObjects);
	}

	// collide moving with moving objects
	for (auto& m1 : m_movingObjects) {
		for (auto& m2 : m_movingObjects)
			if (m1 != m2 and collide(*m1, *m2))
				processCollision(*m1, *m2);
	}

	// collide moving with static objects
	for (auto& m1 : m_movingObjects) {	
		if (typeid(*m1) == typeid(Monster)) {
			Monster& monster = dynamic_cast<Monster&>(*m1);
			monster.setLeftGround(false);
			monster.setRightGround(false);
		}	
		for (auto& s1 : m_staticObjects) {
			if (collide(*m1, *s1))
				processCollision(*m1, *s1);
		}
		if (typeid(*m1) == typeid(Monster)) {
			Monster& monster = dynamic_cast<Monster&>(*m1);
			monster.setdir();
		}
	}
}
//=========================================================
void Board::eraseIfDead() {

	// delete dead objects
	std::erase_if(m_movingObjects, [](auto& movingObject) {
		return movingObject->getIsDead();
		});

	std::erase_if(m_staticObjects, [](auto& staticObject) {
		return staticObject->getIsDead();
		});
}
//=========================================================
void Board::updateAnimation(const sf::Time dt) {

	// move the objects

	m_player->updateAnimation(dt);

	for (auto& staticObject : m_staticObjects)
		staticObject->update(dt);

	for (auto& movingObject : m_movingObjects)
		movingObject->update(dt);
}
//=========================================================
void Board::drawObjects(sf::RenderWindow& window) const {
	
	// draw all objects

	for (auto& staticObject : m_staticObjects)
		staticObject->draw(window);

	for (auto& movingObject : m_movingObjects)
		movingObject->draw(window);

	m_player->draw(window);
}
//=========================================================
void Board::playerDir(const sf::Keyboard::Key key) const
{
	if (key == sf::Keyboard::Left) 
		m_player->setRightDir(false);
	else if (key == sf::Keyboard::Right)
		m_player->setRightDir(true);

	m_player->state(key);
}
//=========================================================
void Board::movePlayer(const sf::Time delta)
{
	m_player->update(delta);
}
//=========================================================
const sf::Vector2f Board::getPlayerPos() const
{
	return m_player->getPos();
}
//=========================================================
const bool Board::getPlayerkey() const
{
	return m_player->getHaveKey();
}
//=========================================================
void Board::setPlayerPos(sf::Vector2f pos)
{
	m_player->setPos(pos);
}
//=========================================================
const bool Board::getWinGame() const {

	return m_winGame;
}
//=========================================================
void Board::setWinGame(const bool win) {

	m_winGame = win;
}
//=========================================================
const bool Board::getWinLevel() const {

	return m_player->getEnterDoor();
}
//=========================================================
const int Board::getTime() const {

	return m_timeLevel;
}
//=========================================================