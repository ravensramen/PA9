#pragma once
#include "header.h"

class CloudPlatform
{
public:
	CloudPlatform();

	const sf::RectangleShape& getCollisionShape() const;
	float getVelocityX(void) const;
	float getVelocityY(void) const;
	sf::Vector2f getPosition(void) const;
	sf::Vector2f getSize(void) const;

	void atEndReset(void);
	void startOrEndReverse(void);
	void resetPos(void);
	void reverseDirection(void);
	void reverseHorizontal(void);
	void reverseVertical(void);

	void update(float dt);
	void draw(sf::RenderWindow& window) const;


protected:

	sf::RectangleShape mPlatformVis;
	sf::RectangleShape mPlatformCol;
	sf::Vector2f mStartPos;
	sf::Vector2f mEndPos;
	int mMoveType;
	int mSpeedType;
	float mVelocityX;
	float mVelocityY;
};