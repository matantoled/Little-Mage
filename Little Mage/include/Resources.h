#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <thread>
#include <vector>
#include "AnimationData.h"
#include "State.h"
#include <iostream>
#include <fstream>


constexpr auto PlayerSpeed = 100.f, GhostSpeed = 100.f, MonsterSpeed = 100.f;
const auto AnimationTime = sf::seconds(0.2f);

//---------------- player pics consts ---------------------
const int PLAYER_STAY_PICS = 12, PLAYER_SIDES_PICS = 6, PLAYER_JUMP_PICS = 7, PLAYER_ATT_PICS = 7, PLAYER_DEAD_PICS = 10, PLAYER_OFFSET = 70;
const sf::Vector2i PLAYER_SIZE = { 65, 70 }, PLAYER_INIT_SPACE = { 0, 0 }, PLAYER_MIDDLE_SPACE = { 0, 0 };

//---------------- ghost pics consts --------------------
const int GHOST_SIDES_PICS = 4 , GHOST_ATT_PICS = 3, GHOST_DEAD_PICS = 5, GHOST_PICS_OFFSET_Y = 70;
const sf::Vector2i GHOST_SIZE = { 65, 70 }, GHOST_INIT_SPACE = { 0, 420 }, GHOST_MIDDLE_SPACE = { 0, 0 };

//---------------- key pics consts ------------------------
const int KEY_PICS = 7;
const sf::Vector2i KEY_SIZE = { 64,64 }, KEY_INIT_SPACE = { 0, 780 }, KEY_MIDDLE_SPACE = { 0, 0 };

//---------------- door pics consts -----------------------
const int DOOR_PICS = 5;
const sf::Vector2i DOOR_SIZE = { 75,75 }, DOOR_INIT_SPACE = { 0, 630 }, DOOR_MIDDLE_SPACE = { 0, 0 };

//---------------- wall pics consts -----------------------
const sf::Vector2i WALL_SIZE = { 75,75 }, WALL_INIT_SPACE = { 0, 705 }, WALL_MIDDLE_SPACE = { 0, 0 };

//---------------- fire pics consts -----------------------
const int FIRE_PICS = 6;
const sf::Vector2i FIRE_SIZE = { 75,75 }, FIRE_INIT_SPACE = { 0, 844 }, FIRE_MIDDLE_SPACE = { 0, 0 };

//---------------- bullet pics consts ---------------------
const sf::Vector2i BULLET_SIZE = { 42, 7 }, BULLET_INIT_SPACE = { 0, 919 }, BULLET_MIDDLE_SPACE = { 0, 0 };

//---------------- spikes pics consts ---------------------
const int SPIKES_PICS = 5;
const sf::Vector2i SPIKES_SIZE = { 75,75 }, SPIKES_INIT_SPACE = { 0, 926 }, SPIKES_MIDDLE_SPACE = { 0, 0 };

//---------------- monster pics consts ---------------------
const int MONSTER_SIDES_PICS = 6, MONSTER_ATT_PICS = 5, MONSTER_DEAD_PICS = 4 , MONSTER_PICS_OFFSET_Y = 75;
const sf::Vector2i MONSTER_SIZE = { 75,75 }, MONSTER_INIT_SPACE = { 0, 1001 }, MONSTER_MIDDLE_SPACE = { 0,0 };

const float OBJECTSIZE_X = 75.f, OBJECTSIZE_Y = 75.f;
const float MENU_SONG_VOLUME = 35.f, GAME_SONG_VOLUME = 50.f;
const float SCREEN_X_SIZE = 1920.f, SCREEN_Y_SIZE = 1050.f;
const float TIME_FOR_CREATE_A_BULLET = 1.2f;
const float BULLET_SPEED = PlayerSpeed * 3.5f;
const float BULLET_OFFSET_TO_LEFT_X = 77.f;
const float TIME_FOR_DEATH_PLAYER_ANIMATION = 1.8f , TIME_FOR_DEATH_GHOST_ANIMATION = 0.8f,
			TIME_FOR_CHANGE_GHOST_DIR = 3;
