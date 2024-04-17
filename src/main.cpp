#include <SFML/Graphics.hpp>
#include <iostream>
#include <chrono>
#include "FlightData.h"
#include "sort.h"

std::vector<FlightData> filterByWeatherDelay(const std::vector<FlightData>& flightData, bool hasWeatherDelay) {
    std::vector<FlightData> filteredData;
    for (const auto& flight : flightData) {
        if (flight.weatherDelay == hasWeatherDelay) {
            filteredData.push_back(flight);
        }
    }
    return filteredData;
}

std::vector<FlightData> filterByMonth(const std::vector<FlightData>& flightData, int targetMonth) {
    std::vector<FlightData> filteredData;
    for (const auto& flight : flightData) {
        if (flight.month == targetMonth) {
            filteredData.push_back(flight);
        }
    }
    return filteredData;
}

std::vector<FlightData> filterByAirline(const std::vector<FlightData>& flightData, const std::string& targetAirline) {
    std::vector<FlightData> filteredData;
    for (const auto& flight : flightData) {
        if (flight.airline == targetAirline) {
            filteredData.push_back(flight);
        }
    }
    return filteredData;
}


int main() {
    //Parsing file data Flight_delay.csv
    vector<FlightData> flightData = parseCSV("files/Flight_delay.csv");
//    //example of all functions in use for final results
//    //example filters added to flightdata
//    flightData = filterByAirline(flightData, "American Airlines Inc.");
//    flightData = filterByWeatherDelay(flightData, true);
//    //timer start
//    auto start = std::chrono::high_resolution_clock::now();
//    //send the flightdata through heap sort
//    heapSort(flightData);
//    //end timer and calculate time to execute
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//    //display all flights in order of flight delay
//    for (const auto& flight : flightData) {
//        std::cout << "Arrival Delay: " << flight.arrivalDelay << ", ";
//        std::cout << "Date: " << flight.month << ", ";
//        std::cout << "Airline: " << flight.airline << ", ";
//        std::cout << "Weather Delay: " << flight.weatherDelay << std::endl;
//    }
//    //display execution time
//    std::cout << "Heap sort execution time: " << duration.count() << " milliseconds" << std::endl;




    //GUI Start here
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Dropdown Menu");

    // Dropdown menu options
    std::vector<std::string> options = {"Option 1", "Option 2", "Option 3"};

    // Dropdown menu rectangle
    sf::RectangleShape dropdownRect(sf::Vector2f(120, 30));
    dropdownRect.setFillColor(sf::Color::White);
    dropdownRect.setOutlineColor(sf::Color::Black);
    dropdownRect.setOutlineThickness(2.f);
    dropdownRect.setPosition(50, 50);

    // Dropdown menu text
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }

    sf::Text dropdownText;
    dropdownText.setFont(font);
    dropdownText.setString("Select an option");
    dropdownText.setCharacterSize(10);
    dropdownText.setFillColor(sf::Color::Black);
    dropdownText.setPosition(55, 55);

    // Dropdown menu items
    std::vector<sf::Text> dropdownItems;
    for (size_t i = 0; i < options.size(); ++i) {
        sf::Text item;
        item.setFont(font);
        item.setString(options[i]);
        item.setCharacterSize(16);
        item.setFillColor(sf::Color::Black);
        item.setPosition(55, 85 + i * 30);
        dropdownItems.push_back(item);
    }

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
