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

    // Titles and Labels
    sf::Text title("AirDelay Detections", font, 24);
    title.setFillColor(sf::Color::Black);

    // Center the title at the top of the window
    float titleWidth = title.getLocalBounds().width;
    title.setPosition(sf::Vector2f((800 - titleWidth) / 2, 50));

    // Calculate horizontal positions for labels and dropdowns
    float centerX = 800 / 2.0f;
    float labelY = 90;
    float dropdownY = 105;

    sf::Text weatherLabel("Weather Delay", font, 10);
    weatherLabel.setFillColor(sf::Color::Black);
    float weatherLabelWidth = weatherLabel.getLocalBounds().width;
    weatherLabel.setPosition(centerX - 150 - weatherLabelWidth, labelY);

    sf::Text monthLabel("Month", font, 10);
    monthLabel.setFillColor(sf::Color::Black);
    float monthLabelWidth = monthLabel.getLocalBounds().width;
    monthLabel.setPosition(centerX - monthLabelWidth / 2, labelY);

    sf::Text airlineLabel("Airline", font, 10);
    airlineLabel.setFillColor(sf::Color::Black);
    float airlineLabelWidth = airlineLabel.getLocalBounds().width;
    airlineLabel.setPosition(centerX + 150, labelY);

    // Dropdown options
    std::vector<std::string> weatherOptions = {"Sunny", "Rainy", "Snowy", "Cloudy"};
    std::vector<std::string> monthOptions = {"January", "February", "March", "April"};
    std::vector<std::string> airlineOptions = {"Airline A", "Airline B", "Airline C", "Airline D"};

    // Dropdown rectangles and texts
    float dropdownWidth = 120; // Adjust as needed based on dropdown content
    sf::RectangleShape weatherRect = test.Rect(centerX - 200 - dropdownWidth / 2, dropdownY, 30, 120);
    sf::RectangleShape monthRect = test.Rect(centerX - dropdownWidth / 2, dropdownY, 30, 120);
    sf::RectangleShape airlineRect = test.Rect(centerX + 200 - dropdownWidth / 2, dropdownY, 30, 120);

    sf::Text weatherDropdownText = test.text(centerX - 200 - dropdownWidth / 2 + 30, dropdownY + 15, 10, "None", font);
    weatherDropdownText.setFillColor(sf::Color::White);

    sf::Text monthDropdownText = test.text(centerX - dropdownWidth / 2 + 30, dropdownY + 15, 10, "None", font);
    monthDropdownText.setFillColor(sf::Color::White);

    sf::Text airlineDropdownText = test.text(centerX + 200 - dropdownWidth / 2 + 30, dropdownY + 15, 10, "None", font);
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

                // Toggle dropdowns
                if (weatherRect.getGlobalBounds().contains(mousePosition)) {
                    weatherDropdownOpen = !weatherDropdownOpen;
                } else if (monthRect.getGlobalBounds().contains(mousePosition)) {
                    monthDropdownOpen = !monthDropdownOpen;
                } else if (airlineRect.getGlobalBounds().contains(mousePosition)) {
                    airlineDropdownOpen = !airlineDropdownOpen;
                }

                // Handle dropdown item selection
                for (size_t i = 0; i < weatherDropdownItems.size(); ++i) {
                    if (dropdownContains(weatherDropdownItems[i], mousePosition)) {
                        weatherDropdownText.setString(weatherOptions[i]);
                        weatherDropdownOpen = false;
                        std::cout << "Selected Weather: " << weatherOptions[i] << std::endl; // Output selected weather
                        break;
                    }
                }
                for (size_t i = 0; i < monthDropdownItems.size(); ++i) {
                    if (dropdownContains(monthDropdownItems[i], mousePosition)) {
                        monthDropdownText.setString(monthOptions[i]);
                        monthDropdownOpen = false;
                        std::cout << "Selected Month: " << monthOptions[i] << std::endl; // Output selected month
                        break;
                    }
                }
                for (size_t i = 0; i < airlineDropdownItems.size(); ++i) {
                    if (dropdownContains(airlineDropdownItems[i], mousePosition)) {
                        airlineDropdownText.setString(airlineOptions[i]);
                        airlineDropdownOpen = false;
                        std::cout << "Selected Airline: " << airlineOptions[i] << std::endl; // Output selected airline
                        break;
                    }
                }
            }
        }

        // Draw everything
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

        // Draw dropdown items based on state
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
