#include <iostream>
#include "StationParser.hpp"
#include "ConnectionParser.hpp"
#include "Navigation.hpp"

// Function to get user input for a station and line, with retry mechanism
bool getUserInput(const std::string& prompt, std::string& stationName, std::string& line, const travel::StationParser& stationParser) {
    while (true) {
        std::cout << prompt << " station name or type 'exit' to quit: ";
        getline(std::cin, stationName);
        if (stationName == "exit") return false;

        std::cout << "Enter " << prompt << " station line or type 'exit' to quit: ";
        getline(std::cin, line);
        if (line == "exit") return false;

        if (stationParser.get_station_id_by_name_and_line(stationName, line) != std::numeric_limits<uint64_t>::max()) {
            return true; // Valid station and line
        }

        // Provide suggestions if the station or line is not found
        std::cout << "No exact match found. Here are some suggestions based on your input:" << std::endl;
        auto suggestions = stationParser.searchStations(stationName);
        for (const auto& suggestion : suggestions) {
            std::cout << suggestion.first << " (Line " << suggestion.second << ")" << std::endl;
        }
        std::cout << "Please try again.\n";
    }
}

int main() {
    travel::StationParser stationParser;
    travel::ConnectionParser connectionParser;
    stationParser.read_stations("src/data/s.csv");
    connectionParser.read_connections("src/data/c.csv");
    travel::Navigation navigation(connectionParser.get_connections_hashmap(), stationParser);

    std::string startStationName, startStationLine, endStationName, endStationLine;

    while (true) {
        std::cout << "\n--- New Path Search ---\n";
        if (!getUserInput("start", startStationName, startStationLine, stationParser) ||
            !getUserInput("end", endStationName, endStationLine, stationParser)) {
            std::cout << "Exiting program.\n";
            break;
        }

        // Compute and print the path if valid inputs are given
        navigation.computeShortestPath(startStationName, startStationLine);
        auto path = navigation.getShortestPath(stationParser.get_station_id_by_name_and_line(endStationName, endStationLine));
        std::cout << "Shortest Path from " << startStationName << " to " << endStationName << ":" << std::endl;
        for (auto station_id : path) {
            const auto& station = stationParser.get_station_by_id(station_id);
            std::cout << station.name << " (Line " << station.line_id << ")" << std::endl;
        }

        std::cout << "Total Distance: " 
                  << navigation.getShortestDistance(stationParser.get_station_id_by_name_and_line(endStationName, endStationLine)) 
                  << " units" << std::endl;

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
