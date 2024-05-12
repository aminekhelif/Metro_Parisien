#include "MetroNetworkParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <algorithm>

namespace travel {

void MetroNetworkParser::read_stations(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the header

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        Station station;
        std::string id_str;
        std::getline(iss, station.name, ',');
        std::getline(iss, id_str, ',');
        std::getline(iss, station.line_id, ',');
        std::getline(iss, station.address, ',');
        std::getline(iss, station.line_name, ',');

        try {
            uint64_t id = std::stoull(id_str);
            stations_hashmap[id] = station;
            name_to_id_map[station.name + station.line_name] = id;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - Exception: " << e.what() << std::endl;
        }
    }

    file.close();
}

void MetroNetworkParser::read_connections(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip the header

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string start_id_str, end_id_str, duration_str;
        std::getline(iss, start_id_str, ',');
        std::getline(iss, end_id_str, ',');
        std::getline(iss, duration_str, ',');

        try {
            uint64_t start_id = std::stoull(start_id_str);
            uint64_t end_id = std::stoull(end_id_str);
            uint64_t duration = std::stoull(duration_str);

            connections_hashmap[start_id][end_id] = duration;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - Exception: " << e.what() << std::endl;
        }
    }

    file.close();
}

void MetroNetworkParser::print_all_stations() const {
    for (const auto& pair : stations_hashmap) {
        std::cout << "Station ID: " << pair.first << " - Name: " << pair.second.name << ", Line: " << pair.second.line_name << std::endl;
    }
}
uint64_t MetroNetworkParser::get_station_id_by_name_and_line(const std::string& name, const std::string& line) const {
    auto it = name_to_id_map.find(name + line);
    if (it != name_to_id_map.end()) {
        return it->second;
    }
    return 0; // Not found
}

std::string MetroNetworkParser::get_station_name_by_id(uint64_t id) const {
    auto it = stations_hashmap.find(id);
    if (it != stations_hashmap.end()) {
        return it->second.name;
    }
    return ""; // Not found
}

Station MetroNetworkParser::get_station_by_id(uint64_t id) const {
    return stations_hashmap.at(id);
}

std::vector<std::pair<std::string, std::string>> MetroNetworkParser::searchStations(const std::string &input) const {
    std::vector<std::pair<std::string, std::string>> matches;
    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower);

    for (const auto& pair : stations_hashmap) {
        std::string lowerName = pair.second.name;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

        if (lowerName.find(lowerInput) != std::string::npos) {
            matches.emplace_back(pair.second.name, pair.second.line_name);
        }
    }
    return matches;
}

uint64_t MetroNetworkParser::get_travel_time(uint64_t start_id, uint64_t end_id) const {
    auto start_it = connections_hashmap.find(start_id);
    if (start_it != connections_hashmap.end()) {
        auto end_it = start_it->second.find(end_id);
        if (end_it != start_it->second.end()) {
            return end_it->second;
        }
    }
    return std::numeric_limits<uint64_t>::max(); // Indicates no valid path
}


} // namespace travel
