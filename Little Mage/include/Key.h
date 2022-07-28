#pragma once
#include "StaticObjects.h"


class Key : public StaticObjects {

public:
	using StaticObjects::StaticObjects;

    Key(const Key&) = default;
    Key& operator=(const Key&) = default;
    Key(Key&&) = default;
    Key& operator=(Key&&) = default;

private:

};