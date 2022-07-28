#pragma once
#include "StaticObjects.h"


class Fire : public StaticObjects {

public:
	using StaticObjects::StaticObjects;

    Fire(const Fire&) = default;
    Fire& operator=(const Fire&) = default;
    Fire(Fire&&) = default;
    Fire& operator=(Fire&&) = default;

private:

};
