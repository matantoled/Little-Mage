#pragma once
#include "Resources.h"
#include <cstdlib>
#include <stdexcept>



namespace
{
	int num_of_pics;

	void readData(AnimationData& animation, sf::Vector2i& currentStart, sf::Vector2i& initSpace,
		sf::Vector2i& middleSpace, State state, sf::Vector2i& size, int pics, int anim_off, int offset) {

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		currentStart = { initSpace.x, initSpace.y + anim_off * offset };
		animation.m_data[state].emplace_back(currentStart, size);
		for (num_of_pics = 1; num_of_pics < pics; num_of_pics++)
			animation.m_data[state].emplace_back(nextStart(), size);

	}
	// ---------------------- player ----------------------
	AnimationData playerData()
	{
		auto size = PLAYER_SIZE;
		auto initSpace = PLAYER_INIT_SPACE;
		auto middleSpace = PLAYER_MIDDLE_SPACE;

		auto player = AnimationData{};
		auto currentStart = initSpace;

		// stay
		readData(player, currentStart, initSpace, middleSpace, State::Stay, size, PLAYER_STAY_PICS, PLAYER_OFFSET, 0);

		// right
		readData(player, currentStart, initSpace, middleSpace, State::Right, size, PLAYER_SIDES_PICS, PLAYER_OFFSET, 1);

		// left
		readData(player, currentStart, initSpace, middleSpace, State::Left, size, PLAYER_SIDES_PICS, PLAYER_OFFSET, 1);

		// jump
		readData(player, currentStart, initSpace, middleSpace, State::Up, size, PLAYER_JUMP_PICS, PLAYER_OFFSET, 2);

		// attack
		readData(player, currentStart, initSpace, middleSpace, State::Ctrl, size, PLAYER_ATT_PICS, PLAYER_OFFSET, 3);

		// dead 
		readData(player, currentStart, initSpace, middleSpace, State::Down, size, PLAYER_DEAD_PICS, PLAYER_OFFSET, 5);

		return player;
	}

	// ---------------------- Ghost ----------------------
	AnimationData ghostData()
	{
		auto size = GHOST_SIZE;
		auto initSpace = GHOST_INIT_SPACE;
		auto middleSpace = GHOST_MIDDLE_SPACE;

		auto ghost = AnimationData{};
		auto currentStart = initSpace;

		// up
		readData(ghost, currentStart, initSpace, middleSpace, State::Up, size, GHOST_SIDES_PICS, GHOST_PICS_OFFSET_Y, 0);

		// down
		readData(ghost, currentStart, initSpace, middleSpace, State::Down, size, GHOST_SIDES_PICS, GHOST_PICS_OFFSET_Y, 0);

		// Right
		readData(ghost, currentStart, initSpace, middleSpace, State::Right, size, GHOST_SIDES_PICS, GHOST_PICS_OFFSET_Y, 0);

		// Left
		readData(ghost, currentStart, initSpace, middleSpace, State::Left, size, GHOST_SIDES_PICS, GHOST_PICS_OFFSET_Y, 0);

		// ctrl
		readData(ghost, currentStart, initSpace, middleSpace, State::Ctrl, size, GHOST_ATT_PICS, GHOST_PICS_OFFSET_Y, 1);

		// dead
		readData(ghost, currentStart, initSpace, middleSpace, State::Stay, size, GHOST_DEAD_PICS, GHOST_PICS_OFFSET_Y, 2);

		return ghost;
	}

	// ---------------------- key ----------------------
	AnimationData keyData()
	{
		auto size = KEY_SIZE;
		auto initSpace = KEY_INIT_SPACE;
		auto middleSpace = KEY_MIDDLE_SPACE;

		auto key = AnimationData{};
		auto currentStart = initSpace;

		// stay
		readData(key, currentStart, initSpace, middleSpace, State::Stay, size, KEY_PICS, 0, 0);

		return key;
	}

	// ---------------------- door ----------------------
	AnimationData doorData()
	{
		auto size = DOOR_SIZE;
		auto initSpace = DOOR_INIT_SPACE;
		auto middleSpace = DOOR_MIDDLE_SPACE;

		auto door = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		door.m_data[State::Stay].emplace_back(currentStart, size);
		for (num_of_pics = 1; num_of_pics < DOOR_PICS; num_of_pics++)
			door.m_data[State::Up].emplace_back(nextStart(), size);

		return door;
	}

	// ---------------------- wall ----------------------
	AnimationData wallData()
	{
		auto size = WALL_SIZE;
		auto initSpace = WALL_INIT_SPACE;

		auto wall = AnimationData{};

		wall.m_data[State::Stay].emplace_back(initSpace, size);

		return wall;
	}

