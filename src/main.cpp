#include <SFML\Graphics.hpp>
#include <iostream>
#include "GUI.h"
int main() {
    //on press down darken button that mouse is over
    // make dropdown sprite or image
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Dropdown Menu");
    gui test;
    // Dropdown menu options
    std::vector<std::string> options = {"Option 1", "Option 2", "Option 3"};
    //dropdown menu rectangle
    sf::RectangleShape dropdownRect = test.Rect(50, 50, 30, 120);

    //Font can be moved into gui class if needed
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }
    //creates dropdown text, position is based on center not corner
    sf::Text dropdownText = test.text(110,65, 10,"Select an option", font);
    // Dropdown menu items
    std::vector<sf::Text> dropdownItems = test.dropdown(options, dropdownRect, font);

    // Dropdown menu state
    bool dropdownOpen = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                if (dropdownRect.getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                    dropdownOpen = !dropdownOpen;
                } else if (dropdownOpen) {
                    for (size_t i = 0; i < dropdownItems.size(); ++i) {
                        if (dropdownItems[i].getGlobalBounds().contains(sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
                            std::cout << "Selected: " << options[i] << std::endl;
                            //sets text
                            dropdownText.setString(dropdownItems[i].getString());
                            dropdownOpen = false;
                            break;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        // Draw dropdown menu rectangle and text
        window.draw(dropdownRect);
        window.draw(dropdownText);

        // Draw dropdown menu items if open
        if (dropdownOpen) {
            for (const auto& item : dropdownItems) {
                window.draw(item);
            }
        }

        window.display();
    }

    return 0;
}
