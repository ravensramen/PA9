#include "cloudLarge.h"

CloudLarge::CloudLarge(sf::Vector2f startingPos, sf::Vector2f endingPos, int speedType, int moveType)
{
	//starting position
	this->mStartPos.x = startingPos.x;
	this->mStartPos.y = startingPos.y;
	//ending position
	this->mEndPos.x = endingPos.x;
	this->mEndPos.y = endingPos.y;
	//move type
	this->mMoveType = moveType;
	//velocity
	this->mSpeedType = speedType;
	switch (speedType)
	{
	case SLOW:
	{
		if (this->mMoveType == HORIZONTAL)
		{
			this->mVelocityX = 90.f;
			this->mVelocityY = 0.f;
		}
		else if (this->mMoveType == VERTICAL)
		{
			this->mVelocityX = 0.f;
			this->mVelocityY = 90.f;
		}
	}break;
	case MEDIUM:
	{
		if (this->mMoveType == HORIZONTAL)
		{
			this->mVelocityX = 150.f;
			this->mVelocityY = 0.f;
		}
		else if (this->mMoveType == VERTICAL)
		{
			this->mVelocityX = 0.f;
			this->mVelocityY = 150.f;
		}
	}break;
	case FAST:
	{
		if (this->mMoveType == HORIZONTAL)
		{
			this->mVelocityX = 250.f;
			this->mVelocityY = 0.f;
		}
		else if (this->mMoveType == VERTICAL)
		{
			this->mVelocityX = 0.f;
			this->mVelocityY = 250.f;
		}
	}break;
	case EXFAST:
	{
		if (this->mMoveType == HORIZONTAL)
		{
			this->mVelocityX = 350.f;
			this->mVelocityY = 0.f;
		}
		else if (this->mMoveType == VERTICAL)
		{
			this->mVelocityX = 0.f;
			this->mVelocityY = 350.f;
		}
	}break;
	}
	//auto velocity adjustment for right->left movement
	if (this->mStartPos.x > 0)
	{
		this->mVelocityX *= -1;
	}
	//size of platform
	this->mPlatformVis.setSize({ 226.f, 104.f });
	this->mPlatformCol.setSize({ 191.f, 1.f });
	//set starting position of platform
	this->mPlatformVis.setPosition(startingPos);
	this->mPlatformCol.setPosition({ startingPos.x + 24.f, startingPos.y + 58.f });
	//texture
	if (this->mTexture.loadFromFile("largeCloud.png"))
	{
		this->mPlatformVis.setTexture(&this->mTexture);
	}
	//fill color
	this->mPlatformCol.setFillColor(sf::Color::Transparent);
}

void CloudLarge::resetPos(void)
{
	this->mPlatformCol.setPosition({ this->mStartPos.x + 24.f, this->mStartPos.y + 58.f });
	this->mPlatformVis.setPosition(this->mStartPos);
}
