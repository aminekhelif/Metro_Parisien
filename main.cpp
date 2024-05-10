#include <iostream>
#include "src/StationParser.hpp"
#include "src/ConnectionParser.hpp"
#include "src/Navigation.hpp"

int main() {
    travel::StationParser stationParser;
    travel::ConnectionParser connectionParser;

    try {
        // Load station data
        stationParser.read_stations("src/data/s.csv");
        std::cout << "Stations loaded successfully." << std::endl;

        // Load connection data
        connectionParser.read_connections("src/data/c.csv");
        std::cout << "Connections loaded successfully." << std::endl;

        // Print all stations
        stationParser.print_all_stations();

        // Example: Calculate shortest path using Navigation class
        travel::Navigation navigation(connectionParser.get_connections_hashmap());

        // Compute shortest path from station ID 1 to station ID 10
        uint64_t startStationId = 1629;
        uint64_t endStationId = 1640;
        navigation.computeShortestPath(startStationId);

        // Print shortest path and distance
        navigation.printShortestPath(endStationId);
        std::cout << "Shortest distance from station " << startStationId << " to station " << endStationId << ": "
                  << navigation.getShortestDistance(endStationId) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}