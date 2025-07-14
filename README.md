# Smart Traffic Flow Optimizer

---

````markdown
# 🚦 Smart Traffic Flow Optimizer

A high-performance **traffic management simulation** project written in **C++**, compiled to **WebAssembly**, and visualized in the browser.  
This project demonstrates the real-time optimization of traffic signal timings based on dynamic vehicle flow, including emergency vehicle prioritization.

> ✨ While the frontend brings visual flair, **this is fundamentally a C++ project** showcasing core algorithms, graph-based routing, and event-driven simulation.

---

## 🧠 Core C++ Logic

### 🔁 Simulation Engine

- The simulation runs on a **discrete time-step model**.
- Each time unit simulates:
  - Vehicle spawning and movement
  - Queue management at intersections
  - Dynamic signal control logic
  - Emergency vehicle override logic

### 🧮 Key Algorithms & Data Structures

| Component                     | Details |
|------------------------------|---------|
| **Graph Representation**     | Adjacency list using `unordered_map<int, vector<pair<int, int>>>` |
| **Shortest Path Routing**    | Custom **Dijkstra's Algorithm** for optimal path computation |
| **Vehicle Management**       | `std::vector<Vehicle>` with status flags (`isEmergency`, `hasArrived`, etc.) |
| **Traffic Signal Control**   | **Priority queue** to manage active green lights based on queue lengths |
| **Simulation Timing**        | Internal `time` counter with condition-based simulation steps |
| **Logging & Reporting**      | Real-time and post-simulation logging of each vehicle's performance |

---

## 🌐 WebAssembly Integration

- Compiled using `emcc` with:
  - `--bind` for C++ class access
  - `EMSCRIPTEN_KEEPALIVE` to expose `startSimulation()`, `stopSimulation()`, and `emergencyOverride()`
- Functions are accessed from JavaScript using `ccall()` and `cwrap()`.

---

## 💻 Frontend (HTML + JS + Canvas + Chart.js + Leaflet)

While the backend logic is C++, the frontend provides an interactive UI with:
- 🚘 Canvas-based vehicle animation
- 📊 Real-time wait time analysis with **Chart.js**
- 🗺️ Live map visualization using **Leaflet.js**
- 📜 Log panel for simulation output

> Note: The frontend is a **visual layer** over the C++ engine and does not contain core simulation logic.

---

## 📦 Build Instructions

> Prerequisite: [Emscripten SDK](https://emscripten.org/docs/getting_started/downloads.html)

```bash
emcc main.cpp -o index.js \
  -s MODULARIZE=1 \
  -s EXPORT_NAME=createModule \
  -s EXPORTED_FUNCTIONS=_startSimulation,_stopSimulation,_emergencyOverride \
  -s EXPORTED_RUNTIME_METHODS=ccall,cwrap \
  -s ALLOW_MEMORY_GROWTH=1 \
  --bind
````

This will generate:

* `index.js` – WebAssembly loader and glue code
* `index.wasm` – compiled C++ simulation engine

---

## 🚀 Deployment

To deploy using GitHub Pages:

1. Push the build files (`index.html`, `index.js`, `index.wasm`, etc.)
2. In GitHub repo → Settings → Pages → Set source to `main` branch (root)
3. Your simulation runs at: `https://<your-username>.github.io/<repo-name>/`

---

## 📚 Learning Outcomes

* 🧠 Applied **graph algorithms** and **C++ STL containers**
* 🛠️ Gained hands-on experience with **WebAssembly compilation** using `emcc`
* 🌍 Integrated C++ logic with interactive JS-based frontend
* 🎨 Visualized performance metrics in real-time

---

## 🤝 Credits

Developed by **Yash Jain**
*B.Tech Engineering Physics | Delhi Technological University*
Team Inferno | Mars Rover & Autonomous Systems

---

## 📌 Project Status

✅ WebAssembly build
✅ Core simulation engine
🛠️ Ongoing UI improvements
🧪 Further testing under real-world routing data

---

```

```
