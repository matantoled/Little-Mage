#pragma once
#include "State.h"
#include "AnimationData.h"
#include "Resources.h"

class Animation
{
public:
    Animation(const AnimationData& data, const State dir, sf::Sprite& sprite);
    virtual ~Animation() = default;

    Animation(const Animation&) = default;
    Animation& operator=(const Animation&) = default;
    Animation(Animation&&) = default;
    Animation& operator=(Animation&&) = default;

    void state(const State dir);
    void update(const sf::Time delta);

private:
    void update();
    const AnimationData& m_data;
    sf::Time m_elapsed = {};
    State m_dir = State::Stay;
    int m_index = 0;
    sf::Sprite& m_sprite;

};