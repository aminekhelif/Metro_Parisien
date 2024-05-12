#pragma once
#ifndef NAVIGATION_HPP
#define NAVIGATION_HPP

#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>
#include <unordered_map>

namespace travel {
    class MetroNetworkParser;  // Forward declaration

    class Navigation {
    public:
        explicit Navigation(MetroNetworkParser &parser);
        void computeShortestPath(const std::string& startName, const std::string& startLine);
        void printShortestPath(const std::string& endName, const std::string& endLine) const;
        uint64_t getShortestDistance(uint64_t end) const;
        std::vector<uint64_t> getShortestPath(uint64_t end) const;

    // private:
        const std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& connections_hashmap;
        std::vector<uint64_t> distance;
        std::vector<uint64_t> previous;
        std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<std::pair<uint64_t, uint64_t>>> pq;
        MetroNetworkParser &metroNetworkParser;
    };
}

#endif // NAVIGATION_HPP