	// ---------------------- fire ----------------------
	AnimationData fireData()
	{
		auto size = FIRE_SIZE;
		auto initSpace = FIRE_INIT_SPACE;
		auto middleSpace = FIRE_MIDDLE_SPACE;

		auto fire = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		// stay
		readData(fire, currentStart, initSpace, middleSpace, State::Stay, size, FIRE_PICS, 0, 0);

		return fire;
	}

	// ---------------------- bullet ----------------------
	AnimationData bulletData()
	{
		auto size = BULLET_SIZE;
		auto initSpace = BULLET_INIT_SPACE;

		auto bullet = AnimationData{};
		auto currentStart = initSpace;

		bullet.m_data[State::Stay].emplace_back(currentStart, size);
		bullet.m_data[State::Right].emplace_back(currentStart, size);
		bullet.m_data[State::Left].emplace_back(currentStart, size);

		return bullet;
	}

	// ---------------------- spikes ----------------------
	AnimationData spikesData()
	{
		auto size = SPIKES_SIZE;
		auto initSpace = SPIKES_INIT_SPACE;
		auto middleSpace = SPIKES_MIDDLE_SPACE;

		auto spikes = AnimationData{};
		auto currentStart = initSpace;

		auto nextStart = [&]()
		{
			currentStart += middleSpace;
			currentStart.x += size.x;
			return currentStart;
		};

		// stay
		readData(spikes, currentStart, initSpace, middleSpace, State::Stay, size, SPIKES_PICS, 0, 0);

		return spikes;
	}

	// ---------------------- monster ----------------------
	AnimationData monsterData()
	{
		auto size = MONSTER_SIZE;
		auto initSpace = MONSTER_INIT_SPACE;
		auto middleSpace = MONSTER_MIDDLE_SPACE;

		auto monster = AnimationData{};
		auto currentStart = initSpace;

		// Right
		readData(monster, currentStart, initSpace, middleSpace, State::Right, size, MONSTER_SIDES_PICS, MONSTER_PICS_OFFSET_Y, 0);

		// left
		readData(monster, currentStart, initSpace, middleSpace, State::Left, size, MONSTER_SIDES_PICS, MONSTER_PICS_OFFSET_Y, 0);

		// ctrl
		readData(monster, currentStart, initSpace, middleSpace, State::Ctrl, size, MONSTER_ATT_PICS, MONSTER_PICS_OFFSET_Y, 1);

		// dead
		readData(monster, currentStart, initSpace, middleSpace, State::Stay, size, MONSTER_DEAD_PICS, MONSTER_PICS_OFFSET_Y, 2);

		return monster;
	}
}


