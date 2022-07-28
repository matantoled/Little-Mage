#pragma once

#include "GameObjects.h"
#include "Resources.h"

#include <iostream>
#include <typeinfo>

// Sample struct for exception throwing
struct UnknownCollision : public std::runtime_error
{
    UnknownCollision(GameObjects& a, GameObjects& b)
        : std::runtime_error(std::string("Unknown collision of ") + typeid(a).name() + " and " + typeid(b).name())
    {
    }
};

void processCollision(GameObjects& object1, GameObjects& object2);
