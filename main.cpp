#include "simulation.hpp"
#include <emscripten.h>

Simulation sim;
Graph g;

extern "C" {

EMSCRIPTEN_KEEPALIVE
void startSimulation() {
    g = Graph();
    g.addEdge(0, 1, 4);
    g.addEdge(1, 2, 3);
    g.addEdge(2, 3, 2);
    g.addEdge(0, 3, 10);

    sim = Simulation();

    sim.spawnVehicle(g, 0, 0, 3);
    sim.spawnVehicle(g, 1, 1, 3, true);
    sim.spawnVehicle(g, 2, 0, 2);
    sim.spawnVehicle(g, 3, 3, 0, false);
    sim.spawnVehicle(g, 4, 1, 2, true);

    for (int t = 0; t < 30; ++t) sim.step();

    sim.report();
}

EMSCRIPTEN_KEEPALIVE
void stopSimulation() {
    printf("Simulation stopped.\n");
}

EMSCRIPTEN_KEEPALIVE
void emergencyOverride() {
    sim.spawnVehicle(g, 99, 0, 3, true);
    printf("Emergency vehicle spawned.\n");
}

}