Resources::Resources() : m_data(Max) {

	m_textures.resize(NUM_OF_TEXTURES);
	m_buffers.resize(NUM_OF_SOUNDS);

	try {
		std::ifstream file = std::ifstream("FilesList.txt");	//open level file
		if (file) {
			auto line = std::string();			// to reads lines from the file

			// read textures names from file
			for (int i = 0; i < NUM_OF_TEXTURES; i++) {
				if (!std::getline(file, line))
					throw std::runtime_error("Can't read from file");
				m_textures[i].loadFromFile(line);
			}

			// read sounds names from file
			for (int i = 0; i < NUM_OF_SOUNDS; i++) {
				if (!std::getline(file, line))
					throw std::runtime_error("Can't read from file");
				m_buffers[i].loadFromFile(line);
			}

			// read musics names from file
			for (int i = 0; i < NUM_OF_MUSICS; i++) {
				if (!std::getline(file, line))
					throw std::runtime_error("Can't read from file");
				m_musics[i].openFromFile(line);
			}
		}
		else
			throw std::runtime_error("Can't load file");

		// font
		if (!m_font.loadFromFile("panipuri.ttf"))
			throw std::runtime_error("Can't load file");

	}
	catch (std::runtime_error& exception) {
		std::cerr << "Exception: " << exception.what() << '\n';
		exit(EXIT_FAILURE);
	}

	// set volume
	m_musics[MenuMusic].setVolume(MENU_SONG_VOLUME);
	m_musics[IntroMusic].setVolume(MAX_VOLUME);
	m_musics[GameMusic].setVolume(GAME_SONG_VOLUME);

	// set animation
	m_data[Objects::Player] = playerData();
	m_data[Objects::Ghost] = ghostData();
	m_data[Objects::Key] = keyData();
	m_data[Objects::Door] = doorData();
	m_data[Objects::Wall] = wallData();
	m_data[Objects::Fire] = fireData();
	m_data[Objects::Bullet] = bulletData();
	m_data[Objects::Spikes] = spikesData();
	m_data[Objects::Monster] = monsterData();
}
//=========================================================
sf::Texture& Resources::get(const BackgroundType type)
{
	switch (type)
	{
		// backgrounds
	case BackgroundType::MenuBackground:
		return m_textures[0];
	case BackgroundType::HelpBackground:
		return m_textures[1];
	case BackgroundType::Background1:
		return m_textures[2];
	case BackgroundType::Background2:
		return m_textures[3];
	case BackgroundType::Background3:
		return m_textures[4];
	case BackgroundType::WinLevelBackground:
		return m_textures[5];
	case BackgroundType::WinBackground:
		return m_textures[6];
	}
	throw std::runtime_error("No Texture of that type");
}
//=========================================================
sf::Texture& Resources::get(const ButtonType type)
{
	switch (type)
	{
		// buttons
	case ButtonType::Start:
		return m_textures[7];
	case ButtonType::Help:
		return m_textures[8];
	case ButtonType::Exit:
		return m_textures[9];
	case ButtonType::Back:
		return m_textures[10];
	case ButtonType::SoundOn:
		return m_textures[11];
	case ButtonType::SoundOff:
		return m_textures[12];
	case ButtonType::KeyButton:
		return m_textures[19];
	}
	throw std::runtime_error("No Texture of that type");
}
//=========================================================
sf::Texture& Resources::get(const IntroTakesType type) {

	switch (type)
	{
		// game intro takes
	case IntroTakesType::Take1:
		return m_textures[13];
	case IntroTakesType::Take2:
		return m_textures[14];
	case IntroTakesType::Take3:
		return m_textures[15];
	case IntroTakesType::Take4:
		return m_textures[16];
	case IntroTakesType::Take5:
		return m_textures[17];
	case IntroTakesType::Take6:
		return m_textures[18];
	}
	throw std::runtime_error("No Texture of that type");
}
//=========================================================
sf::Font& Resources::get() {

	return m_font;
}
//=========================================================
void Resources::playSound(const SoundType type){

	switch (type)
	{
		// sounds
	case SoundType::GateSound:
		m_sound.setBuffer(m_buffers[0]);
		m_sound.play();
		return;
	case SoundType::ShootSound:
		m_sound.setBuffer(m_buffers[1]);
		m_sound.play();
		return;
	case SoundType::DeathPlayerSound:
		m_sound.setBuffer(m_buffers[2]);
		m_sound.play();
		return;
	case SoundType::DeathGhostSound:
		m_sound.setBuffer(m_buffers[3]);
		m_sound.play();
		return;
	case SoundType::KeySound:
		m_sound.setBuffer(m_buffers[4]);
		m_sound.play();
		return;
	case SoundType::LoseSound:
		m_sound.setBuffer(m_buffers[5]);
		m_sound.play();
		return;
	case SoundType::WinLevelSound:
		m_sound.setBuffer(m_buffers[6]);
		m_sound.play();
		return;
	case SoundType::ClickSound:
		m_sound.setBuffer(m_buffers[7]);
		m_sound.play();
		return;
	case SoundType::WinGameSound:
		m_sound.setBuffer(m_buffers[8]);
		m_sound.play();
		return;
	}
	throw std::runtime_error("No sound buffer of that type");
}
//=========================================================
void Resources::playMusic(const MusicType type) {

	switch (type)
	{
		// game intro takes
	case MusicType::MenuMusic:
		m_musics[GameMusic].stop();
		m_musics[MenuMusic].play();
		m_musics[MenuMusic].setLoop(true);
		return;
	case MusicType::IntroMusic:
		m_musics[MenuMusic].stop();
		m_musics[IntroMusic].play();
		return;
	case MusicType::GameMusic:
		m_musics[IntroMusic].stop();
		m_musics[MenuMusic].stop();
		m_musics[GameMusic].play();
		m_musics[GameMusic].setLoop(true);
		return;
	}
	throw std::runtime_error("No music of that type");
}
//=========================================================
void Resources::setMute(bool status) {
	if (status) {
		m_musics[GameMusic].setVolume(MUTE_VOLUME);
		m_sound.setVolume(MUTE_VOLUME);
	}
	else {
		m_musics[GameMusic].setVolume(GAME_SONG_VOLUME);
		m_sound.setVolume(MAX_VOLUME);
	}
}
//=========================================================