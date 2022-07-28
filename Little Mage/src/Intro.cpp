#pragma once
#include "Intro.h"

Intro::Intro()
{
	skipButton.setSize(SKIP_BUTTON_SIZE);
	skipButton.setPosition(SKIP_BUTTON_POS);
	skipButton.setOutlineColor(sf::Color::White);
	skipButton.setFillColor(sf::Color::Transparent);
	skipButton.setOutlineThickness(THICKNESS_FRAME);

	m_imageTime[0] = TAKE1;
	m_imageTime[1] = TAKE2;
	m_imageTime[2] = TAKE3;
	m_imageTime[3] = TAKE4;
	m_imageTime[4] = TAKE5;
	m_imageTime[5] = TAKE6;
}
//=========================================================
void Intro::runGameIntro(sf::RenderWindow& window) {
	
	sf::Clock voiceClock;

	Resources::instance().playMusic(MusicType::IntroMusic);

	for (int i = 0; i < NUM_OF_VOICES; i++, m_inIntro) {

		voiceClock.restart();
		while (voiceClock.getElapsedTime().asSeconds() < m_imageTime[i] && window.isOpen() and m_inIntro) {
			window.clear();
			window.draw(sf::Sprite(Resources::instance().get(IntroTakesType(i))));
			window.draw(skipButton);
			window.display();
			for (auto event = sf::Event{}; window.pollEvent(event);)
			{
				switch (event.type)
				{
				case sf::Event::Closed:
					window.close();
					exit(EXIT_SUCCESS);
				case sf::Event::MouseMoved:
					handleMouseMove(window);
					break;
				case sf::Event::MouseButtonReleased:
					if (event.mouseButton.button == sf::Mouse::Button::Left)
						handleMenuClick(window);
					break;
				}
			}
		}
	}
}
//=========================================================
void Intro::handleMouseMove(sf::RenderWindow& window) {

	if (skipButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
		skipButton.setOutlineColor(sf::Color::Magenta);
	else
		skipButton.setOutlineColor(sf::Color::White);
}
//=========================================================
void Intro::handleMenuClick(sf::RenderWindow& window) {

	// start game -> user pressed skip button
	if (skipButton.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window)))) {
		m_inIntro = false;
		Resources::instance().playSound(SoundType::ClickSound);
	}
}
//=========================================================