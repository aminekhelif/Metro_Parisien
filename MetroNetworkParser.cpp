#include "MetroNetworkParser.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <limits>
#include <unordered_map>
#include <algorithm>

namespace travel {

void MetroNetworkParser::read_stations(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening station file." << std::endl;
        return;
    }
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        uint64_t id;
        std::string name, line_name;
        getline(ss, name, ',');
        getline(ss, line_name, ',');
        ss >> id;
        Station station{id, name, line_name};
        stations_hashmap[id] = station;
        name_to_id_map[name + line_name] = id;
    }
    file.close();
}

void MetroNetworkParser::read_connections(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening connection file." << std::endl;
        return;
    }
    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        uint64_t start_id, end_id, travel_time;
        ss >> start_id;
        ss >> end_id;
        ss >> travel_time;
        connections[start_id].push_back({end_id, travel_time});
    }
    file.close();
}

std::vector<std::pair<uint64_t, uint64_t>> MetroNetworkParser::compute_travel(uint64_t start, uint64_t end) {
    std::unordered_map<uint64_t, uint64_t> distances;
    std::unordered_map<uint64_t, uint64_t> previous;
    auto compare = [&] (const uint64_t& left, const uint64_t& right) {
        return distances[left] > distances[right];
    };
    std::priority_queue<uint64_t, std::vector<uint64_t>, decltype(compare)> queue(compare);
    distances[start] = 0;
    queue.push(start);

    while (!queue.empty()) {
        uint64_t current = queue.top();
        queue.pop();
        if (current == end) {
            break;
        }
        for (auto& neighbor : connections[current]) {
            uint64_t alt = distances[current] + neighbor.second;
            if (alt < distances[neighbor.first]) {
                distances[neighbor.first] = alt;
                previous[neighbor.first] = current;
                queue.push(neighbor.first);
            }
        }
    }

    std::vector<std::pair<uint64_t, uint64_t>> path;
    for (uint64_t at = end; at != start; at = previous[at]) {
        path.push_back({at, distances[at]});
    }
    path.push_back({start, distances[start]});
    std::reverse(path.begin(), path.end());
    return path;
}

std::vector<std::pair<uint64_t, uint64_t>> MetroNetworkParser::compute_and_display_travel(uint64_t start, uint64_t end) {
    auto path = compute_travel(start, end);
    for (auto& p : path) {
        std::cout << "Station ID: " << p.first << ", Distance: " << p.second << std::endl;
    }
    return path;
}

uint64_t MetroNetworkParser::get_station_id_by_name_and_line(const std::string& name, const std::string& line) const {
    std::string key = name + line;
    return name_to_id_map.at(key);
}

std::string MetroNetworkParser::get_station_name_by_id(uint64_t id) const {
    return stations_hashmap.at(id).name;
}

Station MetroNetworkParser::get_station_by_id(uint64_t id) const {
    return stations_hashmap.at(id);
}

std::vector<std::pair<std::string, std::string>> MetroNetworkParser::searchStations(const std::string &input) const {
    std::vector<std::pair<std::string, std::string>> results;
    for (const auto& [id, station] : stations_hashmap) {
        if (station.name.find(input) != std::string::npos) {
            results.emplace_back(station.name, station.line);
        }
    }
    return results;
}

} // namespace travel