#include "asteroidHazard.h"

asteroidHazard::asteroidHazard(sf::Vector2f startingPos)
{
	this->mStartPos = (startingPos);
	this->mMoveType = HORIZONTAL;
	this->mSpeedType = MEDIUM;
	if (this->mStartPos.x < 0)
	{
		this->mVelocityX = 150.f; //medium
	}
	else
	{
		this->mVelocityX = -150.f; //medium
	}
	this->mVelocityY = 0.f;
	this->mHazard.setRadius(35.f);
	this->mHazard.setPosition(mStartPos);
	//texture
	if (this->mTexture.loadFromFile("asteroidHazard.png"))
	{
		this->mHazard.setTexture(&this->mTexture);
	}
	//this->mHazard.setFillColor(sf::Color::Cyan);
	if (this->mStartPos.x < 0)
	{
		this->mEndPos = (sf::Vector2f(750.f + this->mHazard.getRadius() * 2, this->mStartPos.y));
	}
	else
	{
		this->mEndPos = (sf::Vector2f(0 - this->mHazard.getRadius() * 2, this->mStartPos.y));
	}
}


