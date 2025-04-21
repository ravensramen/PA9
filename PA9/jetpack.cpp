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

bool jetpack::isPickedUp(const bool yesOrNo)
{
	if (this->mPosition.x != 339.f && this->mPosition.y != 401.f)
	{
		return true;
	}
	return false;
}

//move it off the map when it's picked up
void jetpack::pickUp(void)
{
	this->mPosition.x = 800.f;
}

void jetpack::draw(sf::RenderWindow& window) const
{
	window.draw(this->mJetpackItem);
}
