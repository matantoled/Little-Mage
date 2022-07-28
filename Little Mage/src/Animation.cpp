#pragma once
#include "Animation.h"


Animation::Animation(const AnimationData& data, const State dir, sf::Sprite& sprite)
    : m_data(data), m_dir(dir), m_sprite(sprite){
    m_sprite.setTexture(Resources::instance().texture());
    update();
}

void Animation::state(const State dir){

    if (m_dir == dir)
        return;

    m_dir = dir;
    m_index = 0;
    update();
}

void Animation::update(const sf::Time delta){

    m_elapsed += delta;
    if (m_elapsed >= AnimationTime){
        m_elapsed -= AnimationTime;
        ++m_index;
        m_index %= m_data.m_data.find(m_dir)->second.size();
        update();
    }
}

void Animation::update()
{
    m_sprite.setTextureRect(m_data.m_data.find(m_dir)->second[m_index]);
    if (m_dir == State::Left) 
        m_sprite.setScale(SCALE_TO_THE_LEFT);
    else if (m_dir == State::Right) 
        m_sprite.setScale(SCALE_TO_THE_RIGHT);
}