const float WIDTH_SCREEN = 3840.f;
const float JUMP_SECONDS = 2.f, JUMP = 3.f;
const float MUTE_VOLUME = 0, MAX_VOLUME = 100;
const int NUM_OF_BACKGROUNDS = 3;
const int NUM_OF_LEVELS = 3;
const int NUM_OF_DIRECTIONS = 4;
const int BUTTON_MENU_Y_LOC = 555, MIDDLE_SPCAE_BUTTON_MENU_Y = 100 , OFFSET_BUTTON_MENU_Y = 40;
const int PLAYER_HIGHT = 70;
const int OFFSET_X_FOR_BULLET = 50, OFFSET_Y_FOR_BULLET = 10;
const int DEFAULT_ROWS = 14;
const int DEFAULT_COLS = 51;
const int MOVMENT_SPEED = 150;
const int NUM_OF_TEXTURES = 21;
const int NUM_OF_SOUNDS = 9;
const int NUM_OF_MUSICS = 3;
const int NUM_OF_MENU_BUTTONS = 4;
const int FPS = 60;
const int START_BUTTON = 0, HELP_BUTTON = 1, QUIT_BUTTON = 2, BACK_BUTTON = 3;
const int SIZE_OF_TEXT = 40;
const int THICKNESS_FRAME = 3;
const int FIRST_LEVEL = 1;
const int NUM_OF_VOICES = 6;
const int TAKE1 = 7, TAKE2 = 5, TAKE3 = 6, TAKE4 = 6, TAKE5 = 3, TAKE6 = 6;
const sf::Vector2f LEVEL_TEXT_POS = { 312.f, 996.f }, TIME_TEXT_POS = { 698.f, 996.f }, SKIP_BUTTON_POS = { 1635.f, 36.f };
const sf::Vector2f BUTTON_MENU_SIZE = { 315.f, 90.f }, SKIP_BUTTON_SIZE = { 240.f, 75.f };
const sf::Vector2f LEFT = { -1.f,0.f }, RIGHT = { 1.f,0.f }, DOWN = { 0.f,-1.f }, UP = { 0.f,1.f };
const std::string LEVEL_NAME = "Board", FILE_EXTENSION = ".txt";
const sf::Vector2f CHAR_SIZE = { 70.f, 70.f };
const sf::Vector2f SCALE_TO_THE_LEFT = { -1, 1 }, SCALE_TO_THE_RIGHT = { 1, 1 };
const sf::Color BACKGROUND_COLOR = { 55, 55, 55, 255 };
const std::string LEVEL = "LEVEL: ", TIME = "TIME: " , KEY = "KEY: ";
const auto BPP = sf::VideoMode::getFullscreenModes()[0].bitsPerPixel;


enum class ObjectType
{
	PlayerChar = 'P',
	GhostChar = 'G',
	MonsterChar = 'M',
	WallChar = '=',
	DoorChar = '#',
	FireChar = '*',
	KeyChar = 'F',
	BulletChar = '-',
	SpikesChar = '+'
};

enum class BackgroundType
{
	MenuBackground,
	HelpBackground,
	Background1,
	Background2,
	Background3,
	WinLevelBackground,
	WinBackground
};

enum class ButtonType
{
	Start,
	Help,
	Exit,
	Back,
	SoundOn,
	SoundOff,
	KeyButton
};

enum MusicType
{
	MenuMusic,
	IntroMusic,
	GameMusic
};

enum class IntroTakesType
{
	Take1,
	Take2,
	Take3,
	Take4,
	Take5,
	Take6
};

enum class SoundType
{
	GateSound,
	ShootSound,
	DeathPlayerSound,
	DeathGhostSound,
	KeySound,
	LoseSound,
	WinLevelSound,
	ClickSound,
	WinGameSound,

};

class Resources {

public:
	enum Objects
	{
		Player,
		Ghost,
		Key,
		Door,
		Wall,
		Fire,
		Bullet,
		Spikes,
		Monster,
		Max,
	};

	static Resources & instance() {
		static auto resources = Resources(); // static in function!
		return resources;
	}
	Resources(const Resources&) = delete;
	void operator=(const Resources&) = delete;
	sf::Texture& get(const BackgroundType type);
	sf::Texture& get(const ButtonType type); 
	sf::Texture& get(const IntroTakesType type);
	sf::Font& get();
	void playSound(const SoundType type);
	void playMusic(const MusicType type);

	const AnimationData& animationData(Objects object) { return m_data[object]; }
	const sf::Texture& texture() const { return m_textures[20]; }

	void setMute(bool status);

private:
	Resources();
	std::vector<sf::Texture> m_textures;	//to store all game textures
	sf::Music m_musics[NUM_OF_MUSICS];		// sf::Music can not be used by std::vector
	std::vector<sf::SoundBuffer> m_buffers;	//to store game sounds
	std::vector<AnimationData> m_data;

	sf::Font m_font;						//to store game font
	sf::Sound m_sound;						//to play current sound
	
};
