#pragma once
#include "hazard.h"

class meteorHazard : public hazard
{
public:
	meteorHazard(sf::Vector2f startingPos); //vertical movement from top to bottom
};
