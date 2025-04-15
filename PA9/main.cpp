#include <SFML/Graphics.hpp>

#include <SFML/System.hpp> //need this for time mechanics

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 700, 900 }), "wip");
 
    
    sf::Texture backgroundArt;
    if (!backgroundArt.loadFromFile("backgroundart.png")) {
        return -1; //return -1 if background image fails
    }
    sf::Sprite backgroundArtSprite(backgroundArt);

    //set sprite player image
    sf::Texture characterSprite;
    characterSprite.loadFromFile("forwardSprite.png"); //forward facing start
    //add precond/check (!image -> return -1)

    //set vector position for start
    sf::Vector2f initialPosition;
    initialPosition.x = 320; //access + assign vector location members
    initialPosition.y = 820;

    sf::Sprite characterForwardSprite(characterSprite);
    characterForwardSprite.setPosition(initialPosition);

    //code for key press movement
    float movementSpeed = .5f;
    sf::Vector2f moveLeft(-movementSpeed, 0); //vector to modify sprite to the left
    sf::Vector2f moveRight(+movementSpeed, 0);  
    sf::Vector2f moveUp(0, -movementSpeed);
    sf::Vector2f moveDown(0, +movementSpeed);

    //code for jumping movement +
    sf::Vector2f velocity(0.f, 0.f);
    bool isJumping = false;
    float gravity = 800.0f; //higher -> fall down faster
    float jumpStrength = -375.f; //lower -> jump higher 

    sf::Clock clock;

    while (window.isOpen())
    {

        //TIME MECHANICS (to slow jump)
      
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();


        while (const std::optional event = window.pollEvent()) //this while loop handles closing window (i think...)
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        //movement input based on arrow key press (might modify to wasd?)
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
            characterForwardSprite.move(moveLeft);
          
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            characterForwardSprite.move(moveRight);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) {
            characterForwardSprite.move(moveUp);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
            characterForwardSprite.move(moveDown);
        }

        //code to trigger jumping mechanic from static initial position
        if (!isJumping && sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Space)) {
            velocity.y = jumpStrength;
            isJumping = true;
        }

        if (isJumping) {
            velocity.y += gravity * dt;
            characterForwardSprite.move(sf::Vector2f(0.f, velocity.y * dt)); //gotta expicity case these a vectors, compiler thinks its a float...
            if (characterForwardSprite.getPosition().y >= 820.f) {
                characterForwardSprite.setPosition(sf::Vector2f(characterForwardSprite.getPosition().x, 820.f));
                velocity.y = 0;
                isJumping = false; //reset back to static position
            }
        }

        window.clear();
        window.draw(backgroundArtSprite);
        window.draw(characterForwardSprite); //character sprite called on top of background
     
        window.display();
    }
}