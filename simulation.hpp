#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cmath>
#include <climits>
#include <algorithm>

#include "graph.hpp"
#include "signal_controller.hpp"
#include "utils.hpp"

using namespace std;

// -------------------- STRUCTS --------------------

struct Vehicle {
    int id, start, end;
    vector<int> path;
    int currentNodeIndex = 0;
    int waitTime = 0;
    int totalTime = 0;
    bool isEmergency = false;
    bool reached = false;
};

struct Intersection {
    vector<queue<int>> lanes = vector<queue<int>>(4); // N, E, S, W
    int greenLane = 0;
    int timer = 0;
};

// -------------------- SIMULATION CLASS --------------------

class Simulation {
public:
    unordered_map<int, Intersection> intersections;
    vector<Vehicle> vehicles;
    int time = 0;

    // --- Add a new vehicle
    void spawnVehicle(Graph& g, int id, int start, int end, bool isEmergency = false) {
        Vehicle v;
        v.id = id;
        v.start = start;
        v.end = end;
        v.path = g.dijkstra(start, end);
        v.isEmergency = isEmergency;
        vehicles.push_back(v);
    }

    // --- Main simulation loop
    void run(int duration) {
        while (time < duration) {
            updateSignals();
            updateVehicles();
        }
    }

private:
    // --- Update traffic light timers and state
    void updateSignals() {
        for (auto& pair : intersections) {
            Intersection& inter = pair.second;
            inter.timer--;

            if (inter.timer <= 0) {
                inter.greenLane = chooseGreenLaneGreedy(inter.lanes);
                int trafficVol = inter.lanes[inter.greenLane].size();
                inter.timer = max(5, min(20, trafficVol * 2)); // Dynamic timer
            }
        }
    }
    
    // --- Handle vehicle movement and emergency priority
    void updateVehicles() {
        for (auto& v : vehicles) {
            if (v.reached) continue;
            v.totalTime++;

            if (v.currentNodeIndex >= v.path.size() - 1) {
                v.reached = true;
                continue;
            }

            int curr = v.path[v.currentNodeIndex];
            int next = v.path[v.currentNodeIndex + 1];
            Intersection& inter = intersections[curr];

            // EMERGENCY OVERRIDE: Force green light along its path
            if (v.isEmergency) {
                inter.greenLane = getLaneForNextNode(curr, next);
                inter.timer = 10; // Keep it green
            }

            int lane = rand() % 4; // Simplified direction logic

            if (lane == inter.greenLane) {
                v.currentNodeIndex++;
                logMovement(v.id, curr, next, time);
            } else {
                v.waitTime++;
                inter.lanes[lane].push(v.id);
            }
        }

        time++;
    }

    // --- (Helper) Determine which lane corresponds to the next node in the path
    int getLaneForNextNode(int current, int next) {
        // This is a placeholder. A real implementation would use coordinates
        // to determine if 'next' is North, East, South, or West of 'current'.
        return rand() % 4;
    }

public:
    // --- Show performance after simulation
    void report() {
        int totalWait = 0, reachedCount = 0;

        cout << "\n====== SIMULATION SUMMARY ======\n";
        for (auto& v : vehicles) {
            if (v.reached) {
                totalWait += v.waitTime;
                reachedCount++;

                cout << "Vehicle " << v.id << (v.isEmergency ? " [EMERGENCY]" : "")
                     << " reached in " << v.totalTime << "s"
                     << " | Waited: " << v.waitTime << "s\n";
            }
        }

        cout << "\nAverage Wait Time: "
             << (reachedCount > 0 ? (double)totalWait / reachedCount : 0)
             << "s\n";
    }
};