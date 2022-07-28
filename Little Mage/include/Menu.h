#pragma once
#include "Resources.h"


class Menu {

public:
	Menu();
	virtual ~Menu() = default;

	Menu(const Menu&) = default;
	Menu& operator=(const Menu&) = default;
	Menu(Menu&&) = default;
	Menu& operator=(Menu&&) = default;

	void runMenu(sf::RenderWindow& window);

private:
	void handleMenuClick(bool& inMenu, sf::RenderWindow& window);
	void handleMouseMove(const sf::RenderWindow& window);
	void helpButton(sf::RenderWindow& window);
	void drawHelp(sf::RenderWindow& window);
	void drawMenu(sf::RenderWindow& window);

	std::vector<sf::RectangleShape> m_buttons;		//for menu buttons

};