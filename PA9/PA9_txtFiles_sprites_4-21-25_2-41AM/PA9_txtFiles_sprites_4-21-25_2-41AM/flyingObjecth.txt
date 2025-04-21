#pragma once
#include "header.h"

class flyingObject
{
public:
	flyingObject() { this->mMoveType = 0; this->mSpeedType = 0; this->mVelocityX = 0; this->mVelocityY = 0; };

	float getVelocityX(void) const { return this->mVelocityX; };
	float getVelocityY(void) const { return this->mVelocityY; };
protected:
	sf::Vector2f mStartPos;
	sf::Vector2f mEndPos;
	int mMoveType;
	int mSpeedType;
	float mVelocityX;
	float mVelocityY;
};