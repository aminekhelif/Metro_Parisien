#include "ConnectionParser.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

namespace travel {

void ConnectionParser::read_connections(const std::string& filename) {
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

void ConnectionParser::read_stations(const std::string& filename) {
    // Stub implementation, do nothing
}

} // namespace travel
