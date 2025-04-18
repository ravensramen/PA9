#include "header.h"
#include "clouds.h"

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
    sf::Texture forwardTexture, leftTexture, rightTexture, deadTexture;

    if (!forwardTexture.loadFromFile("forwardSprite.png") ||
         !leftTexture.loadFromFile("leftSprite.png") ||
         !rightTexture.loadFromFile("rightSprite.png")||!deadTexture.loadFromFile("deadSprite.png")) {
         return -1; // one or more files didn't load
    }

    //set vector position for start
    sf::Vector2f initialPosition;
    initialPosition.x = 320; //access + assign vector location members
    initialPosition.y = 820;

    sf::Sprite characterForwardSprite(forwardTexture);
    characterForwardSprite.setPosition(initialPosition);


    //code for key press movement
    float movementSpeed = .2f;
    sf::Vector2f moveLeft(-movementSpeed, 0); //vector to modify sprite to the left
    sf::Vector2f moveRight(+movementSpeed, 0);  
    sf::Vector2f moveUp(0, -movementSpeed);
    sf::Vector2f moveDown(0, +movementSpeed);

    //code for jumping movement +
    sf::Vector2f velocity(0.f, 0.f);
    bool isJumping = false;
    float gravity = 800.0f; //higher -> fall down faster
    float jumpStrength = -375.f; //lower -> jump higher 


    //-----------------------------------platform visuals-----------------------------------
    sf::RectangleShape platformVis({ 35.f, 20.f });
    sf::Vector2f platformVisPos({ -35.f, 795.f });//the platform itself should be at the vertical middle
    platformVis.setFillColor(sf::Color().Blue); //this will be replaced with a texture
    platformVis.setPosition(platformVisPos);
    float platformVisVelocityX = .04; //only moving horizontally for now
    float platformVisVelocityY = 0;
    //----------------------------------platform collision----------------------------------
    //platform rectangle base (this is the smallest "spawnable" platform)
    sf::RectangleShape platform({ 35.f, 1.f }); //(this is the smallest "spawnable" platform)(ideally only the x value will be changed)
    sf::Vector2f platformPos({ -35.f, 805.f });//should be in the vertical middle of the visual
    platform.setFillColor(sf::Color().Cyan); //this will be replaced with transparent color
    platform.setPosition(platformPos); //lowest platform (highest is at 485.f)
    float platformVelocityX = .04; //only moving horizontally for now
    float platformVelocityY = 0;


    sf::Clock clock;

    sf::Music backgroundMusic; //add more songs! and sound effects
    if (!backgroundMusic.openFromFile("misato.mp3")) {
        return -1; // error loading music file
    }
    backgroundMusic.setLooping(true); // loop the music
    backgroundMusic.setVolume(10.f); // optional
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

    //checkpoint for cloud level
    float checkpointY = 375.f; // example value: lowest allowed position
    bool checkpointReached = false;


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
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)&& !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
            characterForwardSprite.setTexture(forwardTexture);
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

            // Predict the new Y position
            float predictedY = characterForwardSprite.getPosition().y + velocity.y * dt;

            // If checkpoint is reached and predicted position would go below it, clamp it
            if (checkpointReached && predictedY > checkpointY) {
                predictedY = checkpointY;
                velocity.y = 0;      // stop falling
                isJumping = false;   // treat as landed
            }

            characterForwardSprite.setPosition(sf::Vector2f(characterForwardSprite.getPosition().x, predictedY));

            // Ground detection after jump
            if (predictedY >= 820.f) {
                float fallDistance = 820.f - maxJumpHeight;
                if (fallDistance > deathFallThreshold) {
                    deathSound.play();
                    isDead = true;
                }

                characterForwardSprite.setPosition(sf::Vector2f(characterForwardSprite.getPosition().x, 820.f));
                velocity.y = 0;
                isJumping = false;
            }
        }

        //----------------------------------platform visuals------------------------------------

//bouncing horizontally off walls
//if (platformVisPos.x < 0.f || platformVisPos.x > 665.f)
//{
//    platformVisVelocityX *= -1;
//}

//resetting to the left side of the screen
        if (platformVisPos.x > 700.f)
        {
            platformVisPos.x = -35.f;
        }

        platformVisPos.x += platformVisVelocityX;
        platformVis.setPosition(platformVisPos);
        //---------------------------------platform collision-------------------------------------

        //bouncing horizontally off walls
        //if (platformPos.x < 0.f || platformPos.x > 665.f)
        //{
        //    platformVelocityX *= -1;
        //}

        //resetting to the left side of the screen
        if (platformPos.x > 700.f)
        {
            platformPos.x = -35.f;
        }

        platformPos.x += platformVelocityX;
        platform.setPosition(platformPos);
        //-----------------------------character platform interaction---------------------------

        //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
        if ((int)characterForwardSprite.getPosition().y + 52 == platformPos.y - 1)
        {
            //if the character's center is within the width of the platform
            if (platform.getPosition().x < characterForwardSprite.getPosition().x + 21.f && characterForwardSprite.getPosition().x + 21.f < (platform.getPosition().x + platform.getSize().x))
            {
                isJumping = false; //without this the character falls through the platform after about 1 second
                characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + platformVelocityX, platformPos.y - 53.f));
            }
            else
            {
                isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
            }
        }

        if (isDead) {
            //logic to save score and exit gameplay
            characterForwardSprite.setTexture(deadTexture);
            window.waitEvent(sf::Time::Zero); //infinite pause?
        }

        sf::Vector2f pos = characterForwardSprite.getPosition();

        // Trigger checkpoint when crossing the line going up
        if (!checkpointReached && pos.y < checkpointY) {
            checkpointReached = true;
        }

        // Clamp Y so player can't drop below once checkpoint is reached
        if (checkpointReached && !isJumping && pos.y > checkpointY) {
            pos.y = checkpointY;
            characterForwardSprite.setPosition(pos);
        }

        
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

        window.draw(platformVis); //the part of the platform that will be visible 
        window.draw(platform); //the part of the platform that will be invisible (collision)


        window.draw(characterForwardSprite); //character sprite called on top of background
     
        window.display();
    }
}