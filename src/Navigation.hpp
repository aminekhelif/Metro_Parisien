#pragma once
#ifndef NAVIGATION_HPP
#define NAVIGATION_HPP

#include <unordered_map>
#include "StationParser.hpp"
#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <algorithm>

namespace travel {
    class Navigation {
        public:
        Navigation(const std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> &connections, StationParser &parser);
        void computeShortestPath(const std::string& start, const std::string& startLine);
        void printShortestPath(const std::string& end, const std::string& endLine) const;
        uint64_t getShortestDistance(uint64_t end) const;
        std::vector<uint64_t> getShortestPath(uint64_t end) const;

        private:
        const std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>> &connections_hashmap;
        std::vector<uint64_t> distance;
        std::vector<uint64_t> previous;
        std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<std::pair<uint64_t, uint64_t>>> pq;
        StationParser &stationParser;
    };
} // namespace travel

#endif // NAVIGATION_HPP
