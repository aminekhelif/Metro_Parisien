#include "StationParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <limits>
#include <algorithm> // Include for std::transform

namespace travel {

void StationParser::read_stations(const std::string& filename) {
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
            name_to_id_map[station.name + "|" + station.line_id] = id;  // Populate reverse lookup map
        } catch (const std::exception& e) {
                std::cerr << "Error parsing line: " << line << " - Exception: " << e.what() << std::endl;
            }
        }

        file.close();
    }

void StationParser::print_all_stations() const {
    for (const auto& pair : stations_hashmap) {
        const Station& station = pair.second;
            std::cout << "Station ID: " << pair.first
                      << ", Name: " << station.name
                      << ", Line ID: " << station.line_id
                      << ", Address: " << station.address
                      << ", Line Name: " << station.line_name << std::endl;
        }
    }

    uint64_t StationParser::get_station_id_by_name_and_line(const std::string& name, const std::string& line) const {
    std::string key = name + "|" + line;
    auto it = name_to_id_map.find(key);
    if (it != name_to_id_map.end()) {
        return it->second;
    }
    return std::numeric_limits<uint64_t>::max();
}

std::string StationParser::get_station_name_by_id(uint64_t id) const {
        auto it = stations_hashmap.find(id);
    if (it != stations_hashmap.end()) {
            return it->second.name; // Return the name of the station
    } else {
            return "Station ID not found"; // Return error message if ID not found
        }
    }
Station StationParser::get_station_by_id(uint64_t id) const {
        auto it = stations_hashmap.find(id);
        if (it != stations_hashmap.end()) {
            return it->second;
    } else {
            throw std::runtime_error("Station ID not found"); // Throw an error if the ID is not found
        }
    }
    std::vector<std::pair<std::string, std::string>> StationParser::searchStations(const std::string &input) const
    {
        std::vector<std::pair<std::string, std::string>> matches;
        std::string lowerInput = input;
        std::transform(lowerInput.begin(), lowerInput.end(), lowerInput.begin(), ::tolower); // Convert input to lowercase

        for (const auto &pair : stations_hashmap)
        {
            std::string lowerName = pair.second.name;
            std::transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower); // Convert station name to lowercase

            if (lowerName.find(lowerInput) != std::string::npos)
            {
                matches.emplace_back(pair.second.name, pair.second.line_id); // Add matching station name and line
            }
        }
        return matches;
    }

} // namespace travel
