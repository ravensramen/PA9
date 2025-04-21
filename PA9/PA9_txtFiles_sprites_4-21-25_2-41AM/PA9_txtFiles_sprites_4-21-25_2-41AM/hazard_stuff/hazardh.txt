#pragma once
#include "flyingObject.h"

class hazard : public flyingObject
{
public:
	hazard();

	const sf::CircleShape& getCollisionShape() const;
	sf::Vector2f getPosition(void) const;
	float getRadius(void) const;

	void update(float dt);
	void draw(sf::RenderWindow& window) const;
	void atEndReset(void);
	void resetPos(void);

protected:
	sf::CircleShape mHazard;
	sf::Texture mTexture;
};