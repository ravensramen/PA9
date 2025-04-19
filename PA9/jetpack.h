#pragma once
#include "header.h"

class jetpack
{
public:
	jetpack() {
		/*   sf::Texture jetPackTexture;
			 if (!jetPackTexture.loadFromFile("jetpacktexture.png"))
			  return -1;*/
	}
	sf::Vector2f getPosition(void) const { return this->mJetpackItem.getPosition(); }
	sf::FloatRect getGlobalBounds(void) const { return this->mJetpackItem.getGlobalBounds(); }
	bool pickedUp(bool yesOrNo) {/*change its position to off the map*/ }
private:
	sf::RectangleShape mJetpackItem; //set the position through rectangle
	sf::Texture mJetpackTexure;
};