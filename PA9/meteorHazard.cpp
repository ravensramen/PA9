#include "meteorHazard.h"

meteorHazard::meteorHazard(sf::Vector2f startingPos)
{
	this->mStartPos = (startingPos);
	this->mMoveType = VERTICAL;
	this->mSpeedType = SLOW;
	this->mVelocityX = 0.f;
	this->mVelocityY = 90.f; //slow
	this->mHazard.setRadius(25.f);
	this->mHazard.setPosition(mStartPos);
	//texture
	if (this->mTexture.loadFromFile("meteorHazard.png"))
	{
		this->mHazard.setTexture(&this->mTexture);
	}
	//this->mHazard.setFillColor(sf::Color::Cyan);
	this->mEndPos = (sf::Vector2f({ startingPos.x, 355.f }));
}
