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

    class MetroNetworkParser : public Generic_mapper {
    private:
        std::unordered_map<uint64_t, Station> stations_hashmap;
        std::unordered_map<std::string, uint64_t> name_to_id_map;
        std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> connections_hashmap;
        Navigation* navigation;  // Pointer to Navigation

    public:
        MetroNetworkParser();
        ~MetroNetworkParser();
        void initializeData();
        std::vector<std::pair<uint64_t, uint64_t>> compute_travel(uint64_t _start, uint64_t _end) override;
        std::vector<std::pair<uint64_t, uint64_t>> compute_and_display_travel(uint64_t _start, uint64_t _end) override;

        void read_stations(const std::string& filename) override;
        void read_connections(const std::string& filename) override;

        uint64_t get_station_id_by_name_and_line(const std::string& name, const std::string& line) const;
        std::string get_station_name_by_id(uint64_t id) const;
        Station get_station_by_id(uint64_t id) const;
        void print_all_stations() const;
        std::vector<std::pair<std::string, std::string>> searchStations(const std::string &input) const;

        Navigation* getNavigation() const { return navigation; }  // Accessor for navigation
    };

} // namespace travel

#endif // METRO_NETWORK_PARSER_HPP
