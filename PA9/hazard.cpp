#include "hazard.h"

hazard::hazard()
{
}

const sf::CircleShape& hazard::getCollisionShape() const
{
	return this->mHazard;
}

sf::Vector2f hazard::getPosition(void) const
{
	return this->mHazard.getPosition();
}

float hazard::getRadius(void) const
{
	return this->mHazard.getRadius();
}

void hazard::update(float dt)
{
	if (this->mMoveType == HORIZONTAL)
	{
		this->mHazard.move({ this->mVelocityX * dt, 0.f });
	}
	else if (this->mMoveType == VERTICAL)
	{
		this->mHazard.move({ 0.f, this->mVelocityY * dt });
	}
	else if (this->mMoveType == DIAGONAL)
	{
		this->mHazard.move({ this->mVelocityX * dt, this->mVelocityY * dt });
	}
	atEndReset();
}

void hazard::draw(sf::RenderWindow& window) const
{
	window.draw(this->mHazard);
}

void hazard::atEndReset(void)
{
	if (this->mMoveType == HORIZONTAL)
	{
		if (this->mStartPos.x < 0)
		{
			if (this->mEndPos.x < this->mHazard.getPosition().x)
			{
				resetPos();
			}
		}
		else
		{
			if (this->mEndPos.x > this->mHazard.getPosition().x)
			{
				resetPos();
			}
		}
	}
	else if (this->mMoveType == VERTICAL)
	{
		if (this->mEndPos.y < this->mHazard.getPosition().y)
		{
			resetPos();
		}
	}
	else if (this->mMoveType == DIAGONAL)
	{
		if (this->mEndPos.y < this->mHazard.getPosition().y)
		{
			resetPos();
		}
	}
}

void hazard::resetPos(void)
{
	this->mHazard.setPosition(this->mStartPos);
}
