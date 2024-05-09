#pragma once
#ifndef STATION_PARSER_HPP
#define STATION_PARSER_HPP

#include "Generic_station_parser.hpp"
#include <string>

namespace travel {

class StationParser : public Generic_station_parser {
public:
    void read_stations(const std::string& filename) override;
    void print_all_stations() const; // Method to print all stations
};

} // namespace travel

#endif // STATION_PARSER_HPP
