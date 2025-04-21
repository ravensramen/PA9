#pragma once
#include "hazard.h"

class asteroidHazard : public hazard
{
public:
	asteroidHazard(sf::Vector2f startingPos); //horizontal movement
};