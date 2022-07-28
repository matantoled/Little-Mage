#pragma once
#include "StaticObjects.h"


class Wall : public StaticObjects {

public:
	using StaticObjects::StaticObjects;

    Wall(const Wall&) = default;
    Wall& operator=(const Wall&) = default;
    Wall(Wall&&) = default;
    Wall& operator=(Wall&&) = default;

private:

};
