#include "simulation.hpp"
#include <iostream>

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#define KEEPALIVE EMSCRIPTEN_KEEPALIVE
#else
#define KEEPALIVE
#endif

Simulation sim;
Graph g;

extern "C" {

KEEPALIVE void startSimulation() {
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

KEEPALIVE void stopSimulation() {
    std::cout << "Simulation stopped." << std::endl;
}

KEEPALIVE void emergencyOverride() {
    sim.spawnVehicle(g, 99, 0, 3, true);
    std::cout << "Emergency vehicle spawned." << std::endl;
}

} // extern "C"

#ifndef __EMSCRIPTEN__
int main() {
    startSimulation();
    emergencyOverride();
    stopSimulation();
    return 0;
}
#endif
