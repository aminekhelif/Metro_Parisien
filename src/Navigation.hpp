/**
 * @file Navigation.hpp
 * @brief Contains the declaration of the Navigation class.
 */

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

    /**
     * @class Navigation
     * @brief Represents a navigation system for a metro network.
     */
    class Navigation {
    public:
        /**
         * @brief Constructs a Navigation object.
         * @param parser The MetroNetworkParser object used to parse the metro network data.
         */
        explicit Navigation(MetroNetworkParser &parser);

        /**
         * @brief Computes the shortest path between two metro stations.
         * @param startName The name of the starting station.
         * @param startLine The line of the starting station.
         */
        void computeShortestPath(const std::string& startName, const std::string& startLine);

        /**
         * @brief Prints the shortest path between two metro stations.
         * @param endName The name of the destination station.
         * @param endLine The line of the destination station.
         */
        void printShortestPath(const std::string& endName, const std::string& endLine) const;

        /**
         * @brief Gets the shortest distance between the starting station and a given station.
         * @param end The ID of the destination station.
         * @return The shortest distance between the starting station and the destination station.
         */
        uint64_t getShortestDistance(uint64_t end) const;

        /**
         * @brief Gets the shortest path between the starting station and a given station.
         * @param end The ID of the destination station.
         * @return A vector containing the IDs of the stations in the shortest path.
         */
        std::vector<uint64_t> getShortestPath(uint64_t end) const;

    private:
        const std::unordered_map<uint64_t, std::unordered_map<uint64_t, uint64_t>>& connections_hashmap; /**< The hashmap representing the connections between metro stations. */
        std::vector<uint64_t> distance; /**< The vector storing the shortest distances from the starting station. */
        std::vector<uint64_t> previous; /**< The vector storing the previous station in the shortest path from the starting station. */
        std::priority_queue<std::pair<uint64_t, uint64_t>, std::vector<std::pair<uint64_t, uint64_t>>, std::greater<std::pair<uint64_t, uint64_t>>> pq; /**< The priority queue used for Dijkstra's algorithm. */
        MetroNetworkParser &metroNetworkParser; /**< The MetroNetworkParser object used to parse the metro network data. */
    };
}

#endif // NAVIGATION_HPP
