#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include "GUI.h"

bool dropdownContains(const sf::Text& item, const sf::Vector2f& pos);
void handleDropdownSelection(bool& dropdownOpen, const std::vector<sf::Text>& dropdownItems, const std::vector<std::string>& options, const sf::Vector2f& mousePosition, sf::Text& dropdownText);

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
    float titleWidth = title.getLocalBounds().width;
    title.setPosition(sf::Vector2f((800 - titleWidth) / 2, 50));

    float centerX = 800 / 2.0f;
    float labelY = 90;
    float dropdownY = 105;

    // Labels for dropdowns
    sf::Text weatherLabel("Weather Delay", font, 10);
    weatherLabel.setFillColor(sf::Color::Black);
    weatherLabel.setPosition(centerX - 275 - weatherLabel.getLocalBounds().width, labelY);

    sf::Text monthLabel("Month", font, 10);
    monthLabel.setFillColor(sf::Color::Black);
    monthLabel.setPosition(centerX - monthLabel.getLocalBounds().width / 2 - 140, labelY);

    sf::Text airlineLabel("Airline", font, 10);
    airlineLabel.setFillColor(sf::Color::Black);
    airlineLabel.setPosition(centerX + 90 - airlineLabel.getLocalBounds().width, labelY);

    sf::Text sortLabel("Sort By", font, 10);
    sortLabel.setFillColor(sf::Color::Black);
    sortLabel.setPosition(centerX + 290 - sortLabel.getLocalBounds().width, labelY);

    // Dropdown options
    std::vector<std::string> weatherOptions = {"Sunny", "Rainy", "Snowy", "Cloudy"};
    std::vector<std::string> monthOptions = {"January", "February", "March", "April"};
    std::vector<std::string> airlineOptions = {"Airline A", "Airline B", "Airline C", "Airline D"};
    std::vector<std::string> sortOptions = {"None", "Alphabetical", "Date"};

    float dropdownWidth = 120;

    // Rectangles for dropdowns
    sf::RectangleShape weatherRect = test.Rect(centerX - 300 - dropdownWidth / 2, dropdownY, 30, 120);
    sf::RectangleShape monthRect = test.Rect(centerX - dropdownWidth / 2 - 100, dropdownY, 30, 120);
    sf::RectangleShape airlineRect = test.Rect(centerX + 100 - dropdownWidth / 2, dropdownY, 30, 120);
    sf::RectangleShape sortRect = test.Rect(centerX + 300 - dropdownWidth / 2, dropdownY, 30, 120);

    // Text for dropdown selections
    sf::Text weatherDropdownText = test.text(centerX - 200 - dropdownWidth / 2 - 75, dropdownY + 15, 10, "None", font);
    weatherDropdownText.setFillColor(sf::Color::White);
    sf::Text monthDropdownText = test.text(centerX - dropdownWidth / 2 - 75, dropdownY + 15, 10, "None", font);
    monthDropdownText.setFillColor(sf::Color::White);
    sf::Text airlineDropdownText = test.text(centerX + 90 - dropdownWidth / 2 + 30, dropdownY + 15, 10, "None", font);
    airlineDropdownText.setFillColor(sf::Color::White);
    sf::Text sortDropdownText = test.text(centerX + 250 - dropdownWidth / 2 + 75, dropdownY + 15, 10, "None", font);
    sortDropdownText.setFillColor(sf::Color::White);

    // Create dropdown items
    std::vector<sf::Text> weatherDropdownItems = test.dropdown(weatherOptions, weatherRect, font);
    std::vector<sf::Text> monthDropdownItems = test.dropdown(monthOptions, monthRect, font);
    std::vector<sf::Text> airlineDropdownItems = test.dropdown(airlineOptions, airlineRect, font);
    std::vector<sf::Text> sortDropdownItems = test.dropdown(sortOptions, sortRect, font);

    bool weatherDropdownOpen = false;
    bool monthDropdownOpen = false;
    bool airlineDropdownOpen = false;
    bool sortDropdownOpen = false;

    // Position filter button at the bottom center of the screen
    float filterButtonX = (800 - 100) / 2.0f; // Center horizontally
    float filterButtonY = 550; // Position at the bottom

    sf::RectangleShape filterButton(sf::Vector2f(100, 30));
    filterButton.setFillColor(sf::Color::Red);
    filterButton.setPosition(filterButtonX, filterButtonY);

    sf::Text filterButtonText("Apply Filter", font, 14);
    filterButtonText.setFillColor(sf::Color::White);
    filterButtonText.setPosition(filterButtonX + (filterButton.getSize().x - filterButtonText.getLocalBounds().width) / 2, filterButtonY + (filterButton.getSize().y - filterButtonText.getLocalBounds().height) / 2);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonReleased) {
                sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);

                // Toggle dropdowns and manage dropdown selection
                if (weatherRect.getGlobalBounds().contains(mousePosition)) {
                    weatherDropdownOpen = !weatherDropdownOpen;
                    monthDropdownOpen = false;
                    airlineDropdownOpen = false;
                    sortDropdownOpen = false;
                } else if (monthRect.getGlobalBounds().contains(mousePosition)) {
                    monthDropdownOpen = !monthDropdownOpen;
                    weatherDropdownOpen = false;
                    airlineDropdownOpen = false;
                    sortDropdownOpen = false;
                } else if (airlineRect.getGlobalBounds().contains(mousePosition)) {
                    airlineDropdownOpen = !airlineDropdownOpen;
                    weatherDropdownOpen = false;
                    monthDropdownOpen = false;
                    sortDropdownOpen = false;
                } else if (sortRect.getGlobalBounds().contains(mousePosition)) {
                    sortDropdownOpen = !sortDropdownOpen;
                    weatherDropdownOpen = false;
                    monthDropdownOpen = false;
                    airlineDropdownOpen = false;
                }

                // Select dropdown items
                handleDropdownSelection(weatherDropdownOpen, weatherDropdownItems, weatherOptions, mousePosition, weatherDropdownText);
                handleDropdownSelection(monthDropdownOpen, monthDropdownItems, monthOptions, mousePosition, monthDropdownText);
                handleDropdownSelection(airlineDropdownOpen, airlineDropdownItems, airlineOptions, mousePosition, airlineDropdownText);
                handleDropdownSelection(sortDropdownOpen, sortDropdownItems, sortOptions, mousePosition, sortDropdownText);

                // Output selected options when dropdown items are clicked
                if (!weatherDropdownOpen && !monthDropdownOpen && !airlineDropdownOpen && !sortDropdownOpen) {
                    std::cout << "Selected Weather: " << weatherDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Selected Month: " << monthDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Selected Airline: " << airlineDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Selected Sort: " << sortDropdownText.getString().toAnsiString() << std::endl;
                }

                // Filter button click action
                if (filterButton.getGlobalBounds().contains(mousePosition) &&
                    !weatherDropdownOpen && !monthDropdownOpen && !airlineDropdownOpen && !sortDropdownOpen) {
                    std::cout << "Filter Button Clicked!" << std::endl;
                    std::cout << "Applying Filter with: " << std::endl;
                    std::cout << "Weather: " << weatherDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Month: " << monthDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Airline: " << airlineDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Sort: " << sortDropdownText.getString().toAnsiString() << std::endl;
                }
            }
        }

        window.clear(sf::Color::White);
        window.draw(title);
        window.draw(weatherLabel);
        window.draw(monthLabel);
        window.draw(airlineLabel);
        window.draw(sortLabel);

        window.draw(weatherRect);
        window.draw(weatherDropdownText);
        window.draw(monthRect);
        window.draw(monthDropdownText);
        window.draw(airlineRect);
        window.draw(airlineDropdownText);
        window.draw(sortRect);
        window.draw(sortDropdownText);

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
        if (sortDropdownOpen) {
            for (const auto& item : sortDropdownItems) {
                window.draw(item);
            }
        }

        window.draw(filterButton);
        window.draw(filterButtonText);

        window.display();
    }

    return 0;
}

bool dropdownContains(const sf::Text& item, const sf::Vector2f& pos) {
    return item.getGlobalBounds().contains(pos);
}

void handleDropdownSelection(bool& dropdownOpen, const std::vector<sf::Text>& dropdownItems, const std::vector<std::string>& options, const sf::Vector2f& mousePosition, sf::Text& dropdownText) {
    if (!dropdownOpen) return;

    for (size_t i = 0; i < dropdownItems.size(); i++) {
        if (dropdownItems[i].getGlobalBounds().contains(mousePosition)) {
            dropdownText.setString(options[i]);
            dropdownOpen = false;
            break;
        }
    }
}
