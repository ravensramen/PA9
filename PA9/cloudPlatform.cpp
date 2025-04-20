#include "cloudPlatform.h"

CloudPlatform::CloudPlatform()
{
	this->mPlatformVis;
	this->mPlatformCol;
	this->mStartPos.x = 0.f;
	this->mStartPos.y = 0.f;
	this->mEndPos.x = 0.f;
	this->mEndPos.y = 0.f;
	this->mMoveType = 0;
	this->mSpeedType = 0;
	this->mVelocityX = 0.f;
	this->mVelocityY = 0.f;

}

//getters
const sf::RectangleShape& CloudPlatform::getCollisionShape() const
{
	return this->mPlatformCol;
}

float CloudPlatform::getVelocityX(void) const
{
	return this->mVelocityX;
}

float CloudPlatform::getVelocityY(void) const
{
	return this->mVelocityY;
}

sf::Vector2f CloudPlatform::getPosition(void) const
{
	return this->mPlatformCol.getPosition();
}

sf::Vector2f CloudPlatform::getSize(void) const
{
	return this->mPlatformCol.getSize();
}

void CloudPlatform::atEndReset(void)
{
	if (this->mMoveType == HORIZONTAL)
	{
		if (this->mEndPos.x < this->mPlatformVis.getPosition().x)
		{
			resetPos();
		}
	}
	else if (this->mMoveType == VERTICAL)
	{
		if (this->mEndPos.y < this->mPlatformVis.getPosition().y)
		{
			resetPos();
		}
	}
}

void CloudPlatform::startOrEndReverse(void)
{
	//this is empty for now
}

//helper
void CloudPlatform::resetPos(void)
{
	this->mPlatformCol.setPosition({ this->mStartPos.x, this->mStartPos.y + 10.f });
	this->mPlatformVis.setPosition(this->mStartPos);
}

//helper
void CloudPlatform::reverseDirection(void)
{
	switch (this->mMoveType)
	{
	case HORIZONTAL:
	{
		reverseHorizontal();
	}break;
	case VERTICAL:
	{
		reverseVertical();
	}break;
	}
}

//helper
void CloudPlatform::reverseHorizontal(void)
{
	this->mVelocityX *= -1;
}

//helper
void CloudPlatform::reverseVertical(void)
{
	this->mVelocityY *= -1;
}

void CloudPlatform::update(float dt)
{

	if (this->mMoveType == HORIZONTAL)
	{
		this->mPlatformVis.move({ this->mVelocityX * dt, 0.f });
		this->mPlatformCol.move({ this->mVelocityX * dt, 0.f });
	}
	else if (this->mMoveType == VERTICAL)
	{
		this->mPlatformVis.move({ 0.f, this->mVelocityY * dt });
		this->mPlatformCol.move({ 0.f, this->mVelocityY * dt });
	}
	atEndReset();
}

void CloudPlatform::draw(sf::RenderWindow& window) const
{
	
	window.draw(this->mPlatformVis);
	window.draw(this->mPlatformCol);

}

