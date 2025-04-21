#include "starHazard.h"

starHazard::starHazard(sf::Vector2f startingPos, int LeftorRight)
{
	this->mStartPos = (startingPos);
	this->mMoveType = DIAGONAL;
	this->mSpeedType = FAST;
	if (LeftorRight == RIGHT)
	{
		this->mVelocityX = 250.f; //fast
	}
	else if (LeftorRight == LEFT)
	{
		this->mVelocityX = -250.f; //fast
	}
	this->mVelocityY = 250.f;
	this->mHazard.setRadius(5.f);
	this->mHazard.setPosition(this->mStartPos);
	//texture
	//if (this->mTexture.loadFromFile(""))
	//{
	//	this->mHazard.setTexture(&this->mTexture);
	//}
	this->mHazard.setFillColor(sf::Color::Cyan);
	this->mEndPos = (sf::Vector2f(0.f, 400.f - this->mHazard.getRadius() * 2));
}
