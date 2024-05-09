#include "StationParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

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

} // namespace travel
