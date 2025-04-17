//IGNORE ALL TS, better ver of obstacles in main :))



#include "header.h"
#include <optional>
//this is the class for cloud objects
//in the first half of the level, user can only progress upwards by jumping on clouds
//most similar to logs in frogger

//add appearing+disappearing storm clouds to inherit and provide a extra challenge (like turtles in frogger)

class CloudVehicle {
public:
    CloudVehicle(const sf::Vector2f& startPos, float speed);

    void update(float dt);
    void draw(sf::RenderWindow& window);
    sf::FloatRect getBounds() const;

private:
    sf::Texture cloudTexture;
    std::optional<sf::Sprite> cloudSprite; // used instead of default sprite
    float speed;
};

// constructor
CloudVehicle::CloudVehicle(const sf::Vector2f& startPos, float speed)
    : speed(speed)
{
    if (!cloudTexture.loadFromFile("mediumCloud.png")) {
        std::cerr << "Error loading cloud image\n";
        return;
    }

    cloudSprite.emplace(cloudTexture); // construct sprite with texture
    cloudSprite->setPosition(startPos);
}

// movement
void CloudVehicle::update(float dt) {
    if (cloudSprite.has_value()) {
        cloudSprite->move(sf::Vector2f(speed * dt, 0.f));
    }
}

// drawing
void CloudVehicle::draw(sf::RenderWindow& window) {
    if (cloudSprite.has_value()) {
        window.draw(*cloudSprite);
    }
}

// get bounds
sf::FloatRect CloudVehicle::getBounds() const {
    if (cloudSprite.has_value()) {
        return cloudSprite->getGlobalBounds();
    }
    else {
        return sf::FloatRect(); // empty bounds if sprite failed
    }
}