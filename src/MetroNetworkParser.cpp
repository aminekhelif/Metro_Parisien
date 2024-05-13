
#include "MetroNetworkParser.hpp"
#include "Navigation.hpp"

namespace travel {

MetroNetworkParser::MetroNetworkParser(){
    std::cout << "MetroNetworkParser constructor called" << std::endl;
    initializeData();
}

MetroNetworkParser::~MetroNetworkParser() {
    delete navigation;  // Properly delete navigation
}

void MetroNetworkParser::initializeData() {
    read_stations("src/data/s.csv");
    read_connections("src/data/c.csv");
    navigation = new Navigation(*this);  // Properly initialize navigation after all data is loaded

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
            // std::cout << "Loaded station: " << station.name << " ID: " << id << std::endl;
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

            // Debug output
            // std::cout << "Connection from " << start_id << " to " << end_id << " with duration " << duration << " loaded." << std::endl;
        } catch (const std::exception& e) {
            std::cerr << "Error parsing line: " << line << " - Exception: " << e.what() << std::endl;
        }

    }
    file.close();

    // Print the entire connections hashmap for verification
    // for (const auto& conn : connections_hashmap) {
    //     // std::cout << "Station " << conn.first << " connects to: ";
    //     for (const auto& dest : conn.second) {
    //         // std::cout << dest.first << " (duration " << dest.second << "), ";
    //     }
    //     std::cout << std::endl;
    // }
}


// Computes the shortest path between two station IDs and returns it as a list of ID pairs representing segments of the journey
std::vector<std::pair<uint64_t, uint64_t>> MetroNetworkParser::compute_travel(uint64_t start, uint64_t end) {
    Station startStation = get_station_by_id(start);
    // std::cout << "Start station inside compute_travel: " << startStation.name << std::endl;
    try
    {
        navigation->computeShortestPath(startStation.name, startStation.line_id);
        auto path_ids = navigation->getShortestPath(end); // ensure this returns a vector of IDs

        std::vector<std::pair<uint64_t, uint64_t>> paths;
        for (size_t i = 0; i < path_ids.size()  ; i++) {
            paths.emplace_back(path_ids[i], path_ids[i + 1]);
        }
        return paths;
    }
    catch(const std::exception& e)
    {   
        std::cerr << "Error: " << e.what() << std::endl;
        return {};
    }
    
}


std::vector<std::pair<uint64_t, uint64_t>> MetroNetworkParser::compute_and_display_travel(uint64_t start, uint64_t end) {
    auto path = compute_travel(start, end);
    for (auto& segment : path) {
        if (segment.first == end) {
            std::cout << get_station_by_id(segment.first).name << ", Line :  "<< get_station_by_id(segment.first).line_id << std::endl;
            break;
        }else{
            std::cout << get_station_by_id(segment.first).name << ", Line :  "<< get_station_by_id(segment.first).line_id << " -> ";
        }
    }
    return path;
}


// Returns the station ID given a station name and line
uint64_t MetroNetworkParser::get_station_id_by_name_and_line(const std::string& name, const std::string& line) const {
    std::string key = name + "|" + line;
    auto it = name_to_id_map.find(key);
    if (it != name_to_id_map.end()) {
        // std::cout << "Station ID found: " << it->second << std::endl;
        return it->second;
    }
    throw std::runtime_error("Station ID not found (get_station_id_by_name_and_line)");
}

// Returns the station name given an ID
std::string MetroNetworkParser::get_station_name_by_id(uint64_t id) const {
    auto it = stations_hashmap.find(id);
    if (it != stations_hashmap.end()) {
        return it->second.name;
    }
    throw std::runtime_error("Station name not found (get_station_name_by_id)");
}

// Returns a Station object given an ID
Station MetroNetworkParser::get_station_by_id(uint64_t id) const {
    auto it = stations_hashmap.find(id);
    if (it != stations_hashmap.end()) {
        return it->second;
    }
    throw std::runtime_error("Station ID not found (get_station_by_id)");
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
