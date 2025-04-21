#pragma once
#include "header.h"
#include <SFML/Window/Event.hpp> 


void showRulesPopup(sf::RenderWindow& window, const sf::Texture& rulesTexture) 
{
    sf::Sprite rulesPopup(rulesTexture);

    window.draw(rulesPopup);  // Draw the rules popup
    window.display();  // Show the drawn content

    bool waitingForEnter = true;
    while (waitingForEnter) {
       
 

        // Check if Enter key is pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter)) {
            waitingForEnter = false;  // Exit loop when Enter is pressed
            window.clear();
            return;
        }
    }
}