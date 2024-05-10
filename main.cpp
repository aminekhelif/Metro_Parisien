#include <iostream>
#include "StationParser.hpp"
#include "ConnectionParser.hpp"
#include "Navigation.hpp"

int main()
{
    // Initialize the station and connection parsers
    travel::StationParser stationParser;
    travel::ConnectionParser connectionParser;

    // Load station and connection data
    stationParser.read_stations("src/data/s.csv");       // Ensure stations.csv exists with correct data
    connectionParser.read_connections("src/data/c.csv"); // Ensure connections.csv exists with correct data

    // Print all stations
    // std::cout << "All Stations:" << std::endl;
    // stationParser.print_all_stations();
    // std::cout << std::endl;

    // Initialize navigation system with connections and a reference to the station parser
    travel::Navigation navigation(connectionParser.get_connections_hashmap(), stationParser);

    // Define start and end stations by name for path calculation
    std::string startStationName = "Villiers";
    std::string startStationLine = "2";
    std::string endStationName = "Trocadéro";
    std::string endStationLine = "6";

    // Compute shortest path from start station to end station by names
    navigation.computeShortestPath(startStationName, startStationLine);

    // Print the shortest path from start to end station by names
    try {
        std::string lastStationName = "";
        std::string lastStationLine = "";

        auto path = navigation.getShortestPath(stationParser.get_station_id_by_name_and_line(endStationName, endStationLine));
        for (auto station_id : path) {
            const auto& station = stationParser.get_station_by_id(station_id);
            if (station.name != lastStationName || station.line_id != lastStationLine) {
                std::cout << station.name << " (Line " << station.line_id << ")" << std::endl;
                lastStationName = station.name;
                lastStationLine = station.line_id;
            }
        }

        std::cout << "Total Distance: " 
                  << navigation.getShortestDistance(stationParser.get_station_id_by_name_and_line(endStationName, endStationLine)) 
                  << " units" << std::endl;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
