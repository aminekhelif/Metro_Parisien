#include "Navigation.hpp"

namespace travel
{

    Navigation::Navigation(const std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> &connections_hashmap)
        : connections_hashmap(connections_hashmap)
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

    void Navigation::computeShortestPath(uint64_t start)
    {
        if (connections_hashmap.find(start) == connections_hashmap.end())
        {
            std::cerr << "Error: Start node not found in connections." << std::endl;
            return;
        }
        distance[start] = 0;
        pq.push(std::make_pair(0, start));

        while (!pq.empty())
        {
            uint64_t u = pq.top().second;
            pq.pop();

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
    }

    void Navigation::printShortestPath(uint64_t end) const
    {
        if (previous[end] == std::numeric_limits<uint64_t>::max())
        {
            std::cout << "No path from start to end" << std::endl;
            return;
        }

        std::vector<uint64_t> path;
        for (uint64_t at = end; at != std::numeric_limits<uint64_t>::max(); at = previous[at])
        {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());

        for (uint64_t at : path)
        {
            std::cout << at << " ";
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
