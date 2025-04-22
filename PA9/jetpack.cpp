#include "jetpack.h"

jetpack::jetpack()
{
	this->mJetpackItem.setSize({ 25.f, 22.f });
	//mjetpackItem is a rectangle shape!
	if (this->mJetpackTexture.loadFromFile("jetpack.png"))
	{
		this->mJetpackItem.setTexture(&this->mJetpackTexture);
	}
	this->mPosition.x = 339.f;
	this->mPosition.y = 401.f;
	this->mJetpackItem.setPosition(this->mPosition);
	//this->mJetpackItem.setFillColor(sf::Color::Green);
}

bool jetpack::isPickedUp(void)
{
	if (this->mJetpackItem.getFillColor() == sf::Color::Transparent)
	{
		return true;
	}
	return false;
}

void jetpack::pickUp(void)
{
	this->mJetpackItem.setFillColor(sf::Color::Transparent);
}

void jetpack::draw(sf::RenderWindow& window) const
{
	window.draw(this->mJetpackItem);
}
