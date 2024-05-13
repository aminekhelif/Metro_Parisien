#pragma once

#ifndef METRO_NETWORK_PARSER_HPP
#define METRO_NETWORK_PARSER_HPP

#include "Generic_mapper.hpp"
#include <string>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <limits>
#include <algorithm>

namespace travel {
    class Navigation;  // Forward declaration
    
    /**
     * @brief The MetroNetworkParser class is responsible for parsing and managing the metro network data.
     * 
     * It inherits from the Generic_mapper class and provides methods for reading station and connection data,
     * computing and displaying travel routes, searching for stations, and accessing station information.
     */
    class MetroNetworkParser : public Generic_mapper {
       
    public:
        /**
         * @brief Constructs a MetroNetworkParser object.
         */
        MetroNetworkParser();

        /**
         * @brief Destroys the MetroNetworkParser object.
         */
        ~MetroNetworkParser();

        /**
         * @brief Initializes the data required for the metro network.
         */
        void initializeData();

        /**
         * @brief Computes the travel route between two stations.
         * 
         * @param _start The ID of the starting station.
         * @param _end The ID of the destination station.
         * @return A vector of pairs representing the travel route, where each pair contains the ID of a station and the ID of the line it belongs to.
         */
        std::vector<std::pair<uint64_t, uint64_t>> compute_travel(uint64_t _start, uint64_t _end) override;

        /**
         * @brief Computes and displays the travel route between two stations.
         * 
         * @param _start The ID of the starting station.
         * @param _end The ID of the destination station.
         * @return A vector of pairs representing the travel route, where each pair contains the ID of a station and the ID of the line it belongs to.
         */
        std::vector<std::pair<uint64_t, uint64_t>> compute_and_display_travel(uint64_t _start, uint64_t _end) override;

        /**
         * @brief Reads the station data from a file.
         * 
         * @param filename The name of the file containing the station data.
         */
        void read_stations(const std::string& filename) override;

        /**
         * @brief Reads the connection data from a file.
         * 
         * @param filename The name of the file containing the connection data.
         */
        void read_connections(const std::string& filename) override;

        /**
         * @brief Retrieves the ID of a station based on its name and line.
         * 
         * @param name The name of the station.
         * @param line The line the station belongs to.
         * @return The ID of the station.
         */
        uint64_t get_station_id_by_name_and_line(const std::string& name, const std::string& line) const;

        /**
         * @brief Retrieves the name of a station based on its ID.
         * 
         * @param id The ID of the station.
         * @return The name of the station.
         */
        std::string get_station_name_by_id(uint64_t id) const;

        /**
         * @brief Retrieves the station object based on its ID.
         * 
         * @param id The ID of the station.
         * @return The station object.
         */
        Station get_station_by_id(uint64_t id) const;

        /**
         * @brief Prints the information of all stations.
         */
        void print_all_stations() const;

        /**
         * @brief Searches for stations based on a given input.
         * 
         * @param input The input to search for.
         * @return A vector of pairs representing the search results, where each pair contains the name of a station and the line it belongs to.
         */
        std::vector<std::pair<std::string, std::string>> searchStations(const std::string &input) const;

        /**
         * @brief Retrieves the navigation object.
         * 
         * @return A pointer to the navigation object.
         */
        Navigation* getNavigation() const { return navigation; }

        std::unordered_map<uint64_t, Station> stations_hashmap;  // Hashmap to store station information
        std::unordered_map<std::string, uint64_t> name_to_id_map;  // Hashmap to map station names to IDs
        std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> connections_hashmap;  // Hashmap to store connection information
        Navigation* navigation;  // Pointer to Navigation

    };

} // namespace travel

#endif // METRO_NETWORK_PARSER_HPP
