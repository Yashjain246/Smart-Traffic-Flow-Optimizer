#include "simulation.hpp"

int main() {
    Graph g;
    
    // Create city graph
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(0, 3, 10); // Direct long route

    Simulation sim;

    // Spawn normal and emergency vehicles
    sim.spawnVehicle(g, 0, 0, 3);                // normal
    sim.spawnVehicle(g, 1, 1, 3, true);          // emergency
    sim.spawnVehicle(g, 2, 0, 2);                // normal
    sim.spawnVehicle(g, 3, 3, 0, false);         // reverse
    sim.spawnVehicle(g, 4, 1, 2, true);          // emergency

    // Run simulation
    for (int t = 0; t < 30; ++t) {
        cout << "\n[Time " << t << "]\n";
        sim.step();
    }

    sim.report();
    return 0;
}

#include <emscripten.h>

extern "C" {

EMSCRIPTEN_KEEPALIVE
void startSimulation() {
    // Example logic for simulation start
    std::cout << "Simulation started!" << std::endl;
    // Call your traffic optimization or signal handling logic here
}

EMSCRIPTEN_KEEPALIVE
void stopSimulation() {
    std::cout << "Simulation stopped!" << std::endl;
    // Optional: reset states or pause simulation
}

}

