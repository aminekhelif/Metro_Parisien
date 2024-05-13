
# PARISSUBWAY

## Description

This repository features a route planning algorithm specifically tailored for the Parisian subway system, leveraging the RATP network. It incorporates both static and dynamic heuristics to optimize travel times efficiently. The project showcases the algorithm's effectiveness through an interactive, user-friendly interface, employing a robust and realistic dataset to demonstrate its capabilities in real-world scenarios.

## Features

### Interactive User Experience
- **User Interaction Loop:** The user remains engaged through a continuous interaction loop, allowing for seamless operation of the program. Users can easily exit the program by typing "exit".
- **Simplified Navigation:** Users can initiate searches by simply entering the station name and the line number of the departure and arrival stations to discover the shortest path between them.
- **Decision-Making Power:** After completing a search, users are presented with the option to conduct another search or exit the program, ensuring a user-friendly experience.

### Station Finder Assistant
- **Error Handling and Suggestions:** If a user enters a non-existent station name, the program intelligently suggests the closest matching station. This feature is designed with a straightforward and efficient algorithm, eliminating the need for additional downloads or libraries.

### Robust and Reliable
- **Exception Handling:** The program robustly handles numerous exceptions that may occur during operation. Users are informed about errors clearly and comprehensively, preventing the program from crashing and enhancing reliability.

### Code Efficiency and Quality
- **High-Quality Code Structure:** The code is organized into separate .hpp and .cpp files, ensuring clear separation and manageability.
- **Documentation and Maintenance:** Every part of the code is well-documented with docstrings, making maintenance and future updates easier.
- **Performance:** The program is optimized to avoid memory leaks, segmentation faults, and undefined behavior, ensuring efficient and stable performance.
- **Architecture:** The software architecture is thoughtfully designed to support scalability and manageability.

### Clear and Structured Outputs
- **User-Friendly Displays:** The outputs are clear and well-structured to aid comprehension. Each station is displayed with its name and line number, making it straightforward for users to understand the recommended path and the stations to visit to reach their destination.
- **Organized Interface:** Each section of the output is well-titled and separated, enhancing the readability and user experience.


## Getting Started

### Installing



```bash
# Clone the repository
git clone https://github.com/aminekhelif/Metro_Parisien.git
# Navigate to the project directory
cd Metro_Parisien
# Build the project with flags for C++11 and optimizations (asked by the teacher)
g++ -std=c++11 -o main main.cpp src/MetroNetworkParser.cpp src/Navigation.cpp -Wall -Wextra -Werror -pedantic -pedantic-errors -O3 
```

### Executing program

How to run the program after installation.

```bash
# Run the program
./main
```

## Usage Examples



```bash
╭─- Aminekhelif @MacBook-Pro-de-Amine-Khelif.local ~/Documents/PROJECTS/Projet Metro C++ (main|✚2…1⚑1)
╰─➤  ./main                                                                                                                                                                                                            15:44:29
MetroNetworkParser constructor called
Navigation constructor called

--- New Path Search ---

Type 'exit' at any time to quit the program.
start station name: Villiers
Enter start station line: 2
end station name: Rome
Enter end station line: 2
valide input
endStationId: 2452
startStationId: 2509

 ----------------- 
 Shortest Path from Villiers to Rome: 
 ----------------- 

Villiers, Line :  2 -> Rome, Line :  2
 
 ----------------- 
 Total Distance: 125 units 
 -----------------

Do you want to search for another path? (yes to continue): 
```


## Authors



- [@aminekhelif](https://github.com/aminekhelif)

