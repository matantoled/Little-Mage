#pragma once
#include "Resources.h"


class Toolbar
{
public:
	Toolbar();
	virtual ~Toolbar() = default;

	Toolbar(const Toolbar&) = default;
	Toolbar& operator=(const Toolbar&) = default;
	Toolbar(Toolbar&&) = default;
	Toolbar& operator=(Toolbar&&) = default;

	const int getLevelNum() const;
	void setLevelNum(const int num);
	void drawToolbarText(sf::RenderWindow&, const int time, sf::Vector2f pos, bool hasKey);
	void handleSoundStatus(sf::Vector2f location);

private:
	
	sf::Text m_levelText;		//to print text of level number 
	sf::Text m_timeText;		//to print text of level current time
	sf::Text m_keyText;			//to print text of level current time

	int m_levelNum = 1;			//to store level number
	sf::Sprite m_soundStatus , m_key;
	bool m_drawSoundStatus = false;
	bool m_soundStat = true;

};