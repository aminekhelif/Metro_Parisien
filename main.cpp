/**
 * @file main.cpp
 * @brief This file contains the main function and related functions for the Metro Network program.
 */

#include "src/MetroNetworkParser.hpp"
#include "src/Navigation.hpp"

/**
 * @brief Function to normalize the input string by converting it to lowercase and removing punctuation.
 * @param input The input string to be normalized.
 * @return The normalized string.
 */
std::string normalize(const std::string &input)
{
    std::string result;
    result.reserve(input.size());
    for (char c : input)
    {
        if (!std::ispunct(static_cast<unsigned char>(c)))
        {
            result.push_back(std::tolower(static_cast<unsigned char>(c)));
        }
    }
    return result;
}

/**
 * @brief Function to get user input for station name and line, and validate it against the database.
 * @param prompt The prompt message to display to the user.
 * @param stationName Reference to a string variable to store the entered station name.
 * @param line Reference to a string variable to store the entered line.
 * @param metroNetworkParser The MetroNetworkParser object used to validate the input against the database.
 * @return True if the station and line are valid, false if the user chooses to exit.
 */
bool updated_getUserInput(const std::string &prompt, std::string &stationName, std::string &line, const travel::MetroNetworkParser &metroNetworkParser)
{
    // explain exit option
    while (true)
    {
        std::cout << prompt << " station name: ";
        getline(std::cin, stationName);
        if (stationName == "exit")
            return false;

        std::cout << "Enter " << prompt << " station line: ";
        getline(std::cin, line);
        if (line == "exit")
            return false;

        // Validate the provided station and line against the database
        try
        {            
            uint64_t stationId = metroNetworkParser.get_station_id_by_name_and_line(stationName, line);
            if (stationId != std::numeric_limits<uint64_t>::max())
            {
                return true; // Station and line are valid
            }
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
            // Provide suggestions if no exact match is found
            // adding line separator
            std::cout << "-------------------" << std::endl;
            std::cout << "No exact match found. Here are some suggestions based on your input:" << std::endl;
            std::cout << "-------------------" << std::endl;
            auto suggestions = metroNetworkParser.searchStations(normalize(stationName));
            for (const auto &suggestion : suggestions)
            {
                std::cout << suggestion.first << " (Line " << suggestion.second << ")" << std::endl;
            }
            std::cout << "-------------------" << std::endl;
            std::cout << "Please try again.\n";
            std::cout << "-------------------" << std::endl;

        }   
    }
}

/**
 * @brief The main function of the Metro Network program.
 * @return 0 on successful execution.
 */
int main()
{
    travel::MetroNetworkParser metroNetworkParser;

    std::string startStationName, startStationLine, endStationName, endStationLine;
    while (true)
    {
        std::cout << "\n--- New Path Search ---\n";
        std::cout << std::endl
                  << "Type 'exit' at any time to quit the program." << std::endl;
        if (!updated_getUserInput("start", startStationName, startStationLine, metroNetworkParser) ||
            !updated_getUserInput("end", endStationName, endStationLine, metroNetworkParser))
        {
            std::cout << "Exiting program.\n";
            break;
        }

        std::cout << "valide input\n";

        try
        {
            travel::Navigation *navigation = metroNetworkParser.getNavigation();
            uint64_t endStationId = metroNetworkParser.get_station_id_by_name_and_line(endStationName, endStationLine);
            std::cout << "endStationId: " << endStationId << std::endl;
            uint64_t startStationId = metroNetworkParser.get_station_id_by_name_and_line(startStationName, startStationLine);
            std::cout << "startStationId: " << startStationId << std::endl;

            // compute_and_display_travel
            std::cout << "\n ----------------- \n Shortest Path from " 
                    << startStationName << " to " << endStationName 
                    << ": \n ----------------- \n"<< std::endl;

            auto path = metroNetworkParser.compute_and_display_travel(startStationId, endStationId);

            std::cout << " \n ----------------- \n Total Distance: " 
                    << navigation->getShortestDistance(endStationId) 
                    << " units \n -----------------\n"<< std::endl;

            //   Prompt for another search
            std::cout << "Do you want to search for another path? (yes to continue): ";
            std::string answer;
            getline(std::cin, answer);
            if (answer != "yes")
            {
                std::cout << "Exiting program.\n";
                break;
            }
        }
        catch (const std::exception &e){
            std::cerr << "Error: " << e.what() << std::endl;
        }    

    }
    return 0;
}
