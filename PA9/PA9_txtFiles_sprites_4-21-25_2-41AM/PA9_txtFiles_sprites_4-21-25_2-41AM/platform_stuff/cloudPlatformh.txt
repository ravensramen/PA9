#pragma once
#include "flyingObject.h"

class CloudPlatform : public flyingObject
{
public:
	CloudPlatform();

	const sf::RectangleShape& getCollisionShape() const;
	sf::Vector2f getPosition(void) const;
	sf::Vector2f getSize(void) const;

	void atEndReset(void);
	void startOrEndReverse(void);
	virtual void resetPos(void);
	void reverseDirection(void);
	void reverseHorizontal(void);
	void reverseVertical(void);

	void update(float dt);
	void draw(sf::RenderWindow& window) const;

protected:
	sf::RectangleShape mPlatformVis;
	sf::RectangleShape mPlatformCol;
	sf::Texture mTexture;
};