
---

# 🚦 Smart Traffic Flow Optimizer


# 🔍 About the Project
Smart Traffic Flow Optimizer is a performance-driven traffic simulation engine built entirely in C++, designed to optimize vehicle movement through dynamically controlled traffic signals.

At its core, this project showcases:

⚙️ C++ simulation modeling using discrete time steps

🧠 Graph algorithms like Dijkstra’s for optimal vehicle routing

🚗 Real-time event-driven vehicle handling using STL containers

🚦 Intelligent signal management algorithms with emergency vehicle priority

💡 Object-oriented design patterns and modular C++ architecture

To enable cross-platform interactivity, the engine is compiled into WebAssembly using Emscripten, exposing essential simulation controls (start, stop, emergency override) to a lightweight JavaScript frontend.

This project emphasizes how powerful C++ can be for systems-level, real-time simulations — the visual frontend is just a window into the C++ engine doing the real work underneath.

---

## 🧠 Core C++ Logic

### 🔁 Simulation Engine

The simulation runs on a **discrete time-step model**.
Each time unit simulates:

* Vehicle spawning and movement
* Queue management at intersections
* Dynamic signal control logic
* Emergency vehicle override logic

### 🧮 Key Algorithms & Data Structures

| Component                  | Description                                                              |
| -------------------------- | ------------------------------------------------------------------------ |
| **Graph Representation**   | Adjacency list using `unordered_map<int, vector<pair<int, int>>>`        |
| **Shortest Path Routing**  | Custom **Dijkstra’s Algorithm** for optimal vehicle path                 |
| **Vehicle Management**     | `std::vector<Vehicle>` with flags like `isEmergency`, `hasArrived`, etc. |
| **Traffic Signal Control** | **Priority queue** for signal timings based on queue lengths             |
| **Simulation Timing**      | Time-step loop simulating per-second traffic flow                        |
| **Logging & Reporting**    | Wait time logs and final report generated using `std::cout`              |

---

## 🌐 WebAssembly Integration

This C++ backend is compiled to WebAssembly using **Emscripten**, exposing key simulation functions for the web:

* `startSimulation()`
* `stopSimulation()`
* `emergencyOverride()`

Exposed using:

* `EMSCRIPTEN_KEEPALIVE`
* `ccall()` and `cwrap()` in JavaScript

---

## 💻 Frontend (HTML + JS + Canvas + Leaflet)

While the logic is in C++, the frontend is built using:

* 🎨 **HTML/CSS/JavaScript**
* 🖼️ Canvas for vehicle animations
* 📊 **Chart.js** for visualizing wait times
* 🗺️ **Leaflet.js** for real-time map and route visuals
* 📋 Logging panel for step-by-step simulation output

> The frontend acts as a **visual interface** over the powerful C++ simulation engine.

---

## 📦 Build Instructions

> **Prerequisite:** [Install Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

To compile your C++ code to WebAssembly, run:

```bash
emcc main.cpp -o index.js \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=createModule \
  -s EXPORTED_FUNCTIONS=_startSimulation,_stopSimulation,_emergencyOverride \
  -s EXPORTED_RUNTIME_METHODS=ccall,cwrap \
  -s ALLOW_MEMORY_GROWTH=1 \
  --bind
```

Generated output:

* `index.js` – glue code
* `index.wasm` – compiled simulation logic

---

## 🚀 Deployment (GitHub Pages)

1. Push `index.html`, `index.js`, and `index.wasm` to GitHub.
2. Go to **Repository → Settings → Pages**
3. Set **Source** to `main` branch and root directory.
4. Access your site at:

```
https://<your-username>.github.io/<repo-name>/
```

---

## 📚 Learning Outcomes

* Built a **real-time traffic system** in C++
* Implemented **graph algorithms** (Dijkstra, BFS)
* Used **STL containers**: vectors, maps, queues, priority queues
* Learned **WebAssembly** compilation pipeline
* Integrated simulation engine with modern **web visualization tools**

---

## 🤝 Credits

**Yash Jain**
*B.Tech Engineering Physics, Delhi Technological University*
**Team Inferno – DTU Mars Rover Division**

---

## 📌 Project Status

* ✅ Simulation engine in C++ complete
* ✅ Frontend visualizer connected
* 🔄 Ongoing improvements to animation & data visualization
* 🔜 Planned: Real-world map route optimization + external sensor data feed

---


