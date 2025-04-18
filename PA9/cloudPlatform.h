
#include "header.h"

class CloudPlatform {
private:
	sf::RectangleShape visual;
	sf::RectangleShape collision;
	float velocityX;

public:
	CloudPlatform(sf::Vector2f startPos, float speed) {
		visual.setSize({ 35.f, 20.f });
		visual.setFillColor(sf::Color::Blue);
		visual.setPosition(startPos);

		collision.setSize({ 35.f, 1.f });
		collision.setFillColor(sf::Color::Cyan);
		collision.setPosition({ startPos.x, startPos.y + 10.f });

		velocityX = speed;
	}

	void update(float dt) {
		visual.move({ velocityX * dt, 0.f });
		collision.move({ velocityX * dt, 0.f });

		if (visual.getPosition().x > 700.f) {
			visual.setPosition({ -35.f, collision.getPosition().y });
		}
	}

	void draw(sf::RenderWindow& window) const {
		window.draw(visual);
		window.draw(collision);
	}

	const sf::RectangleShape& getCollisionShape() const {
		return collision;
	}

	float getVelocity() const {
		return this->velocityX;
	}
};