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

int chooseGreenLaneGreedy(const vector<queue<int>>& lanes) {
    int maxQ = -1, bestLane = 0;
    for (int i = 0; i < 4; ++i) {
        if ((int)lanes[i].size() > maxQ) {
            maxQ = lanes[i].size();
            bestLane = i;
        }
    }
    return bestLane;
}