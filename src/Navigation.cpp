#include "Navigation.hpp"

namespace travel
{
    
        Navigation::Navigation(const std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& connections_hashmap, StationParser& parser)
        : connections_hashmap(connections_hashmap), stationParser(parser)
    {
        uint64_t max_node_id = 0;
        for (const auto &entry : connections_hashmap)
        {
            max_node_id = std::max(max_node_id, entry.first);
            for (const auto &neighbor : entry.second)
            {
                max_node_id = std::max(max_node_id, neighbor.first);
            }
        }

        distance.resize(max_node_id + 1, std::numeric_limits<uint64_t>::max());
        previous.resize(max_node_id + 1, std::numeric_limits<uint64_t>::max());
    }

    void Navigation::computeShortestPath(const std::string& startName, const std::string& startLine) 
    {
        std::fill(distance.begin(), distance.end(), std::numeric_limits<uint64_t>::max());
        std::fill(previous.begin(), previous.end(), std::numeric_limits<uint64_t>::max());
        while (!pq.empty())
            pq.pop(); // Clear the priority queue
        uint64_t startId = stationParser.get_station_id_by_name_and_line(startName, startLine);
        
        if (connections_hashmap.find(startId) == connections_hashmap.end()) 
        {
            std::cerr << "Error: Start node not found in connections." << std::endl;
            return;
        }

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
            }}
        }
    }

    void Navigation::printShortestPath(const std::string& endName, const std::string& endLine) const {
        uint64_t endId = stationParser.get_station_id_by_name_and_line(endName, endLine);
        if (previous[endId] == std::numeric_limits<uint64_t>::max()) 
        {
            std::cout << "No path from start to end" << std::endl;
            return;
        }

        std::vector<uint64_t> path;
        for (uint64_t at = endId; at != std::numeric_limits<uint64_t>::max(); at = previous[at]) 
        {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        for (const auto& id : path) {
            // Ensure this method exists or create it
            std::cout << stationParser.get_station_name_by_id(id) << " ";
        }
        std::cout << std::endl;
    }

    uint64_t Navigation::getShortestDistance(uint64_t end) const
    {
        return distance[end];
    }

    std::vector<uint64_t> Navigation::getShortestPath(uint64_t end) const
    {
        std::vector<uint64_t> path;
        for (uint64_t at = end; at != std::numeric_limits<uint64_t>::max(); at = previous[at])
        {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
        return path;
    }

} // namespace travel