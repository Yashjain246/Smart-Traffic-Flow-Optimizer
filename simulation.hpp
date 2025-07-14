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
        v.currentNodeIndex = 0;
        v.isEmergency = isEmergency;
        vehicles.push_back(v);
    }

    // --- Update traffic lights based on Greedy logic and emergency detection
    void updateSignals() {
        for (auto& pair : intersections) {
            int id = pair.first;
            auto& inter = pair.second;
            bool emergencyFound = false;

            for (int lane = 0; lane < 4; ++lane) {
                queue<int>& q = inter.lanes[lane];
                queue<int> temp;

                while (!q.empty()) {
                    int vid = q.front(); q.pop();
                    temp.push(vid);

                    auto& v = vehicles[vid];
                    if (v.isEmergency && !v.reached) {
                        inter.greenLane = lane;
                        inter.timer = 0;
                        emergencyFound = true;
                        break;
                    }
                }

                q = temp;
                if (emergencyFound) break;
            }

            if (!emergencyFound && inter.timer % 5 == 0) {
                inter.greenLane = chooseGreenLaneGreedy(inter.lanes);
            }

            inter.timer++;
        }
    }

    // --- Perform one simulation tick
    void step() {
        updateSignals();

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

            int lane = rand() % 4; // 🔁 Simplified direction logic; replace with actual if needed

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
             << (reachedCount ? (double)totalWait / reachedCount : 0.0)
             << "s over " << reachedCount << " vehicles\n";
        cout << "================================\n";
    }
};
