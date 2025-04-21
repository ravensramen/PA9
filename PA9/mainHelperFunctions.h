#pragma once
#include "header.h"
#include <SFML/Window/Event.hpp> 

//
//void showRulesPopup(sf::RenderWindow& window, const sf::Texture& rulesTexture) 
//{
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

void showRulesPopup(sf::RenderWindow& window, const sf::Texture& rulesTexture) 
{
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