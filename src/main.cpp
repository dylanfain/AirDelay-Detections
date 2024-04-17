#include <SFML/Graphics.hpp>
#include <iostream>
#include "GUI.h"

bool dropdownContains(const sf::Text& item, const sf::Vector2f& pos);

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Dropdown Menu");
    gui test;
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    // Titles
    sf::Text title("AirDelay Detections", font, 24);
    title.setFillColor(sf::Color::Black);
    title.setPosition(sf::Vector2f(300, 50));

    sf::Text weatherLabel("Weather Delay", font, 10);
    weatherLabel.setFillColor(sf::Color::Black);
    weatherLabel.setPosition(55, 90);

    sf::Text monthLabel("Month", font, 10);
    monthLabel.setFillColor(sf::Color::Black);
    monthLabel.setPosition(55, 180);

    sf::Text airlineLabel("Airline", font, 10);
    airlineLabel.setFillColor(sf::Color::Black);
    airlineLabel.setPosition(55, 270);

    // Dropdown options
    std::vector<std::string> weatherOptions = {"Sunny", "Rainy", "Snowy", "Cloudy"};
    std::vector<std::string> monthOptions = {"January", "February", "March", "April"};
    std::vector<std::string> airlineOptions = {"Airline A", "Airline B", "Airline C", "Airline D"};

    // Dropdown rectangles
    sf::RectangleShape weatherRect = test.Rect(50, 105, 30, 120);
    sf::RectangleShape monthRect = test.Rect(50, 195, 30, 120);
    sf::RectangleShape airlineRect = test.Rect(50, 285, 30, 120);

    // Dropdown texts
    sf::Text weatherDropdownText = test.text(80, 120, 10, "None", font);
    weatherDropdownText.setFillColor(sf::Color::White);
    sf::Text monthDropdownText = test.text(80, 210, 10, "None", font);
    monthDropdownText.setFillColor(sf::Color::White);
    sf::Text airlineDropdownText = test.text(80, 300, 10, "None", font);
    airlineDropdownText.setFillColor(sf::Color::White);

    // Dropdown menu items
    std::vector<sf::Text> weatherDropdownItems = test.dropdown(weatherOptions, weatherRect, font);
    std::vector<sf::Text> monthDropdownItems = test.dropdown(monthOptions, monthRect, font);
    std::vector<sf::Text> airlineDropdownItems = test.dropdown(airlineOptions, airlineRect, font);

    // Dropdown menu state
    bool weatherDropdownOpen = false;
    bool monthDropdownOpen = false;
    bool airlineDropdownOpen = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);

                if (weatherRect.getGlobalBounds().contains(mousePosition)) {
                    weatherDropdownOpen = !weatherDropdownOpen;
                } else {
                    for (size_t i = 0; i < weatherDropdownItems.size(); ++i) {
                        if (dropdownContains(weatherDropdownItems[i], mousePosition)) {
                            weatherDropdownText.setString(weatherOptions[i]);
                            weatherDropdownOpen = false;
                            break;
                        }
                    }
                }

                if (monthRect.getGlobalBounds().contains(mousePosition)) {
                    monthDropdownOpen = !monthDropdownOpen;
                } else {
                    for (size_t i = 0; i < monthDropdownItems.size(); ++i) {
                        if (dropdownContains(monthDropdownItems[i], mousePosition)) {
                            monthDropdownText.setString(monthOptions[i]);
                            monthDropdownOpen = false;
                            break;
                        }
                    }
                }

                if (airlineRect.getGlobalBounds().contains(mousePosition)) {
                    airlineDropdownOpen = !airlineDropdownOpen;
                } else {
                    for (size_t i = 0; i < airlineDropdownItems.size(); ++i) {
                        if (dropdownContains(airlineDropdownItems[i], mousePosition)) {
                            airlineDropdownText.setString(airlineOptions[i]);
                            airlineDropdownOpen = false;
                            break;
                        }
                    }
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(title);
        window.draw(weatherLabel);
        window.draw(monthLabel);
        window.draw(airlineLabel);
        window.draw(weatherRect);
        window.draw(weatherDropdownText);
        window.draw(monthRect);
        window.draw(monthDropdownText);
        window.draw(airlineRect);
        window.draw(airlineDropdownText);

        if (weatherDropdownOpen) {
            for (const auto& item : weatherDropdownItems) {
                window.draw(item);
            }
        }

        if (monthDropdownOpen) {
            for (const auto& item : monthDropdownItems) {
                window.draw(item);
            }
        }

        if (airlineDropdownOpen) {
            for (const auto& item : airlineDropdownItems) {
                window.draw(item);
            }
        }

        window.display();
    }

    return 0;
}

bool dropdownContains(const sf::Text& item, const sf::Vector2f& pos) {
    return item.getGlobalBounds().contains(pos);
}
