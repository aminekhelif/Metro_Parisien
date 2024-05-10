#include <iostream>
#include "MyMapper.hpp"
#include "Navigation.hpp"

int main() {
    travel::MyMapper mapper;

    try {
        // Load station and connection data
        mapper.read_stations("src/data/s.csv");
        mapper.read_connections("src/data/c.csv");

        // Print all stations
        mapper.print_all_stations();

        // Example: Calculate shortest path using Navigation class
        travel::Navigation navigation(mapper.get_connections_hashmap());

        // Compute shortest path from station ID 1 to station ID 10
        uint64_t startStationId = 1629;
        uint64_t endStationId = 1640;
        navigation.computeShortestPath(startStationId);

        // Print shortest path and distance
        navigation.printShortestPath(endStationId);
        std::cout << "Shortest distance from station " << startStationId << " to station " << endStationId << ": "
                  << navigation.getShortestDistance(endStationId) << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}