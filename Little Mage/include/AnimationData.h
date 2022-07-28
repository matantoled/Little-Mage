#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <vector>

struct AnimationData
{
    using ListType = std::vector<sf::IntRect>;
    using DataType = std::unordered_map<State, ListType>;
    DataType m_data;
};
