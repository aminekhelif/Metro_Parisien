// StationParser.hpp
#pragma once
#ifndef STATION_PARSER_HPP
#define STATION_PARSER_HPP

#include "Generic_station_parser.hpp"
#include <string>
#include <unordered_map>

namespace travel {

class StationParser : public Generic_station_parser {
    std::unordered_map<uint64_t, Station> stations_hashmap;
    std::unordered_map<std::string, uint64_t> name_to_id_map; // Maps station name and line to ID for reverse lookup

public:
    void read_stations(const std::string& filename) override;
    void print_all_stations() const; // Method to print all stations
    uint64_t get_station_id_by_name_and_line(const std::string& name, const std::string& line);
    std::string get_station_name_by_id(uint64_t id) const; // Existing method
    Station get_station_by_id(uint64_t id) const; // New method declaration
};

} // namespace travel

#endif // STATION_PARSER_HPP
