#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>//for sweet tunes + sound effects
#include <SFML/System.hpp> //need this for time mechanics

//create object class for cloud obstacles (with a derived class of more complex obstacles)
//^^similar, but with space obstacles 2

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 700, 900 }), "wip");
 
    
    sf::Texture backgroundArt;
    if (!backgroundArt.loadFromFile("backgroundart.png")) {
        return -1; //return -1 if background image fails
    }
    sf::Sprite backgroundArtSprite(backgroundArt);
  
    //set sprite player image
    sf::Texture forwardTexture, leftTexture, rightTexture;

    if (!forwardTexture.loadFromFile("forwardSprite.png") ||
         !leftTexture.loadFromFile("leftSprite.png") ||
         !rightTexture.loadFromFile("rightSprite.png")) {
         return -1; // one or more files didn't load
    }

    //set vector position for start
    sf::Vector2f initialPosition;
    initialPosition.x = 320; //access + assign vector location members
    initialPosition.y = 820;

    sf::Sprite characterForwardSprite(forwardTexture);
    characterForwardSprite.setPosition(initialPosition);


    //code for key press movement
    float movementSpeed = .25f;
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

    sf::Music backgroundMusic; //add more songs! and sound effects
    if (!backgroundMusic.openFromFile("misato.mp3")) {
        return -1; // error loading music file
    }
    backgroundMusic.setLooping(true); // loop the music
    backgroundMusic.setVolume(20.f); // optional
    backgroundMusic.play();

    //jump sound
    sf::SoundBuffer jumpBuffer;
    if (!jumpBuffer.loadFromFile("jump.wav"))
        return -1;
    sf::Sound jumpSound(jumpBuffer);
    jumpSound.setVolume(80.f);

    //death sound
    sf::SoundBuffer deathBuffer;
    if (!deathBuffer.loadFromFile("death.mp3")) return -1;
    sf::Sound deathSound(deathBuffer);
    deathSound.setVolume(80.f);

    //falling death conditions
    float maxJumpHeight = 820.f; // initial ground height
    float deathFallThreshold = 200.f; // distance that causes death 
    bool isDead = false;

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
            characterForwardSprite.setTexture(leftTexture);
          
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            characterForwardSprite.move(moveRight);
            characterForwardSprite.setTexture(rightTexture);
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
            maxJumpHeight = characterForwardSprite.getPosition().y; //save conditions for death
            jumpSound.play();
        }

        if (isJumping) {

            float currentY = characterForwardSprite.getPosition().y;
            if (currentY < maxJumpHeight) {
                maxJumpHeight = currentY;
            }

            velocity.y += gravity * dt;
            characterForwardSprite.move(sf::Vector2f(0.f, velocity.y * dt)); //gotta expicity case these a vectors, compiler thinks its a float...
            if (characterForwardSprite.getPosition().y >= 820.f) {

                float fallDistance = 820.f - maxJumpHeight; //if fall after jump is greater than max jump height -> death
                if (fallDistance > deathFallThreshold) {
                    deathSound.play();
                    isDead = true;
                }


                characterForwardSprite.setPosition(sf::Vector2f(characterForwardSprite.getPosition().x, 820.f));
                velocity.y = 0;
                isJumping = false; //reset back to static position
            }
        }

        if (isDead) {
            //logic to save score and exit gameplay

            //window.close();
        }

        sf::Vector2f pos = characterForwardSprite.getPosition();
        auto bounds = characterForwardSprite.getGlobalBounds();

        // INSURE SPRITE CANT LEAVE CONSOLE
        if (pos.x < 0) //bound x
            pos.x = 0;
        if (pos.x > 700 - bounds.size.x)
            pos.x = 700 - bounds.size.x;

        // bound y
        if (pos.y < 0)
            pos.y = 0;
        if (pos.y > 900 - bounds.size.y)
            pos.y = 900 - bounds.size.y;

        characterForwardSprite.setPosition(pos);

        window.clear();
        window.draw(backgroundArtSprite);
        window.draw(characterForwardSprite); //character sprite called on top of background
     
        window.display();
    }
}