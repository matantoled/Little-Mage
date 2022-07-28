#include "State.h"

#include <stdexcept>

State opposite(State dir)
{
    switch (dir)
    {
        case State::Up:
            return State::Down;
        case State::Down:
            return State::Up;
        case State::Right:
            return State::Left;
        case State::Left:
            return State::Right;
        case State::Stay:
            return State::Stay;
        case State::Ctrl:
            return State::Ctrl;
        default:
            throw std::runtime_error("Unknown State");
    }
}

sf::Vector2f toVector(State dir)
{
    switch (dir)
    {
        case State::Up:
            return { 0, -1 };
        case State::Down:
            return { 0, 1 };
        case State::Right:
            return { 1, 0 };
        case State::Left:
            return { -1, 0 };
        case State::Stay:
            return { 0, 0 };
        case State::Ctrl:
            return { 0, 0 };
        default:
            throw std::runtime_error("Unknown State");
    }
}
