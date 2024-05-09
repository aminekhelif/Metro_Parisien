#include <iostream>
#include "src/StationParser.hpp"
#include "src/ConnectionParser.hpp"

int main() {
    travel::StationParser stationParser;
    travel::ConnectionParser connectionParser;

    try {
        // Load station data
        stationParser.read_stations("src/data/stations.csv");
        std::cout << "Stations loaded successfully." << std::endl;

        // Load connection data
        connectionParser.read_connections("src/data/connections.csv");
        std::cout << "Connections loaded successfully." << std::endl;

        // Print all stations
        stationParser.print_all_stations();

        // If you add a similar method in ConnectionParser, call it here to print connections.

    } catch (const std::exception& e) {
        std::cerr << "An error occurred: " << e.what() << std::endl;
    }

    return 0;
}
