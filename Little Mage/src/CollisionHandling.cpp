#pragma once
#include "CollisionHandling.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "Player.h"
#include "Wall.h"
#include "Ghost.h"
#include "Fire.h"
#include "Door.h"
#include "Key.h"
#include "Spikes.h"
#include "Bullet.h"
#include "Monster.h"
#include "MovingObjects.h"


namespace // anonymous namespace — the standard way to make function "static"
{

// primary collision-processing functions

// ----------------- player -----------------
// player with wall
void playerWall(GameObjects& p, GameObjects& w)
{
    Player& player = dynamic_cast<Player&>(p);
    Wall& wall = dynamic_cast<Wall&>(w);

    player.setCurrPos({ player.getPos().x, player.getPrevLoc().y });
    if (player.getSprite().getGlobalBounds().intersects(wall.getSprite().getGlobalBounds())) {
        if (player.getPos().x + player.getSprite().getGlobalBounds().width >= wall.getSprite().getPosition().x) {
            player.setCurrPos(player.getPrevLoc());
            player.movePlayerDown();
        }
    }
    if (player.getPos().y + player.getSprite().getGlobalBounds().height >= wall.getSprite().getPosition().y and
        player.getPos().y + player.getSprite().getGlobalBounds().height < wall.getSprite().getPosition().y + (PLAYER_HIGHT/2) and
        player.getPos().y < wall.getSprite().getPosition().y + PLAYER_HIGHT) {
        player.setOnGround(true);
    }
}

// player with ghost
void playerGhost(GameObjects& p, GameObjects& g)
{
    Ghost& ghost = dynamic_cast<Ghost&>(g);
    Player& player = dynamic_cast<Player&>(p);

    player.setCurrPos(player.getPrevLoc());
    ghost.setCurrPos(ghost.getPrevLoc());
    ghost.changeAnimState(player.getState());

    if (!player.getIsDead()) {
        player.handlePlayerDeath();
        Resources::instance().playSound(SoundType::DeathPlayerSound);
    }
}

// player with fire or spikes
void playerObstacle(GameObjects& p, GameObjects&)
{
    Player& player = dynamic_cast<Player&>(p);

    player.setCurrPos(player.getPrevLoc());
    
    if (!player.getIsDead()) {
        player.handlePlayerDeath();
        player.state(sf::Keyboard::Down);
    }
    if (player.getPlayerClock().getElapsedTime().asSeconds() > TIME_FOR_DEATH_PLAYER_ANIMATION) {
        player.setPlayerState(State::Stay);
        player.setCurrPos(player.getStartPos());
        player.setIsDead(false);
    }
    Resources::instance().playSound(SoundType::DeathPlayerSound);
}

// player with door
void playerDoor(GameObjects& p, GameObjects& d)
{
    Player& player = dynamic_cast<Player&>(p);
    Door& door = dynamic_cast<Door&>(d);

    if (player.getHaveKey()) {
        if (door.getState() != State::Up) {
            Resources::instance().playSound(SoundType::GateSound);
            door.state(sf::Keyboard::Up);
        }
        if (player.getSprite().getGlobalBounds().contains(door.getSprite().getPosition().x + door.getSprite().getGlobalBounds().width / 2,
            door.getSprite().getPosition().y + door.getSprite().getGlobalBounds().height / 2)) {
            Resources::instance().playSound(SoundType::WinLevelSound);
            player.setHaveKey(false);
            player.setEnterDoor(true);
        }
    }
}

// player with key
void playerKey(GameObjects& p, GameObjects& k)
{
    Player& player = dynamic_cast<Player&>(p);
    Key& key = dynamic_cast<Key&>(k);

    player.setHaveKey(true);
    key.setIsDead(true);
    Resources::instance().playSound(SoundType::KeySound);
}

// player with monster
void playerMonster(GameObjects& p, GameObjects& m)
{
    Monster& monster = dynamic_cast<Monster&>(m);
    Player& player = dynamic_cast<Player&>(p);

    player.setCurrPos(player.getPrevLoc());
    monster.setCurrPos(monster.getPrevLoc());
    monster.changeAnimState(player.getState());

    if (!player.getIsDead()) {
        player.handlePlayerDeath();
        Resources::instance().playSound(SoundType::DeathPlayerSound);
    }
}

// player with bullet
void playerBullet(GameObjects&, GameObjects&)
{
   // do nothing
} // -------------- end player ---------------



// ----------------- ghost -----------------
// ghost with static objects
void ghostStaticObject(GameObjects& g, GameObjects&)
{
    Ghost& ghost = dynamic_cast<Ghost&>(g);

    ghost.setCurrPos(ghost.getPrevLoc());
    ghost.changeDir();
}

// ghost with bullet
void ghostBullet(GameObjects& g, GameObjects& b)
{
    Ghost& ghost = dynamic_cast<Ghost&>(g);
    Bullet& bullet = dynamic_cast<Bullet&>(b);

    bullet.setIsDead(true);
    ghost.setCurrPos(ghost.getPrevLoc());
    ghost.handleEnemyDeath();
    Resources::instance().playSound(SoundType::DeathGhostSound);
}

// ghost with monster
void ghostMonster(GameObjects& g, GameObjects& m)
{
    Ghost& ghost = dynamic_cast<Ghost&>(g);
    Monster& monster = dynamic_cast<Monster&>(m);

    ghost.setCurrPos(ghost.getPrevLoc());
    ghost.changeDir();

    monster.setCurrPos(monster.getPrevLoc());
    monster.changeDir();
} // -------------- end ghost ---------------

// ----------------- bullet -----------------
void bulletStaticObject(GameObjects& b, GameObjects&)
{
    Bullet& bullet = dynamic_cast<Bullet&>(b);

    bullet.setIsDead(true);
}

void bulletGhost(GameObjects& bullet, GameObjects& ghost)
{
    ghostBullet(ghost, bullet);
} // -------------- end bullet ---------------



// ----------------- monster -----------------
// monster with bullet
void monsterBullet(GameObjects& m, GameObjects& b)
{
    Monster& monster = dynamic_cast<Monster&>(m);
    Bullet& bullet = dynamic_cast<Bullet&>(b);

    bullet.setIsDead(true);
    monster.setCurrPos(monster.getPrevLoc());
    monster.handleEnemyDeath();
    Resources::instance().playSound(SoundType::DeathGhostSound);
}

// monster with wall
void monsterWall(GameObjects& m, GameObjects& w)
{
    Monster& monster = dynamic_cast<Monster&>(m);
    Wall& wall = dynamic_cast<Wall&>(w);

    if (wall.getSprite().getGlobalBounds().contains(monster.getSprite().getPosition().x - monster.getSprite().getGlobalBounds().width,
        monster.getSprite().getPosition().y + monster.getSprite().getGlobalBounds().height)) {
        monster.setLeftGround(true);
    }
    if (wall.getSprite().getGlobalBounds().contains(monster.getSprite().getPosition().x + monster.getSprite().getGlobalBounds().width,
        monster.getSprite().getPosition().y + monster.getSprite().getGlobalBounds().height)) {
        monster.setRightGround(true);
    }

}

// monster with static objects
void monsterStaticObject(GameObjects&, GameObjects&)
{
    // do nothing
} // -------------- end monster ---------------



using HitFunctionPtr = void (*)(GameObjects&, GameObjects&);
using MapKey = std::pair<std::type_index, std::type_index>;
using HitMap = std::map<MapKey, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    //----------------- player collision ------------------------
    phm[MapKey(typeid(Player), typeid(Wall))]    = &playerWall;
    phm[MapKey(typeid(Player), typeid(Ghost))]   = &playerGhost;
    phm[MapKey(typeid(Player), typeid(Fire))]    = &playerObstacle;
    phm[MapKey(typeid(Player), typeid(Door))]    = &playerDoor;
    phm[MapKey(typeid(Player), typeid(Key))]     = &playerKey;
    phm[MapKey(typeid(Player), typeid(Spikes))]  = &playerObstacle;
    phm[MapKey(typeid(Player), typeid(Bullet))]  = &playerBullet;
    phm[MapKey(typeid(Player), typeid(Monster))] = &playerMonster;

