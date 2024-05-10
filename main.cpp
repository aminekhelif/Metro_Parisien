#include <iostream>
#include <string>
#include <cctype>
#include "StationParser.hpp"
#include "ConnectionParser.hpp"
#include "Navigation.hpp"

// Function to normalize the input string by converting it to lowercase and removing punctuation.
std::string normalize(const std::string& input) {
    std::string result;
    result.reserve(input.size());
    for (char c : input) {
        if (!std::ispunct(static_cast<unsigned char>(c))) {
            result.push_back(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

// Function to prompt the user for station and line information, with validation and suggestions.
bool getUserInput(const std::string& prompt, std::string& stationName, std::string& line, const travel::StationParser& stationParser) {
    // explain exit option
    while (true) {
        std::cout << prompt << " station name: ";
        getline(std::cin, stationName);
        if (stationName == "exit") return false;

        std::cout << "Enter " << prompt << " station line: ";
        getline(std::cin, line);
        if (line == "exit") return false;

        // Validate the provided station and line against the database
        if (stationParser.get_station_id_by_name_and_line(stationName, line) != std::numeric_limits<uint64_t>::max()) {
            return true;  // Station and line are valid
        }

        // Provide suggestions if no exact match is found
        std::cout << "No exact match found. Here are some suggestions based on your input:" << std::endl;
        auto suggestions = stationParser.searchStations(stationName);
        for (const auto& suggestion : suggestions) {
            std::cout << suggestion.first << " (Line " << suggestion.second << ")" << std::endl;
        }
        std::cout << "Please try again.\n";
    }
}

int main() {
    // Initialize parsers for stations and connections and load data
    travel::StationParser stationParser;
    travel::ConnectionParser connectionParser;
    stationParser.read_stations("src/data/s.csv");
    connectionParser.read_connections("src/data/c.csv");
    travel::Navigation navigation(connectionParser.get_connections_hashmap(), stationParser);

    std::string startStationName, startStationLine, endStationName, endStationLine;

    // Main loop to handle user queries for paths
    while (true) {
        std::cout << "\n--- New Path Search ---\n";
        std::cout << std::endl<< "Type 'exit' at any time to quit the program." << std::endl;
        if (!getUserInput("start", startStationName, startStationLine, stationParser) ||
            !getUserInput("end", endStationName, endStationLine, stationParser)) {
            std::cout << "Exiting program.\n";
            break;
        }

        // Calculate and display the shortest path between the given stations
        navigation.computeShortestPath(startStationName, startStationLine);
        auto path = navigation.getShortestPath(stationParser.get_station_id_by_name_and_line(endStationName, endStationLine));
        std::cout << "Shortest Path from " << startStationName << " to " << endStationName << ":" << std::endl;
        for (auto station_id : path) {
            const auto& station = stationParser.get_station_by_id(station_id);
            std::cout << station.name << " (Line " << station.line_id << ")" << std::endl;
        }

        // Display the total distance of the path
        std::cout << "Total Distance: "
                  << navigation.getShortestDistance(stationParser.get_station_id_by_name_and_line(endStationName, endStationLine))
                  << " units" << std::endl;

        // Prompt for another search
        std::cout << "Do you want to search for another path? (yes to continue): ";
        std::string answer;
        getline(std::cin, answer);
        if (answer != "yes") {
            std::cout << "Exiting program.\n";
            break;
        }
    }

    return 0;
}
