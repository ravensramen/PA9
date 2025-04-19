#pragma once
#include "cloudPlatform.h"

class CloudLarge : public CloudPlatform
{
public:
	CloudLarge(sf::Vector2f startingPos, sf::Vector2f endingPos, int speedType, int moveType);
};