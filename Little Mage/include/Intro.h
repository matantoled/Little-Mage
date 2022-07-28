#pragma once
#include "Resources.h"


class Intro {

public:
	Intro();
	virtual ~Intro() = default;

	Intro(const Intro&) = default;
	Intro& operator=(const Intro&) = default;
	Intro(Intro&&) = default;
	Intro& operator=(Intro&&) = default;

	void runGameIntro(sf::RenderWindow& window);

private:
	void handleMouseMove(sf::RenderWindow& window);
	void handleMenuClick(sf::RenderWindow& window);

	sf::RectangleShape skipButton;
	bool m_inIntro = true;
	int m_imageTime[NUM_OF_VOICES];

};
