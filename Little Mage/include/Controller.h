#pragma once
#include "Board.h"
#include "Menu.h"
#include "Toolbar.h"
#include "Intro.h"


class Controller {

public:
	Controller();
	virtual ~Controller() = default;

	Controller(const Controller&) = default;
	Controller& operator=(const Controller&) = default;
	Controller(Controller&&) = default;
	Controller& operator=(Controller&&) = default;

	void run();
	
private:
	void resetTimeLevel();
	void printWinLevel();
	void printWinGame();
	void updatePlayerDir();
	void updateView(sf::View& myView);
	void handleEvents(sf::View& myView);
	void draw(sf::View myView);
	void handleGameTime();
	void runGame();
	void runLevel();
	const sf::Sprite getBackgroundSprite() const;

	Board m_board;
	Menu m_menu;									//for menu
	Toolbar m_toolbar;								//for level information data
	Intro m_intro;									//for intro to the game

	sf::RenderWindow m_window;						//game render window
	sf::Time m_gameTime;							//for the time of the game 
	sf::Clock m_deltaTime,							//for delta time of game
		m_timeOfCurrLevel;							//for time of current level

	bool m_endOfTime = false;						//if level time end

};
