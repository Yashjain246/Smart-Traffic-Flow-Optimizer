#include <iostream>
#include <vector>
#include <string>
#include "simulation.hpp"
#include "graph.hpp"
#include "utils.hpp"

using namespace std;

int main() {
    srand(time(0));

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

    // Spawn regular vehicles
    for (int i = 0; i < 10; ++i) {
        sim.spawnVehicle(g, i, randInt(0, 5), randInt(0, 5));
    }

    // Spawn one emergency vehicle
    sim.spawnVehicle(g, 10, 0, 5, true);

    sim.run(200); // Run for 200 time steps
    sim.report();

    return 0;
}