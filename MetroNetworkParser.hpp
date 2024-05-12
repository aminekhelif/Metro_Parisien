#pragma once
#ifndef METRO_NETWORK_PARSER_HPP
#define METRO_NETWORK_PARSER_HPP

#include "src/Generic_mapper.hpp"
#include <string>
#include <unordered_map>
#include <vector>

namespace travel {

struct Station {
    uint64_t id;
    std::string name;
    std::string line;
    // Additional station-related properties can be added here
};

class MetroNetworkParser : public Generic_mapper {
private:
    std::unordered_map<uint64_t, Station> stations_hashmap;
    std::unordered_map<std::string, uint64_t> name_to_id_map; // Maps station name and line to ID for reverse lookup
    std::unordered_map<uint64_t, std::vector<std::pair<uint64_t, uint64_t>>> connections; // Maps from station ID to a list of connections (other station ID and travel time)

public:
    void read_stations(const std::string& filename) override;
    void read_connections(const std::string& filename) override;
    std::vector<std::pair<uint64_t, uint64_t>> compute_travel(uint64_t start, uint64_t end) override;
    std::vector<std::pair<uint64_t, uint64_t>> compute_and_display_travel(uint64_t start, uint64_t end) override;
    uint64_t get_station_id_by_name_and_line(const std::string& name, const std::string& line) const;
    std::string get_station_name_by_id(uint64_t id) const;
    Station get_station_by_id(uint64_t id) const;
    std::vector<std::pair<std::string, std::string>> searchStations(const std::string &input) const;
};

} // namespace travel

#endif // METRO_NETWORK_PARSER_HPP