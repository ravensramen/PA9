#pragma once
#include "header.h"

class jetpack
{
public:
	jetpack();

	sf::Vector2f getPosition(void) const { return this->mJetpackItem.getPosition(); }
	sf::FloatRect getGlobalBounds(void) const { return this->mJetpackItem.getGlobalBounds(); }

	bool isPickedUp(const bool yesOrNo);
	void pickUp(void);
	void draw(sf::RenderWindow& window) const;
private:
	sf::Vector2f mPosition;
	sf::RectangleShape mJetpackItem; //set the position through rectangle
	sf::Texture mJetpackTexture;
};