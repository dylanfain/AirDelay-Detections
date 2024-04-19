#include <SFML\Graphics.hpp>
#include <iostream>
#include <chrono>
#include "FlightData.h"
#include "sort.h"
#include "GUI.h"

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
//    flightData = filterByWeatherDelay(flightData, false);
//    flightData = filterByMonth(flightData, 4);
//    //Keep a copy of the original data
//    auto OriginalData = flightData;
//    //timer start
//    auto start = std::chrono::high_resolution_clock::now();
//    //send the flightdata through heap sort
//    heapSort(flightData);
//    //end timer and calculate time to execute
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
//
//    //display execution time
//    std::cout << "Heap sort execution time: " << duration.count() << " milliseconds" << std::endl;
//
//    // Start timing
//    auto start2 = std::chrono::high_resolution_clock::now();
//    flightData = OriginalData;
//    // Sort flight data by flight delay using merge sort
//    mergeSort(flightData, 0, flightData.size() - 1);
//
//    // End timing
//    auto end2 = std::chrono::high_resolution_clock::now();
//
//    // Calculate duration
//    auto duration2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2);
//
//    // Display sorted flight data
//    cout << endl << endl;
//    //display all flights in order of flight delay
//    for (const auto& flight : flightData) {
//        std::cout << "Arrival Delay: " << flight.arrivalDelay << ", ";
//        std::cout << "Date: " << flight.date << ", ";
//        cout << "Month: " << flight.month << ", ";
//        std::cout << "Airline: " << flight.airline << ", ";
//        std::cout << "Weather Delay: " << flight.weatherDelay << std::endl;
//    }
//    // Output execution time
//    std::cout << "Merge sort execution time: " << duration2.count() << " milliseconds" << std::endl;



    //GUI Start here



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