    //----------------- ghost collision ------------------------
    phm[MapKey(typeid(Ghost), typeid(Wall))]    = &ghostStaticObject;
    phm[MapKey(typeid(Ghost), typeid(Fire))]    = &ghostStaticObject;
    phm[MapKey(typeid(Ghost), typeid(Door))]    = &ghostStaticObject;
    phm[MapKey(typeid(Ghost), typeid(Key))]     = &ghostStaticObject;
    phm[MapKey(typeid(Ghost), typeid(Spikes))]  = &ghostStaticObject;
    phm[MapKey(typeid(Ghost), typeid(Ghost))]   = &ghostStaticObject;
    phm[MapKey(typeid(Ghost), typeid(Bullet))]  = &ghostBullet;
    phm[MapKey(typeid(Ghost), typeid(Monster))] = &ghostMonster;        
    
    //----------------- bullet collision ------------------------
    phm[MapKey(typeid(Bullet), typeid(Wall))]    = &bulletStaticObject;
    phm[MapKey(typeid(Bullet), typeid(Fire))]    = &bulletStaticObject;
    phm[MapKey(typeid(Bullet), typeid(Spikes))]  = &bulletStaticObject;
    phm[MapKey(typeid(Bullet), typeid(Key))]     = &bulletStaticObject;
    phm[MapKey(typeid(Bullet), typeid(Door))]    = &bulletStaticObject;
    phm[MapKey(typeid(Bullet), typeid(Monster))] = &bulletStaticObject;
    phm[MapKey(typeid(Bullet), typeid(Ghost))]   = &bulletGhost;
    phm[MapKey(typeid(Bullet), typeid(Bullet))]  = &bulletGhost;

    //----------------- Monster collision ------------------------
    phm[MapKey(typeid(Monster), typeid(Bullet))]  = &monsterBullet;
    phm[MapKey(typeid(Monster), typeid(Wall))]    = &monsterWall;
    phm[MapKey(typeid(Monster), typeid(Ghost))]   = &monsterStaticObject;
    phm[MapKey(typeid(Monster), typeid(Monster))] = &monsterStaticObject;
    phm[MapKey(typeid(Monster), typeid(Key))]     = &monsterStaticObject;
    phm[MapKey(typeid(Monster), typeid(Fire))]    = &monsterStaticObject;
    phm[MapKey(typeid(Monster), typeid(Spikes))]  = &monsterStaticObject;
    phm[MapKey(typeid(Monster), typeid(Door))]    = &monsterStaticObject;
        
    return phm;
}


HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

} // end namespace

void processCollision(GameObjects& object1, GameObjects& object2)
{
    auto phf = lookup(typeid(object1), typeid(object2));
    if (!phf)
    {
        throw UnknownCollision(object1, object2);
    }
    phf(object1, object2);
}
