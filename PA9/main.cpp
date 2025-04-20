#include "character.h"
#include "mainHelperFunctions.h" //includes cloud functions and a copy of the header 

int main()
{
    sf::RenderWindow window(sf::VideoMode({ 700, 900 }), "wip");

    sf::Texture backgroundArt;
    if (!backgroundArt.loadFromFile("backgroundArt.png")) {
        return -1; //return -1 if background image fails
    }
    sf::Texture backgroundGameOver;
    if (!backgroundGameOver.loadFromFile("backgroundGameover.PNG")) {
        return -1;
    }

    sf::Sprite backgroundArtSprite(backgroundArt);

    sf::Texture rulesTexture;
    if (!rulesTexture.loadFromFile("rulesPopup.png")) {
        return -1;
    }

    //set sprite player image
    sf::Texture forwardTexture, leftTexture, rightTexture, deadTexture;

    if (!forwardTexture.loadFromFile("forwardSprite.png") ||
        !leftTexture.loadFromFile("leftSprite.png") ||
        !rightTexture.loadFromFile("rightSprite.png") || !deadTexture.loadFromFile("deadSprite.png")) {
        return -1; // one or more files didn't load
    }
    ///CLOUD TEXTURES
    sf::Texture smallCloudTex, mediumCloudTex, largeCloudTex; 

    if (!smallCloudTex.loadFromFile("smallCloud.PNG") ||
        !mediumCloudTex.loadFromFile("mediumCloud.png") ||
        !largeCloudTex.loadFromFile("largeCloud.png")) {
        return -1;
    }
    ///

    //set vector position for start
    sf::Vector2f initialPosition;
    initialPosition.x = 320; //access + assign vector location members
    initialPosition.y = 820;

    sf::Sprite characterForwardSprite(forwardTexture);
    characterForwardSprite.setPosition(initialPosition);


    //code for key press movement
    float movementSpeed = .2f; //had to speed up after adding clouds
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


    //testing cloud platforms (start, end, speed, movement type)
    CloudSmall c1(sf::Vector2f(-35.f, 795.f), sf::Vector2f(700.f, 795.f), SLOW, HORIZONTAL);
    CloudMedium c2(sf::Vector2f(-70.f, 750.f), sf::Vector2f(735.f, 750.f), MEDIUM, HORIZONTAL);
    CloudLarge c3(sf::Vector2f(-105.f, 710.f), sf::Vector2f(770.f, 710.f), FAST, HORIZONTAL);
    CloudSmall c4(sf::Vector2f(-35.f, 670.f), sf::Vector2f(700.f, 670.f), EXFAST, HORIZONTAL);


    while (window.isOpen())
    {
        float dt = clock.restart().asSeconds(); //for cloud logic


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
        if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
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

        //-----------------------------character platform interaction---------------------------

        //cloud updates (i'm sorry, i couldnt get the vector of platforms to work D;  they weren't even showing up for me)
        c1.update(dt);
        c2.update(dt);
        c3.update(dt);
        c4.update(dt);

        //NOTE: this should work as an array in a loop as well. (currently checking from lowest cloud to the highest cloud, in that order)
        //The only thing changing in this code is the name of the cloud (c1, c2, c3, etc...)

         //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
        if ((int)characterForwardSprite.getPosition().y + 52 == (int)c1.getPosition().y - 1)
        {
            //if the character's center is within the width of the platform
            if (c1.getPosition().x < characterForwardSprite.getPosition().x + 21.f && characterForwardSprite.getPosition().x + 21.f < (c1.getPosition().x + c1.getSize().x))
            {
                isJumping = false; //without this the character falls through the platform after about 1 second
                characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c1.getVelocityX() * dt), c1.getPosition().y - 53.f));
            }
            else
            {
                isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
            }
        }

        //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
        if ((int)characterForwardSprite.getPosition().y + 52 == (int)c2.getPosition().y - 1)
        {
            //if the character's center is within the width of the platform
            if (c2.getPosition().x < characterForwardSprite.getPosition().x + 21.f && characterForwardSprite.getPosition().x + 21.f < (c2.getPosition().x + c2.getSize().x))
            {
                isJumping = false; //without this the character falls through the platform after about 1 second
                characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c2.getVelocityX() * dt), c2.getPosition().y - 53.f));
            }
            else
            {
                isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
            }
        }
        //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
        if ((int)characterForwardSprite.getPosition().y + 52 == (int)c3.getPosition().y - 1)
        {
            //if the character's center is within the width of the platform
            if (c3.getPosition().x < characterForwardSprite.getPosition().x + 21.f && characterForwardSprite.getPosition().x + 21.f < (c3.getPosition().x + c3.getSize().x))
            {
                isJumping = false; //without this the character falls through the platform after about 1 second
                characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c3.getVelocityX() * dt), c3.getPosition().y - 53.f));
            }
            else
            {
                isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
            }
        }

        //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
        if ((int)characterForwardSprite.getPosition().y + 52 == (int)c4.getPosition().y - 1)
        {
            //if the character's center is within the width of the platform
            if (c4.getPosition().x < characterForwardSprite.getPosition().x + 21.f && characterForwardSprite.getPosition().x + 21.f < (c4.getPosition().x + c4.getSize().x))
            {
                isJumping = false; //without this the character falls through the platform after about 1 second
                characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c4.getVelocityX() * dt), c4.getPosition().y - 53.f));
            }
            else
            {
                isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
            }
        }

        if (isDead) {
            backgroundArtSprite.setTexture(backgroundGameOver); //set end screen 
            //logic to save score and exit gameplay
            characterForwardSprite.setTexture(deadTexture);
            //characterForwardSprite.move({0,10.f}); // lower a little, nvm it messes stuff up
            characterForwardSprite.setRotation(sf::Angle(sf::degrees(90))); //rotate sprite (so player lies horizontally)
           // window.waitEvent(sf::Time::Zero); //infinite pause?

            //ignore the floating up/glitching after, thats just because the loop doesnt actually end yet (it will cut to gameover eventually)
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

        // ENSURE SPRITE CANT LEAVE CONSOLE
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
        
        drawClouds(window, c1, c2, c3, c4, smallCloudTex, mediumCloudTex, largeCloudTex); 
        //^^ if you add more clouds, you need to change this function accordingly
        // 
        //showRulesPopup(window, rulesTexture); //display rules popup on opening 

        window.draw(characterForwardSprite); //character sprite called on top of background
        window.display();
        
    }
}