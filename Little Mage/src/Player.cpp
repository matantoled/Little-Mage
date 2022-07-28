#pragma once
#include "Player.h"
#include <optional>

namespace
{
    std::optional<State> toState(sf::Keyboard::Key key)
    {
        switch (key)
        {
        case sf::Keyboard::Left:
            return State::Left;
        case sf::Keyboard::Right:
            return State::Right;
        case sf::Keyboard::Up:
            return State::Up;
        case sf::Keyboard::Space:
            return State::Stay;
        case sf::Keyboard::LControl:
            return State::Ctrl;
        default:
            return {};
        }
    }
} // end namespace

//=========================================================
Player::Player(sf::Vector2f location, Resources::Objects object) : MovingObjects(location, object) {

    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
    m_startPos = m_sprite.getPosition();
    m_animation.state(State::Stay);
}
//=========================================================
void Player::updateDir() {

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        m_dir = State::Right;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        m_dir = State::Left;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        m_dir = State::Up;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        m_dir = State::Ctrl;
    }
    else
        m_dir = State::Stay;
}
//=========================================================
void Player::update(const sf::Time delta)
{
    if (m_isDead and m_clock.getElapsedTime().asSeconds() > TIME_FOR_DEATH_PLAYER_ANIMATION) {
        updateDir();
        m_animation.state(m_dir);
        m_sprite.setPosition(m_startPos);
        m_isDead = false;
    }
    else if(!m_isDead) {
        movePlayer(delta);
    }
}
//=========================================================
void Player::movePlayer(const sf::Time delta) {

    sf::Vector2f newLoc;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        if (!m_pressJump and m_onGround) {
            m_pressJump = true;
            m_clock.restart();
            m_onGround = false;
        }

        m_elapsed = m_clock.getElapsedTime();
        if (m_pressJump) {
            newLoc = findNewLoc(sf::Keyboard::Up, delta.asSeconds());
            m_sprite.setPosition(newLoc);

        }
    }
    if (m_elapsed.asSeconds() > JUMP_SECONDS)
        m_pressJump = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        newLoc = findNewLoc(sf::Keyboard::Left, delta.asSeconds());
        m_sprite.setPosition(newLoc);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        newLoc = findNewLoc(sf::Keyboard::Right, delta.asSeconds());
        m_sprite.setPosition(newLoc);
    }

    m_sprite.move(sf::Vector2f(0, 1) * delta.asSeconds() * PlayerSpeed * (JUMP / 2));
}
//=========================================================
void Player::movePlayerDown() {

    m_sprite.move(sf::Vector2f(0, 1) * m_dt * PlayerSpeed * 2.f);
}
//=========================================================
const sf::Vector2f Player::findNewLoc(const sf::Keyboard::Key key, const float dt) const {

    //find player new location and return it
    switch (key) {
    case sf::Keyboard::Up:
        return { getSprite().getPosition().x,
            getSprite().getPosition().y + -PlayerSpeed * dt * JUMP };
    case sf::Keyboard::Left:
        return { getSprite().getPosition().x - PlayerSpeed * dt,
        getSprite().getPosition().y };
    case sf::Keyboard::Right:
        return { getSprite().getPosition().x + PlayerSpeed * dt,
            getSprite().getPosition().y };
    }
    throw std::runtime_error("Unknown Keyboard key");
}
//=========================================================
void Player::handlePlayerDeath()
{
    m_isDead = true;
    m_clock.restart();
    m_dir = State::Down;
    m_animation.state(m_dir);
}
//=========================================================
void Player::setPlayerState(State state)
{
    m_dir = state;
    m_animation.state(m_dir);
}
//=========================================================
void Player::updateAnimation(const sf::Time delta){

    m_animation.update(delta);
}
//=========================================================
const bool Player::getHaveKey() const
{
    return m_haveKey;
}
//=========================================================
void Player::setHaveKey(bool status)
{
    m_haveKey = status;
}
//=========================================================
const bool Player::getEnterDoor() const
{
    return m_enterDoor;
}
//=========================================================
void Player::setEnterDoor(bool status)
{
    m_enterDoor = status;
}
//=========================================================
void Player::setOnGround(bool status)
{
    m_onGround = status;
}
//=========================================================
void Player::setDt(float dt)
{
    m_dt = dt;
}
//=========================================================
const sf::Clock& Player::getPlayerClock() const
{
    return m_clock;
}
//=========================================================
const sf::Vector2f Player::getStartPos() const
{
    return m_startPos;
}
//=========================================================
const bool Player::getRightDir() const
{
    return m_rightDir;
}
//=========================================================
void Player::setRightDir(bool status)
{
    m_rightDir = status;
}
//=========================================================
