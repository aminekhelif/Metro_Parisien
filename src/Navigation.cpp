#include "Navigation.hpp"
#include "MetroNetworkParser.hpp"

namespace travel {

/**
 * @brief Constructs a Navigation object.
 * 
 * @param parser The MetroNetworkParser object used for parsing the metro network.
 */
Navigation::Navigation(MetroNetworkParser& parser)
: connections_hashmap(parser.connections_hashmap), metroNetworkParser(parser) {
    std::cout << "Navigation constructor called" << std::endl;
    uint64_t max_node_id = 0;
    for (const auto &entry : connections_hashmap) {
        max_node_id = std::max(max_node_id, entry.first);
        for (const auto &neighbor : entry.second) {
            max_node_id = std::max(max_node_id, neighbor.first);
        }
    }
    distance.resize(max_node_id + 1, std::numeric_limits<uint64_t>::max());
    previous.resize(max_node_id + 1, std::numeric_limits<uint64_t>::max());
}

/**
 * @brief Computes the shortest path from a given start station to all other stations in the metro network.
 * 
 * @param startName The name of the start station.
 * @param startLine The line of the start station.
 */
void Navigation::computeShortestPath(const std::string& startName, const std::string& startLine) 
{
    std::fill(distance.begin(), distance.end(), std::numeric_limits<uint64_t>::max());
    std::fill(previous.begin(), previous.end(), std::numeric_limits<uint64_t>::max());
    while (!pq.empty())
        pq.pop(); // Clear the priority queue
    uint64_t startId = metroNetworkParser.get_station_id_by_name_and_line(startName, startLine);

    distance[startId] = 0;
    pq.push(std::make_pair(0, startId));

    while (!pq.empty())
    {
        uint64_t u = pq.top().second;
        pq.pop();

        if (connections_hashmap.find(u) != connections_hashmap.end()) {
            for (const auto &pair : connections_hashmap.at(u))
            {
                uint64_t v = pair.first;
                uint64_t w = pair.second;

                if (distance[v] > distance[u] + w)
                {
                    distance[v] = distance[u] + w;
                    previous[v] = u;
                    pq.push(std::make_pair(distance[v], v));
                }
            }
        }
        else{
            std::cerr << "Error: Node not found in connections." << std::endl;
        }
    }
}

/**
 * @brief Prints the shortest path from a given end station to the start station.
 * 
 * @param endName The name of the end station.
 * @param endLine The line of the end station.
 */
void Navigation::printShortestPath(const std::string& endName, const std::string& endLine) const {
    uint64_t endId = metroNetworkParser.get_station_id_by_name_and_line(endName, endLine);
    if (previous[endId] == std::numeric_limits<uint64_t>::max()) {
        std::cout << "No path from start to end" << std::endl;
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

/**
 * @brief Gets the shortest distance from the start station to a given end station.
 * 
 * @param end The ID of the end station.
 * @return The shortest distance from the start station to the end station.
 */
uint64_t Navigation::getShortestDistance(uint64_t end) const {
    return distance[end];
}

/**
 * @brief Gets the shortest path from the start station to a given end station.
 * 
 * @param end The ID of the end station.
 * @return A vector containing the IDs of the stations in the shortest path.
 */
std::vector<uint64_t> Navigation::getShortestPath(uint64_t end) const {
    std::vector<uint64_t> path;
    for (uint64_t at = end; at != std::numeric_limits<uint64_t>::max(); at = previous[at]) {
        path.push_back(at);
    }
    std::reverse(path.begin(), path.end());
    return path;
}

} // namespace travel
