#pragma once
#include "hazard.h"

class starHazard : public hazard
{
public:
	starHazard(sf::Vector2f startingPos, int LeftorRight); //diagonal movement top to bottom
};
