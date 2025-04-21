#include "meteorHazard.h"

meteorHazard::meteorHazard(float startingXPos)
{
	this->mStartPos = (sf::Vector2f({ startingXPos, -70.f }));
	this->mMoveType = VERTICAL;
	this->mSpeedType = SLOW;
	this->mVelocityX = 0.f;
	this->mVelocityY = 90.f; //slow
	this->mHazard.setRadius(25.f);
	this->mHazard.setPosition(mStartPos);
	//texture
	//if (this->mTexture.loadFromFile(""))
	//{
	//	this->mHazard.setTexture(&this->mTexture);
	//}
	this->mHazard.setFillColor(sf::Color::Cyan);
	this->mEndPos = (sf::Vector2f({ startingXPos, 405.f}));
}
