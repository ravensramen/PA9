#pragma once

#include <SFML/Window/Event.hpp> 
#include "cloudMedium.h" //these include a copy of the header
#include "cloudLarge.h"
#include "cloudSmall.h"

void drawClouds(sf::RenderWindow& window,
    CloudSmall& c1, CloudMedium& c2,
    CloudLarge& c3, CloudSmall& c4,
    const sf::Texture& smallCloudTex,
    const sf::Texture& mediumCloudTex,
    const sf::Texture& largeCloudTex)
{
    // c1 - small
    c1.draw(window);
    sf::Sprite smallCloudSprite(smallCloudTex);
    smallCloudSprite.setPosition({ c1.getPosition().x - 30, c1.getPosition().y - 25 });
    window.draw(smallCloudSprite);

    // c2 - medium -> might need to make the sprite a litttle bit bigger
    c2.draw(window);
    sf::Sprite mediumCloudSprite(mediumCloudTex);
    mediumCloudSprite.setPosition({ c2.getPosition().x - 23, c2.getPosition().y - 35 });
    window.draw(mediumCloudSprite);

    // c3 - large
    c3.draw(window);
    sf::Sprite largeCloudSprite(largeCloudTex);
    largeCloudSprite.setPosition({ c3.getPosition().x - 50, c3.getPosition().y - 55 });
    window.draw(largeCloudSprite);

    // c4 - small again
    c4.draw(window);
    sf::Sprite smallCloudSprite2(smallCloudTex);
    smallCloudSprite2.setPosition({ c4.getPosition().x - 30, c4.getPosition().y - 25 });
    window.draw(smallCloudSprite2);
}

//
//void showRulesPopup(sf::RenderWindow& window, const sf::Texture& rulesTexture) {
//    sf::Sprite rulesPopup(rulesTexture);
//    //rulesPopup.setPosition({ 100.f, 150.f }); // adjust to your needs
//
//  
//    bool waitingForEnter = true;
//    while (waitingForEnter) {
//       
//        window.draw(rulesPopup);
//        window.display();
//
//        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter)) {
//            waitingForEnter = false;
//            window.clear();
//        }
//    }
//}

void showRulesPopup(sf::RenderWindow& window, const sf::Texture& rulesTexture) {
    sf::Sprite rulesPopup(rulesTexture);

    bool waitingForEnter = true;
    while (waitingForEnter) {
        window.clear();  // Clear window to prepare for drawing the new frame
        window.draw(rulesPopup);  // Draw the rules popup
        window.display();  // Show the drawn content

        // Check if Enter key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter)) {
            waitingForEnter = false;  // Exit loop when Enter is pressed
            window.clear();
            return;
        }
    }
}