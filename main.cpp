#include <emscripten/emscripten.h>
#include <string>
#include <sstream>

int lane1Vehicles = 0;
int lane2Vehicles = 0;
int lane3Vehicles = 0;

extern "C" {

// Set lane data from JS
EMSCRIPTEN_KEEPALIVE
void setLaneData(int l1, int l2, int l3) {
    lane1Vehicles = l1;
    lane2Vehicles = l2;
    lane3Vehicles = l3;
}

// Start simulation and return result
EMSCRIPTEN_KEEPALIVE
const char* startSimulation() {
    static std::string result; // persistent to avoid returning pointer to temporary

    // Determine lane with most vehicles
    int maxLane = 1;
    int maxVehicles = lane1Vehicles;

    if (lane2Vehicles > maxVehicles) {
        maxLane = 2;
        maxVehicles = lane2Vehicles;
    }
    if (lane3Vehicles > maxVehicles) {
        maxLane = 3;
        maxVehicles = lane3Vehicles;
    }

    std::ostringstream oss;
    oss << "Simulation Results:\n";
    oss << "Lane 1: " << lane1Vehicles << " vehicles\n";
    oss << "Lane 2: " << lane2Vehicles << " vehicles\n";
    oss << "Lane 3: " << lane3Vehicles << " vehicles\n\n";
    oss << "Recommendation: Give priority to Lane " << maxLane
        << " with " << maxVehicles << " vehicles.";

    result = oss.str();
    return result.c_str();
}

} // extern "C"
