#pragma once
#include "Toolbar.h"

Toolbar::Toolbar() {
	
	//set font
	m_levelText.setFont(Resources::instance().get());
	m_timeText.setFont(Resources::instance().get());
	m_keyText.setFont(Resources::instance().get());

	//set text size
	m_levelText.setCharacterSize(SIZE_OF_TEXT);
	m_timeText.setCharacterSize(SIZE_OF_TEXT);
	m_keyText.setCharacterSize(SIZE_OF_TEXT);

	//set text color
	m_levelText.setFillColor(sf::Color::White);
	m_timeText.setFillColor(sf::Color::White);
	m_keyText.setFillColor(sf::Color::White);

	m_soundStatus.setTexture(Resources::instance().get(ButtonType::SoundOn));
	m_soundStatus.setScale(0.25, 0.25);
	m_key.setTexture(Resources::instance().get(ButtonType::KeyButton));

}
//=========================================================
void Toolbar::drawToolbarText (sf::RenderWindow& window, const int time, sf::Vector2f pos, bool hasKey) {

	//draw level number
	m_levelText.setString(LEVEL + std::to_string(m_levelNum));
	m_levelText.setPosition(sf::Vector2f(pos.x - 170, 10));
	window.draw(m_levelText);
	
	//draw level time
	m_timeText.setPosition(sf::Vector2f(pos.x - 500, 10));
	m_timeText.setString(TIME + std::to_string(time));
	window.draw(m_timeText);

	m_keyText.setPosition(sf::Vector2f(pos.x + 150, 10));
	m_keyText.setString(KEY);
	window.draw(m_keyText);

	m_soundStatus.setPosition(sf::Vector2f(pos.x + 450.f, 10.f));
	window.draw(m_soundStatus);

	if (hasKey) {
		m_key.setPosition(sf::Vector2f(pos.x + 250.f, 10.f));
		window.draw(m_key);
	}
}
//=========================================================
const int Toolbar::getLevelNum() const {

	return m_levelNum;
}
//=========================================================
void Toolbar::setLevelNum(const int num) {

	m_levelNum = num;
}
//=========================================================
void Toolbar::handleSoundStatus(sf::Vector2f location)
{
	if (m_soundStatus.getGlobalBounds().contains(location))
	{
		if (!m_soundStat)
		{
			m_soundStatus.setTexture(Resources::instance().get(ButtonType::SoundOn));
			m_soundStat = true;
			Resources::instance().setMute(false);
		}
		else
		{
			m_soundStatus.setTexture(Resources::instance().get(ButtonType::SoundOff));
			m_soundStat = false;
			Resources::instance().setMute(true);
		}
	}
}
