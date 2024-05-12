#pragma once
#ifndef METRO_NETWORK_PARSER_HPP
#define METRO_NETWORK_PARSER_HPP

#include "src/Generic_mapper.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace travel {


class MetroNetworkParser : public Generic_mapper {
    std::unordered_map<uint64_t, Station> stations_hashmap;
    std::unordered_map<std::string, uint64_t> name_to_id_map;
    std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> connections_hashmap;

public:
    void read_stations(const std::string& filename) override;
    void read_connections(const std::string& filename) override;
    void print_all_stations() const;
    uint64_t get_station_id_by_name_and_line(const std::string& name, const std::string& line) const;
    std::string get_station_name_by_id(uint64_t id) const;
    Station get_station_by_id(uint64_t id) const;
    std::vector<std::pair<std::string, std::string>> searchStations(const std::string &input) const;
    uint64_t get_travel_time(uint64_t start_id, uint64_t end_id) const;
};

} // namespace travel

#endif // METRO_NETWORK_PARSER_HPP
