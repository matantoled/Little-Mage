#pragma once

#include <SFML/Graphics.hpp>

enum class State
{
    Up,
    Down,
    Right,
    Left,
    Stay,
    Ctrl,
    Max,
};

State opposite(State dir);
sf::Vector2f toVector(State dir);
