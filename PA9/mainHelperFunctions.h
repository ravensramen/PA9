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


void showGameWon(sf::RenderWindow& window) {
    sf::Texture gameWonTexture("youWinScreen.png");
    sf::Sprite gameWonPopup(gameWonTexture);

    window.draw(gameWonPopup);
    window.display();

    sf::sleep(sf::seconds(100));//change! display indefintely (idk how yet... ;;)
    //might have to have a loop condition in main or something idk ;-;
}

void showGameOver(sf::RenderWindow& window) {
    sf::Texture gameoverTexture("gameoverScreen.PNG");
    sf::Sprite gameoverPopup(gameoverTexture);

    window.draw(gameoverPopup);
    window.display();

    sf::sleep(sf::seconds(100)); //change! display indefintely (idk how yet... ;;)
    //might have to have a loop condition in main or something idk ;-;
}