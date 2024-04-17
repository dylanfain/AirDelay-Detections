#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct FlightData {
    std::string date;         // Date
    std::string airline;      // Airline
    int arrivalDelay;         // Arrival Delay
    bool weatherDelay;        // Weather Delay (0 or 1)
    int month;                // Month
};

int extractMonth(const std::string& date) {
    // Example date format: "3/1/2019"
    std::stringstream ss(date);
    std::string token;
    std::getline(ss, token, '/');
    return std::stoi(token); // Extract month
}


std::vector<FlightData> parseCSV(const std::string& filename) {
    std::vector<FlightData> data;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filename << std::endl;
        return data;
    }

    std::string line;
    // Skip header line
    std::getline(file, line);

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string cell;
        FlightData flight;

        // Skip first column (DayOfWeek)
        std::getline(ss, cell, ',');

        // Date (2nd column)
        std::getline(ss, flight.date, ',');
        flight.month = extractMonth(flight.date); // Extract and store month

        // Skip columns 3 to 6
        for (int i = 0; i < 4; ++i) {
            std::getline(ss, cell, ',');
        }

        // Airline (7th column)
        std::getline(ss, flight.airline, ',');

        // Skip columns 8 to 12
        for (int i = 0; i < 5; ++i) {
            std::getline(ss, cell, ',');
        }

        // Arrival Delay (13th column)
        std::getline(ss, cell, ',');
        flight.arrivalDelay = std::stoi(cell);

        // Skip columns 14 to 24
        for (int i = 0; i < 11; ++i) {
            std::getline(ss, cell, ',');
        }

        // Weather Delay (25th column)
        std::getline(ss, cell, ',');
        flight.weatherDelay = (std::stoi(cell) == 1); // Convert to boolean

        data.push_back(flight);
    }

    file.close();
    return data;
}

