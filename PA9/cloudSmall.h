#pragma once
#include "cloudPlatform.h"

class CloudSmall : public CloudPlatform
{
public:
	CloudSmall(sf::Vector2f startingPos, sf::Vector2f endingPos, int speedType = 0, int moveType = 0);
};