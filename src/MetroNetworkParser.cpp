// #include <limits>
// #include <queue>
// #include <iostream>
// #include <algorithm>

#include "MetroNetworkParser.hpp"
#include "Navigation.hpp"

namespace travel {

MetroNetworkParser::MetroNetworkParser() : navigation(nullptr) {
}

MetroNetworkParser::~MetroNetworkParser() {
    delete navigation;  // Properly delete navigation
}

void MetroNetworkParser::initializeData() {
    read_stations("src/data/s.csv");
    read_connections("src/data/c.csv");
    navigation = new Navigation(*this);  // Properly initialize navigation
}


// Reads station data from a file and populates the stations_hashmap
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
            name_to_id_map[station.name + "|" + station.line_id] = id;
            std::cout << "Loaded station: " << station.name << " ID: " << id << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - Exception: " << e.what() << std::endl;
        }
    }
    file.close();
    
}

// Reads connection data from a file and populates the connections_hashmap
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

// Computes the shortest path between two station IDs and returns it as a list of ID pairs representing segments of the journey
std::vector<std::pair<uint64_t, uint64_t>> MetroNetworkParser::compute_travel(uint64_t start, uint64_t end) {
    Station startStation = get_station_by_id(start);
    navigation->computeShortestPath(startStation.name, startStation.line_id);
    std::vector<uint64_t> path_ids = navigation->getShortestPath(end);

    std::vector<std::pair<uint64_t, uint64_t>> path;
    for (size_t i = 0; i < path_ids.size() - 1; i++) {
        path.emplace_back(path_ids[i], path_ids[i + 1]);
    }
    return path;
}

std::vector<std::pair<uint64_t, uint64_t>> MetroNetworkParser::compute_and_display_travel(uint64_t start, uint64_t end) {
    auto path = compute_travel(start, end);
    for (auto& segment : path) {
        std::cout << get_station_name_by_id(segment.first) << " to " << get_station_name_by_id(segment.second) << std::endl;
    }
    return path;
}


// Returns the station ID given a station name and line
uint64_t MetroNetworkParser::get_station_id_by_name_and_line(const std::string& name, const std::string& line) const {
    std::string key = name + "|" + line;
    auto it = name_to_id_map.find(key);
    if (it != name_to_id_map.end()) {
        return it->second;
    }
    return std::numeric_limits<uint64_t>::max(); // Return a max value to indicate not found
}

// Returns the station name given an ID
std::string MetroNetworkParser::get_station_name_by_id(uint64_t id) const {
    auto it = stations_hashmap.find(id);
    if (it != stations_hashmap.end()) {
        return it->second.name;
    }
    return "Station ID not found";
}

// Returns a Station object given an ID
Station MetroNetworkParser::get_station_by_id(uint64_t id) const {
    auto it = stations_hashmap.find(id);
    if (it != stations_hashmap.end()) {
        return it->second;
    }
    throw std::runtime_error("Station ID not found");
}

// Print all stations stored in the parser
void MetroNetworkParser::print_all_stations() const {
    for (const auto& pair : stations_hashmap) {
        const Station& station = pair.second;
        std::cout << "Station ID: " << pair.first
                  << ", Name: " << station.name
                  << ", Line ID: " << station.line_id
                  << ", Address: " << station.address
                  << ", Line Name: " << station.line_name << std::endl;
    }
}

std::vector<std::pair<std::string, std::string>> MetroNetworkParser::searchStations(const std::string &input) const {
    std::vector<std::pair<std::string, std::string>> matches;
    std::string lowerInput = input;
    std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower); // Convert input to lowercase

    for (const auto &pair : stations_hashmap) {
        std::string lowerName = pair.second.name;
        std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower); // Convert station name to lowercase

        if (lowerName.find(lowerInput) != std::string::npos) {
            matches.emplace_back(pair.second.name, pair.second.line_id); // Add matching station name and line
        }
    }
    return matches;
}


} // namespace travel
