#pragma once
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <string>
#include <cmath>
#include <climits>
#include <algorithm>

using namespace std;

// Log vehicle movement
inline void logMovement(int vid, int from, int to, int t) {
    cout << "[T+" << t << "s] Vehicle " << vid << " moved from " << from << " to " << to << "\n";
}

// Generate a random integer in range [a, b]
inline int randInt(int a, int b) {
    return a + rand() % (b - a + 1);
}
