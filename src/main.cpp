#include <SFML\Graphics.hpp>
#include <iostream>
#include <chrono>
#include "FlightData.h"
#include "sort.h"
#include "GUI.h"

bool dropdownContains(const sf::Text& item, const sf::Vector2f& pos);
void handleDropdownSelection(bool& dropdownOpen, const std::vector<sf::Text>& dropdownItems, const std::vector<std::string>& options, const sf::Vector2f& mousePosition, sf::Text& dropdownText);

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
    auto originalData = flightData;

/*    //example of all functions in use for final results
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
    std::cout << "Merge sort execution time: " << duration2.count() << " milliseconds" << std::endl;*/



    //GUI Start here



    //on press down darken button that mouse is over
    // make dropdown sprite or image

    sf::RenderWindow window(sf::VideoMode(800, 600), "AirDelay Detections");
    gui test;
    // Dropdown menu options
    //std::vector<std::string> options = {"Option 1", "Option 2", "Option 3"};
    //dropdown menu rectangle
    //sf::RectangleShape dropdownRect = test.Rect(50, 50, 30, 120);

    //Font can be moved into gui class if needed
    sf::Font font;
    if (!font.loadFromFile("files/font.ttf")) {
        std::cerr << "Failed to load font" << std::endl;
        return 1;
    }
    //creates dropdown text, position is based on center not corner
    //sf::Text dropdownText = test.text(110,65, 10,"Select an option", font);
    // Dropdown menu items
    //std::vector<sf::Text> dropdownItems = test.dropdown(options, dropdownRect, font);

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
    std::vector<std::string> weatherOptions = {"None","True", "False"};
    std::vector<std::string> monthOptions = {"None","January", "February", "March", "April","May","June","July"
                                            ,"August","September","October","November","December"};
    std::vector<std::string> airlineOptions = {"None","Southwest Airlines Co.", "American Airlines Inc.",
                                               "American Eagle Airlines Inc.","United Air Lines Inc.","Skywest Airlines Inc."};
    std::vector<std::string> sortOptions = {"Heap", "Merge"};

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
    sf::Text sortDropdownText = test.text(centerX + 250 - dropdownWidth / 2 + 75, dropdownY + 15, 10, "Heap", font);
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
                    flightData = originalData;
                    std::cout << "Filter Button Clicked!" << std::endl;
                    std::cout << "Applying Filter with: " << std::endl;
                    std::cout << "Weather: " << weatherDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Month: " << monthDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Airline: " << airlineDropdownText.getString().toAnsiString() << std::endl;
                    std::cout << "Sort: " << sortDropdownText.getString().toAnsiString() << std::endl;

                    //Apply filters by function
                    if(weatherDropdownText.getString().toAnsiString() != "None"){
                        if(weatherDropdownText.getString().toAnsiString() == "True")
                            flightData = filterByWeatherDelay(flightData, true);
                        else
                            flightData = filterByWeatherDelay(flightData, false);
                    }
                    if(monthDropdownText.getString().toAnsiString() != "None"){
                        if(monthDropdownText.getString().toAnsiString() == "January")
                            flightData = filterByMonth(flightData, 1);
                        else if(monthDropdownText.getString().toAnsiString() == "February")
                            flightData = filterByMonth(flightData, 2);
                        else if(monthDropdownText.getString().toAnsiString() == "March")
                            flightData = filterByMonth(flightData, 3);
                        else if(monthDropdownText.getString().toAnsiString() == "April")
                            flightData = filterByMonth(flightData, 4);
                        else if(monthDropdownText.getString().toAnsiString() == "May")
                            flightData = filterByMonth(flightData, 5);
                        else if(monthDropdownText.getString().toAnsiString() == "June")
                            flightData = filterByMonth(flightData, 6);
                        else if(monthDropdownText.getString().toAnsiString() == "July")
                            flightData = filterByMonth(flightData, 7);
                        else if(monthDropdownText.getString().toAnsiString() == "August")
                            flightData = filterByMonth(flightData, 8);
                        else if(monthDropdownText.getString().toAnsiString() == "September")
                            flightData = filterByMonth(flightData, 9);
                        else if(monthDropdownText.getString().toAnsiString() == "October")
                            flightData = filterByMonth(flightData, 10);
                        else if(monthDropdownText.getString().toAnsiString() == "November")
                            flightData = filterByMonth(flightData, 11);
                        else if(monthDropdownText.getString().toAnsiString() == "December")
                            flightData = filterByMonth(flightData, 12);
                    }
                    if(airlineDropdownText.getString().toAnsiString() != "None"){
                        flightData = filterByAirline(flightData, airlineDropdownText.getString().toAnsiString());
                    }

                    //Determine sort method
                    if(sortDropdownText.getString().toAnsiString() == "Heap"){
                        //timer start
                        auto start = std::chrono::high_resolution_clock::now();
                        //send the flightdata through heap sort
                        heapSort(flightData);
                        //end timer and calculate time to execute
                        auto end = std::chrono::high_resolution_clock::now();
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                        std::cout << "Heap sort execution time: " << duration.count() << " milliseconds" << std::endl;
                    }
                    else if(sortDropdownText.getString().toAnsiString() == "Merge"){
                        // Start timing
                        auto start = std::chrono::high_resolution_clock::now();
                        // Sort flight data by flight delay using merge sort
                        mergeSort(flightData, 0, flightData.size() - 1);
                        // End timing
                        auto end = std::chrono::high_resolution_clock::now();
                        // Calculate duration
                        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
                        std::cout << "Merge sort execution time: " << duration.count() << " milliseconds" << std::endl;
                    }
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
