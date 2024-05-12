#include "Navigation.hpp"

namespace travel {

Navigation::Navigation(MetroNetworkParser& parser)
: metroNetworkParser(parser) {
    uint64_t max_node_id = 0; // Assuming MetroNetworkParser can provide this information if not, we need to adjust this.
    // Initialize distance and previous vectors to appropriate sizes and values
    distance.resize(max_node_id + 1, std::numeric_limits<uint64_t>::max());
    previous.resize(max_node_id + 1, std::numeric_limits<uint64_t>::max());
}

void Navigation::computeShortestPath(const std::string& start, const std::string& startLine) {
    uint64_t startId = metroNetworkParser.get_station_id_by_name_and_line(start, startLine);
    if (startId == 0) {
        std::cerr << "Start station not found." << std::endl;
        return;
    }

    distance[startId] = 0;
    pq.push(std::make_pair(0, startId));

    while (!pq.empty()) {
        uint64_t u = pq.top().second;
        pq.pop();

        if (distance[u] != std::numeric_limits<uint64_t>::max()) {
            auto neighbors = metroNetworkParser.get_connections(u); // Method to retrieve all connections from a station
            for (const auto &pair : neighbors) {
                uint64_t v = pair.first;
                uint64_t w = pair.second;

                if (distance[v] > distance[u] + w) {
                    distance[v] = distance[u] + w;
                    previous[v] = u;
                    pq.push(std::make_pair(distance[v], v));
                }
            }
        }
    }
}

void Navigation::printShortestPath(const std::string& end, const std::string& endLine) const {
    uint64_t endId = metroNetworkParser.get_station_id_by_name_and_line(end, endLine);
    if (endId == 0 || previous[endId] == std::numeric_limits<uint64_t>::max()) {
        std::cout << "No path from start to end." << std::endl;
        return;
    }

    std::vector<uint64_t> path;
    for (uint64_t at = endId; at != std::numeric_limits<uint64_t>::max(); at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());

    for (const auto& id : path) {
        std::cout << metroNetworkParser.get_station_name_by_id(id) << " ";
    }
    std::cout << std::endl;
}

uint64_t Navigation::getShortestDistance(uint64_t end) const {
    return distance[end];
}

std::vector<uint64_t> Navigation::getShortestPath(uint64_t end) const {
    std::vector<uint64_t> path;
    for (uint64_t at = end; at != std::numeric_limits<uint64_t>::max(); at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace travel
