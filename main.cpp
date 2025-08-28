#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include "simulation.hpp"
#include "graph.hpp"
#include "utils.hpp"

// The main function now correctly parses arguments passed from JavaScript
int main(int argc, char **argv) {
    // Ensure we have the correct number of arguments from the front-end
    if (argc != 5) {
        std::cout << "[ERROR] Invalid number of arguments received from JavaScript." << std::endl;
        std::cout << "Expected 4, but received " << argc - 1 << std::endl;
        return 1;
    }

    // Seed the random number generator
    srand(time(0));

    // Parse arguments from the command line (which are passed by our JS)
    int numVehicles = std::stoi(argv[1]);
    int simDuration = std::stoi(argv[2]);
    int emergencyStart = std::stoi(argv[3]);
    int emergencyEnd = std::stoi(argv[4]);

    std::cout << "Configuration:" << std::endl;
    std::cout << "- " << numVehicles << " vehicles" << std::endl;
    std::cout << "- " << simDuration << "s duration" << std::endl;
    std::cout << "- Emergency Route: " << emergencyStart << " -> " << emergencyEnd << std::endl;
    std::cout << "------------------------------------------" << std::endl;


    // --- Define the Road Network ---
    Graph g;
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 10);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 3);

    Simulation sim;

    // --- Spawn Regular Vehicles ---
    // We spawn one less than the total, because one is reserved for the emergency vehicle.
    for (int i = 0; i < numVehicles - 1; ++i) {
        // Spawn vehicles at random start/end points
        sim.spawnVehicle(g, i, randInt(0, 5), randInt(0, 5), false);
    }

    // --- Spawn the Emergency Vehicle ---
    // The last vehicle ID is used for the emergency one.
    sim.spawnVehicle(g, numVehicles - 1, emergencyStart, emergencyEnd, true);

    // --- Run and Report ---
    sim.run(simDuration);
    sim.report();

    return 0;
}
