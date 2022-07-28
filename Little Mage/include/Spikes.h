#pragma once
#include "StaticObjects.h"


class Spikes : public StaticObjects {

public:
	using StaticObjects::StaticObjects;

    Spikes(const Spikes&) = default;
    Spikes& operator=(const Spikes&) = default;
    Spikes(Spikes&&) = default;
    Spikes& operator=(Spikes&&) = default;

private:

};
