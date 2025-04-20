#include "cloudMedium.h"

CloudMedium::CloudMedium(sf::Vector2f startingPos, sf::Vector2f endingPos, int speedType, int moveType)
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
	//size of platform
	this->mPlatformVis.setSize({ 70.f, 20.f });
	this->mPlatformCol.setSize({ 70.f, 1.f });
	//set starting position of platform
	this->mPlatformVis.setPosition(startingPos);
	this->mPlatformCol.setPosition({ startingPos.x, startingPos.y + 10.f });
	//fill colors
	this->mPlatformVis.setFillColor(sf::Color::Transparent);
	this->mPlatformCol.setFillColor(sf::Color::Cyan);
}