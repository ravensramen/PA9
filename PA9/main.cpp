#include "classesInclude.h";
//#include "testCases.h";
int main()
{
    ////TEST CASES: uncomment to test (including testCases.h)
    //TEST_PLANET_RANDOMIZATION();
    //TEST_STAR_HAZARD_DIRECTIONALITY();
    //TEST_CLOUD_MOVEMENT();
    //TEST_METEOR_MOVEMENT();
    //TEST_CLOUD_RESET_POSITION();
    ////

    int keepPlaying = 1;
    while (keepPlaying)
    {
        std::srand((int)std::time(0)); //for random

        sf::RenderWindow window(sf::VideoMode({ 700, 900 }), "Space Hopper");

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
        bool rulesShown = false; //bool so rules are only shown once (rather than every frame of gameplay loop)

        //set sprite player image
        sf::Texture forwardTexture, leftTexture, rightTexture, deadTexture, deadJetTexture,
            jetFrontTexture, jetFrontOnTexture, jetRightTexture, jetLeftTexture, jetRightOnTexture, jetLeftOnTexture;

        if (!forwardTexture.loadFromFile("forwardSprite.png") ||
            !leftTexture.loadFromFile("leftSprite.png") ||
            !rightTexture.loadFromFile("rightSprite.png") ||
            !deadTexture.loadFromFile("deadSprite.png") ||
            !deadJetTexture.loadFromFile("dead_jetpack.png") ||
            !jetFrontTexture.loadFromFile("front_jetpack_off.png") ||
            !jetFrontOnTexture.loadFromFile("front_jetpack_on.png") ||
            !jetRightTexture.loadFromFile("right_jetpack_off.png") ||
            !jetLeftTexture.loadFromFile("left_jetpack_off.png") ||
            !jetRightOnTexture.loadFromFile("right_jetpack_on.png") ||
            !jetLeftOnTexture.loadFromFile("left_jetpack_on.png")) {
            return -1; // one or more files didn't load
        }

        //set vector position for start
        sf::Vector2f initialPosition;
        initialPosition.x = 320; //access + assign vector location members
        initialPosition.y = 820;

        sf::Sprite characterForwardSprite(forwardTexture);
        characterForwardSprite.setPosition(initialPosition);


        //code for key press movement
        float movementSpeed = .3f; //had to speed up after adding clouds
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
        deathSound.setVolume(40.f);

        //falling death conditions
        float maxJumpHeight = 820.f; // initial ground height
        float deathFallThreshold = 200.f; // distance that causes death 
        bool isDead = false;

        //win
        bool isWon = false;

        //checkpoint for cloud level
        float checkpointY = 375.f; // example value: lowest allowed position
        bool checkpointReached = false;

        //the goal!
        goal g1;

        //the jetpack!
        jetpack j1;


        //hazards (you die when you touch them)
        // 
        //meteor (x axis input only) (from 0 to 650)
        int randomValue = std::rand() % 650;
        int randomValue2 = std::rand() % 70 - 300;
        meteorHazard m1(sf::Vector2f(randomValue, randomValue2));
        randomValue = std::rand() % 650;
        randomValue2 = std::rand() % 70 - 300;
        meteorHazard m2(sf::Vector2f(randomValue, randomValue2));
        randomValue = std::rand() % 650;
        randomValue2 = std::rand() % 70 - 300;
        meteorHazard m3(sf::Vector2f(randomValue, randomValue2));
        //asteroid (horizontal movement, needs start point)
        //y between 0 and 300, x is either -70 or 700
        randomValue2 = std::rand() % 300;
        asteroidHazard a1(sf::Vector2f(-70.f, (float)randomValue2));
        randomValue2 = std::rand() % 300;
        asteroidHazard a2(sf::Vector2f(700.f, (float)randomValue2));
        //shooting star (needs start and diagonal direction)
        //x between 0 and 700, y is always 0, randomize right and left
        randomValue = std::rand() % 700;
        if (randomValue > 350)
        {
            randomValue2 = LEFT;
        }
        else
        {
            randomValue2 = RIGHT;
        }
        starHazard s1(sf::Vector2f((float)randomValue, 0.f), randomValue2);
        randomValue = std::rand() % 700 + 1;
        if (randomValue > 350)
        {
            randomValue2 = LEFT;
        }
        else
        {
            randomValue2 = RIGHT;
        }
        starHazard s2(sf::Vector2f((float)randomValue, 0.f), randomValue2);

        //cloud platforms (start, end, speed, movement type)
        CloudSmall c1(sf::Vector2f(-94.f, 760.f), sf::Vector2f(700.f, 760.f), SLOW, HORIZONTAL);
        CloudMedium c2(sf::Vector2f(735.f, 670.f), sf::Vector2f(-105.f, 670.f), MEDIUM, HORIZONTAL);
        CloudLarge c3(sf::Vector2f(-226.f, 580.f), sf::Vector2f(770.f, 580.f), FAST, HORIZONTAL);
        CloudSmall c4(sf::Vector2f(-94.f, 530.f), sf::Vector2f(700.f, 530.f), EXFAST, HORIZONTAL);
        CloudMedium c5(sf::Vector2f(735.f, 455.f), sf::Vector2f(-105.f, 455.f), SLOW, HORIZONTAL);


        while (window.isOpen())
        {
            float dt = clock.restart().asSeconds(); //for cloud logic


            while (const std::optional event = window.pollEvent()) //this while loop handles closing window (i think...)
            {
                if (event->is<sf::Event::Closed>())
                    window.close();
            }


            if (!j1.isPickedUp()) //jetpack isnt picked up yet
            {
                //movement input based on arrow key press (might modify to wasd?)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
                    characterForwardSprite.move(moveLeft);
                    characterForwardSprite.setTexture(leftTexture, true);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                    characterForwardSprite.move(moveRight);
                    characterForwardSprite.setTexture(rightTexture, true);
                }
                //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up)) { //no floating allowed...not until jetpack equipped
                //    characterForwardSprite.move(moveUp);
                //}
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
                    characterForwardSprite.move(moveDown);
                }
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                    characterForwardSprite.setTexture(forwardTexture, true);
                }
            }
            else //jetpack is picked up
            {
                //movement input based on arrow key press (might modify to wasd?)
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left)) {
                    characterForwardSprite.move(moveLeft);
                    if (characterForwardSprite.getPosition().y != (int)375)
                    {
                        characterForwardSprite.setTexture(jetLeftOnTexture, true);
                    }
                    characterForwardSprite.setTexture(jetLeftTexture, true);

                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                    characterForwardSprite.move(moveRight);
                    if (characterForwardSprite.getPosition().y != (int)375)
                    {
                        characterForwardSprite.setTexture(jetRightOnTexture, true);
                    }
                    characterForwardSprite.setTexture(jetRightTexture, true);
                }
                if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Up))&&(j1.isPickedUp())) {
                    characterForwardSprite.move(moveUp);
                    characterForwardSprite.setTexture(jetFrontOnTexture, true);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Down)) {
                    characterForwardSprite.move(moveDown);
                    if (characterForwardSprite.getPosition().y != (int)375)
                    {
                        characterForwardSprite.setTexture(jetFrontOnTexture, true);
                    }
                    characterForwardSprite.setTexture(jetFrontTexture, true);
                }
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Right)) {
                    if (characterForwardSprite.getPosition().y != (int)375)
                    {
                        characterForwardSprite.setTexture(jetFrontOnTexture, true);
                    }
                    else
                    {
                        characterForwardSprite.setTexture(jetFrontTexture, true);
                    }
                }
            }

            if (!checkpointReached)
            {
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
            }
            else //checkpoint reached, no more jumping allowed.
            {
                velocity.y = 0;      // stop falling
                isJumping = false;   // treat as landed
            }

            //hazard updates
            m1.update(dt);
            m2.update(dt);
            m3.update(dt);
            a1.update(dt);
            a2.update(dt);
            s1.update(dt);
            s2.update(dt);

            //cloud updates
            c1.update(dt);
            c2.update(dt);
            c3.update(dt);
            c4.update(dt);
            c5.update(dt);

            //-----------------------------character platform interaction---------------------------

            //NOTE: this should work as an array in a loop as well. (currently checking from lowest cloud to the highest cloud, in that order)
            //The only thing changing in this code is the name of the cloud (c1, c2, c3, etc...)

             //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
            if ((int)characterForwardSprite.getPosition().y + (characterForwardSprite.getTextureRect().size.y) == (int)c1.getPosition().y - 1)
            {
                //if the character's center is within the width of the platform
                if (c1.getPosition().x < characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) &&
                    characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) < (c1.getPosition().x + c1.getSize().x))
                {
                    isJumping = false; //without this the character falls through the platform after about 1 second
                    characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c1.getVelocityX() * dt),
                        c1.getPosition().y - ((characterForwardSprite.getTextureRect().size.y) + 1)));
                }
                else
                {
                    isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
                }
            }

            //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
            if ((int)characterForwardSprite.getPosition().y + (characterForwardSprite.getTextureRect().size.y) == (int)c2.getPosition().y - 1)
            {
                //if the character's center is within the width of the platform
                if (c2.getPosition().x < characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) &&
                    characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) < (c2.getPosition().x + c2.getSize().x))
                {
                    isJumping = false; //without this the character falls through the platform after about 1 second
                    characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c2.getVelocityX() * dt),
                        c2.getPosition().y - ((characterForwardSprite.getTextureRect().size.y) + 1)));
                }
                else
                {
                    isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
                }
            }
            //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
            if ((int)characterForwardSprite.getPosition().y + (characterForwardSprite.getTextureRect().size.y) == (int)c3.getPosition().y - 1)
            {
                //if the character's center is within the width of the platform
                if (c3.getPosition().x < characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) &&
                    characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) < (c3.getPosition().x + c3.getSize().x))
                {
                    isJumping = false; //without this the character falls through the platform after about 1 second
                    characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c3.getVelocityX() * dt),
                        c3.getPosition().y - ((characterForwardSprite.getTextureRect().size.y) + 1)));
                }
                else
                {
                    isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
                }
            }

            //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
            if ((int)characterForwardSprite.getPosition().y + (characterForwardSprite.getTextureRect().size.y) == (int)c4.getPosition().y - 1)
            {
                //if the character's center is within the width of the platform
                if (c4.getPosition().x < characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) &&
                    characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) < (c4.getPosition().x + c4.getSize().x))
                {
                    isJumping = false; //without this the character falls through the platform after about 1 second
                    characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c4.getVelocityX() * dt),
                        c4.getPosition().y - ((characterForwardSprite.getTextureRect().size.y) + 1)));
                }
                else
                {
                    isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
                }
            }

            //if the character's base is above the platform top (must be cast as int to check correctly [took me forever for me to realize (q_q) ])
            if ((int)characterForwardSprite.getPosition().y + (characterForwardSprite.getTextureRect().size.y) == (int)c5.getPosition().y - 1)
            {
                //if the character's center is within the width of the platform
                if (c5.getPosition().x < characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) &&
                    characterForwardSprite.getPosition().x + (characterForwardSprite.getTextureRect().size.x / 2) < (c5.getPosition().x + c5.getSize().x))
                {
                    isJumping = false; //without this the character falls through the platform after about 1 second
                    characterForwardSprite.setPosition(sf::Vector2f((characterForwardSprite.getPosition().x) + (c5.getVelocityX() * dt),
                        c5.getPosition().y - ((characterForwardSprite.getTextureRect().size.y) + 1)));
                }
                else
                {
                    isJumping = true; //without this the character just hangs out at the level of the platform even when they should fall
                }
            }

            //touch jetpack and movement style should change.
            if (characterForwardSprite.getGlobalBounds().findIntersection(j1.getGlobalBounds()))
            {
                j1.pickUp();
            }

            //touch a hazard and you die
            //once again somethig that can probably be put in some kind of loop to check each one
            if (characterForwardSprite.getGlobalBounds().findIntersection(m1.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }
            if (characterForwardSprite.getGlobalBounds().findIntersection(m2.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }
            if (characterForwardSprite.getGlobalBounds().findIntersection(m3.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }
            if (characterForwardSprite.getGlobalBounds().findIntersection(a1.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }
            if (characterForwardSprite.getGlobalBounds().findIntersection(a2.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }
            if (characterForwardSprite.getGlobalBounds().findIntersection(s1.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }
            if (characterForwardSprite.getGlobalBounds().findIntersection(s2.getCollisionShape().getGlobalBounds()))
            {
                isDead = true;
            }

            //IF THE PLAYER REACHES THE GOAL
            if (characterForwardSprite.getGlobalBounds().findIntersection(g1.getCollisionShape().getGlobalBounds()))
            {
                showGameWon(window, keepPlaying);
            }


            if (isDead) {
                window.clear(); //clear previous elements (gameplay before death)

                backgroundArtSprite.setTexture(backgroundGameOver); //change background texture
                if (!j1.isPickedUp())
                {
                    characterForwardSprite.setTexture(deadTexture, true);
                    characterForwardSprite.move(sf::Vector2f(0,+10.f)); //lower dead texture a little, otherwise it may float
                }
                else if (j1.isPickedUp())
                {
                    characterForwardSprite.setTexture(deadJetTexture, true);
                }

                //draw end screen elements
                window.draw(backgroundArtSprite);
                window.draw(characterForwardSprite);
                showGameOver(window, keepPlaying);
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
            if (rulesShown == false) {
                showRulesPopup(window, rulesTexture);
                rulesShown = true;
            }



            /////////DRAW CLOUDS AND CORRESPONDING SPRITE IMAGES, 

            //draw goal
            g1.draw(window);

            //draw cloud platforms
            c1.draw(window);
            c2.draw(window);
            c3.draw(window);
            c4.draw(window);
            c5.draw(window);

            //draw hazard
            m1.draw(window);
            m2.draw(window);
            m3.draw(window);
            a1.draw(window);
            a2.draw(window);
            s1.draw(window);
            s2.draw(window);

            //draw jetpack
            j1.draw(window);

            window.draw(characterForwardSprite); //character sprite called on top of background
            window.display();

        }
    }
}