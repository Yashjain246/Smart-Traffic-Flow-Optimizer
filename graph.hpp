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

class Graph {
public:
    unordered_map<int, vector<pair<int, int>>> adj;

    void addEdge(int u, int v, int w, bool bidir = true) {
        adj[u].push_back({v, w});
        if (bidir) adj[v].push_back({u, w});
    }

    vector<int> dijkstra(int src, int dest) {
        unordered_map<int, int> dist;
        unordered_map<int, int> parent;
        for (auto& node : adj) dist[node.first] = INT_MAX;
        dist[src] = 0;

        using pii = pair<int, int>;
        priority_queue<pii, vector<pii>, greater<>> pq;
        pq.push({0, src});

        while (!pq.empty()) {
            auto top = pq.top(); pq.pop();
            int d = top.first;
            int node = top.second;

            for (auto& edge : adj[node]) {
                int nbr = edge.first;
                int wt = edge.second;
                if (dist[node] + wt < dist[nbr]) {
                    dist[nbr] = dist[node] + wt;
                    parent[nbr] = node;
                    pq.push({dist[nbr], nbr});
                }
            }
        }

        vector<int> path;
        int curr = dest;
        while (curr != src) {
            path.push_back(curr);
            if (parent.find(curr) == parent.end()) return {}; // No path
            curr = parent[curr];
        }
        path.push_back(src);
        reverse(path.begin(), path.end());
        return path;
    }
};