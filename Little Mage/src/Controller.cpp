#pragma once
#include "Controller.h"
#include "Player.h"
#include <SFML/OpenGL.hpp>

Controller::Controller() :m_window(sf::VideoMode(unsigned(SCREEN_X_SIZE), unsigned(SCREEN_Y_SIZE), BPP), "LITTLE MAGE", sf::Style::Default)
{
	m_window.setFramerateLimit(FPS);
}
//=========================================================
void Controller::run() {

	srand(static_cast<unsigned>(time(nullptr)));

	//main loop
	while (m_window.isOpen()) {

		m_menu.runMenu(m_window);
		m_board.setBoard(m_toolbar.getLevelNum());
		runGame();
		printWinGame();
	}
}
//=========================================================
void Controller::runGame() {

	static bool runIntro = false;	// to run the intro only once
	if (!runIntro) {
		m_intro.runGameIntro(m_window);
		runIntro = true;
	}

	Resources::instance().playMusic(MusicType::GameMusic);	

	while (!m_board.getWinGame()) {

		resetTimeLevel();
		runLevel();
		if (!m_endOfTime) {	//if level time not end and got here, set the next level
			m_toolbar.setLevelNum(m_toolbar.getLevelNum() + 1);
			printWinLevel();
		}
		m_board.setBoard(m_toolbar.getLevelNum());
	}
	m_toolbar.setLevelNum(FIRST_LEVEL);
	m_board.setWinGame(false);
}
//=========================================================
void Controller::runLevel() {

	sf::View myView(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(SCREEN_X_SIZE, SCREEN_Y_SIZE));
	auto delta = m_deltaTime.restart();
	m_window.setKeyRepeatEnabled(false);

	while (!m_board.getWinLevel())
	{
		updateView(myView);
		draw(myView);
		handleGameTime();

		if (m_gameTime.asSeconds() < 0) {	// if level time ends
			m_endOfTime = true;
			Resources::instance().playSound(SoundType::LoseSound);
			break;
		}

		handleEvents(myView);
		m_board.handleIfPressCtrl();	// to create the bullet
		delta = m_deltaTime.restart();
		m_board.moveObjects(delta);
	}
	myView.setCenter(SCREEN_X_SIZE / 2, myView.getCenter().y);
	m_window.setView(myView);
}
//=========================================================
void Controller::handleGameTime() {

	if (m_board.getTime() > 0) {	//if time > 0: time is factor in level
		m_gameTime -= m_timeOfCurrLevel.getElapsedTime();
		m_timeOfCurrLevel.restart();
	}
}
//=========================================================
void Controller::handleEvents(sf::View& myView) {

	for (auto event = sf::Event{}; m_window.pollEvent(event);)
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			exit(EXIT_SUCCESS);
		case sf::Event::Resized:
			myView.setSize(SCREEN_X_SIZE * (m_window.getSize().x) / float(m_window.getSize().y), SCREEN_Y_SIZE);
			break;
		case sf::Event::MouseMoved:
			break;
		case sf::Event::MouseButtonReleased:
			auto location = m_window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
			m_toolbar.handleSoundStatus(location);
			break;
		}
		updatePlayerDir();
	}
}
//=========================================================
void Controller::updatePlayerDir() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_board.playerDir(sf::Keyboard::Right);
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_board.playerDir(sf::Keyboard::Left);
	else
		m_board.playerDir(sf::Keyboard::Space);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		m_board.playerDir(sf::Keyboard::Up);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl))
		m_board.playerDir(sf::Keyboard::LControl);
}
//=========================================================
void Controller::updateView(sf::View& myView) {

	sf::Vector2f playerPos = m_board.getPlayerPos();

	myView = m_window.getView();
	if (playerPos.x - m_window.getSize().x / 2 < 0) {
		myView.setCenter(float(m_window.getSize().x / 2), myView.getCenter().y);
	}
	else if ((playerPos.x + m_window.getSize().x / 2) > WIDTH_SCREEN) {
		myView.setCenter(WIDTH_SCREEN - m_window.getSize().x / 2, myView.getCenter().y);
	}
	else
		myView.setCenter(playerPos.x, myView.getCenter().y);
	m_window.setView(myView);	// set the view according to the player
}
//=========================================================
void Controller::draw(sf::View myView){
	
	m_window.clear();
	m_window.draw(getBackgroundSprite());
	m_board.drawObjects(m_window);

	if (m_board.getTime() == 0)
		m_toolbar.drawToolbarText(m_window, int(m_timeOfCurrLevel.getElapsedTime().asSeconds()) , myView.getCenter(), m_board.getPlayerkey());
	else
		m_toolbar.drawToolbarText(m_window, int(m_gameTime.asSeconds()), myView.getCenter(), m_board.getPlayerkey());

	m_window.display();
}
//=========================================================
const sf::Sprite Controller::getBackgroundSprite() const {

	// choose background level from 3 backgounds (by %3)
	if (m_toolbar.getLevelNum() % NUM_OF_BACKGROUNDS == 1)
		return sf::Sprite(Resources::instance().get(BackgroundType::Background1));
	else if (m_toolbar.getLevelNum() % NUM_OF_BACKGROUNDS == 2)
		return sf::Sprite(Resources::instance().get(BackgroundType::Background2));
	else
		return sf::Sprite(Resources::instance().get(BackgroundType::Background3));
}
//=========================================================
void Controller::printWinGame() {

	m_window.clear();
	sf::Sprite winSprite(Resources::instance().get(BackgroundType::WinBackground));
	m_window.draw(winSprite);
	m_window.display();
	Resources::instance().playSound(SoundType::WinGameSound);
	while (true) //wating for user press escape to continue
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			break;
}
//=========================================================
void Controller::resetTimeLevel() {

	m_timeOfCurrLevel.restart();
	m_gameTime = sf::seconds(float(m_board.getTime()));
	m_endOfTime = false;
}
//=========================================================
void Controller::printWinLevel() {

	if (m_toolbar.getLevelNum() > NUM_OF_LEVELS)
		return;
	m_window.clear();
	sf::Sprite winSprite(Resources::instance().get(BackgroundType::WinLevelBackground));
	m_window.draw(winSprite);
	Resources::instance().playSound(SoundType::WinLevelSound);
	m_window.display();
	while (true) //wating for user press enter to continue
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
			break;
}
//=========================================================