#pragma once
#include "header.h"

class goal
{
public:
	goal()
	{
		this->mGoal.setSize({ 70.f, 70.f });
		this->mMinXRange = 0;
		this->mMaxXRange = 700 - this->mGoal.getSize().x;
		if (this->mTexture.loadFromFile("planet.png"))
		{
			this->mGoal.setTexture(&this->mTexture);
		}
		this->mCollision.setSize({ this->mGoal.getSize().x, 20.f });

		this->mPosition.x = (std::rand() % 9) * 70; //randomize within 10 blocks of 70 pixels.
		this->mPosition.y = 0.f;
		this->mGoal.setPosition(mPosition);
		this->mCollision.setPosition(mPosition);

		//this->mGoal.setFillColor(sf::Color::Cyan);
		this->mCollision.setFillColor(sf::Color::Transparent);
	};
	const sf::RectangleShape& getCollisionShape() const { return this->mCollision; };
	void draw(sf::RenderWindow& window) const { window.draw(this->mCollision); window.draw(this->mGoal); };
private:
	sf::RectangleShape mCollision;
	sf::RectangleShape mGoal;
	sf::Texture mTexture;
	sf::Vector2f mPosition;
	int mMinXRange;
	int mMaxXRange;
};