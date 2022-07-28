#pragma once
#include "StaticObjects.h"


class Door : public StaticObjects {

public:
	using StaticObjects::StaticObjects;

    Door(const Door&) = default;
    Door& operator=(const Door&) = default;
    Door(Door&&) = default;
    Door& operator=(Door&&) = default;

    const State getState() const { return m_dir; }

private:

};
