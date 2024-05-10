#pragma once

#include "Generic_mapper.hpp"

namespace travel {
class MyMapper : public Generic_mapper {
public:
    void read_stations(const std::string& filename) override {
        StationParser stationParser;
        stationParser.read_stations(filename);
    }

    void read_connections(const std::string& filename) override {
        ConnectionParser connectionParser;
        connectionParser.read_connections(filename);
    }

    std::vector<std::pair<uint64_t, uint64_t>> compute_travel(uint64_t start, uint64_t end) override {
        ConnectionParser connectionParser;
        Navigation navigation(connectionParser.get_connections_hashmap());
        navigation.computeShortestPath(start);
        return navigation.getShortestPath(end);
    }

    std::vector<std::pair<uint64_t, uint64_t>> compute_and_display_travel(uint64_t start, uint64_t end) override {
        ConnectionParser connectionParser;
        Navigation navigation(connectionParser.get_connections_hashmap());
        navigation.computeShortestPath(start);

        std::cout << "Shortest path from station " << start << " to station " << end << ":" << std::endl;
        for (uint64_t id : navigation.getShortestPath(end)) {
            std::cout << id << " ";
        }
        std::cout << std::endl;

        return navigation.getShortestPath(end);
    }
};
}  // namespace travel