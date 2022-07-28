#pragma once
#include "Ghost.h"
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
        case sf::Keyboard::Down:
            return State::Down;
        case sf::Keyboard::Space:
            return State::Stay;
        case sf::Keyboard::LControl:
            return State::Stay;
        default:
            return {};
        }
    }
} // end namespace

//=========================================================
void Ghost::update(sf::Time delta)
{
    if (getWasShot() and m_clock.getElapsedTime().asSeconds() >= TIME_FOR_DEATH_GHOST_ANIMATION) {
        m_isDead = true;
        return;
    }
    if (m_clock.getElapsedTime().asSeconds() >= TIME_FOR_CHANGE_GHOST_DIR)
    {
        m_clock.restart();
        m_dir = static_cast<State>(rand() % static_cast<int>(NUM_OF_DIRECTIONS));
        m_animation.state(m_dir);
    }

    m_prevLocation = m_sprite.getPosition();

    m_sprite.move(toVector(m_dir) * delta.asSeconds() * GhostSpeed);
    m_animation.update(delta);
}
//=========================================================
void Ghost::changeDir() {
    m_clock.restart();
    m_dir = static_cast<State>(rand() % static_cast<int>(NUM_OF_DIRECTIONS));
    m_animation.state(m_dir);
}
//=========================================================
void Ghost::changeAnimState(State state) {
    m_clock.restart();

    m_dir = State::Ctrl;
    if (state == State::Right) {
        m_sprite.setScale(SCALE_TO_THE_LEFT);
    }
    else if (state == State::Left) {
        m_sprite.setScale(SCALE_TO_THE_RIGHT);
    }
    m_animation.state(m_dir);
}
//=========================================================
const sf::Vector2f Ghost::findNewLoc(const sf::Keyboard::Key key, const float dt) const {

    //find player new location and return it
    switch (key) {
    case sf::Keyboard::Up:
        return { getSprite().getPosition().x,
            getSprite().getPosition().y + -GhostSpeed * dt * 2 };
    case sf::Keyboard::Down:
        return { getSprite().getPosition().x,
        getSprite().getPosition().y + GhostSpeed * dt };
    case sf::Keyboard::Left:
        return { getSprite().getPosition().x - GhostSpeed * dt,
        getSprite().getPosition().y };
    case sf::Keyboard::Right:
        return { getSprite().getPosition().x + GhostSpeed * dt,
            getSprite().getPosition().y };
    }
    throw std::runtime_error("Unknown Keyboard key");
}
//=========================================================

Ghost::Ghost(sf::Vector2f location, Resources::Objects object) : Enemy( location, object) {

    m_sprite.setOrigin(m_sprite.getGlobalBounds().width / 2.f, m_sprite.getGlobalBounds().height / 2.f);
}
//=========================================================