# Adaptive Traffic Signal System with Emergency Evacuation Support

## Brief Description

Adaptive Traffic Signal System with Emergency Evacuation Support is a simulation-based project developed using C++. It aims to improve traffic management by adjusting signal timings according to traffic conditions and supporting emergency vehicles through priority handling and route planning.

## Problem Statement / Objective

Traditional traffic signals often operate with fixed timings, which can increase congestion and vehicle waiting time. During emergencies, ambulances and fire trucks may face delays because of traffic congestion or blocked roads.

The main objectives of this project are:

- Reduce traffic congestion at junctions.
- Adjust traffic signals according to traffic conditions.
- Provide priority to emergency vehicles.
- Identify alternative routes when roads are blocked.
- Apply Data Structures, OOP, and File Handling concepts in a practical simulation.

## Team Members

- Riya Goyal
- Divya Smriti
- Anushka Verma
- Tanishka Soni

## Technologies / Tools Used

| Technology / Tool | Purpose |
|---|---|
| C++ | Core programming language |
| Object-Oriented Programming (OOP) | Modular system design |
| Data Structures | Managing vehicles, roads, and junctions |
| File Handling | Saving and loading project data |
| Git | Version control |
| GitHub | Repository hosting and collaboration |
| VS Code | Development environment |

## Project Setup / Installation Instructions

### Prerequisites

- A C++ compiler such as GCC (g++).
- VS Code or another C++ development environment.
- Git, for cloning the repository.

### Steps to Run

1. Clone the repository:

   ```bash
   git clone <https://github.com/goyalriya207-bot/adaptive-traffic-signal-system>
   ```

2. Open the cloned project folder in VS Code.

3. Navigate to the folder containing the C++ source files:
   ```bash
   cd "PHASE-2 copy"
   ```

4. Compile the project:

   ```bash
   g++ main.cpp Vehicle.cpp Graph.cpp EmergencyResponse.cpp TrafficSignal.cpp FileManager.cpp -o traffic_system
   ```

5. Run the program:

   **Windows PowerShell:**
   ```powershell
   .\traffic_system.exe
   ```

   **Linux/macOS:**
   ```bash
   ./traffic_system
   ```

> Run the program from the same folder where its data files are stored, because file paths are currently relative to the working directory.

## Major Features / Modules

| Module | Features |
|---|---|
| Vehicle Management Module | Vehicle-related classes and vehicle data management |
| Route Management Module | Road and junction graph management and route planning |
| Emergency Response Module | Emergency vehicle response support |
| Traffic Control Module | Traffic signal control and traffic management |
| Data Management Module | Saving and loading vehicle and graph data through file handling |

## Git and GitHub Progress

- Created and maintained a Git repository for the project.
- Used Git to track changes to the C++ source files.
- Committed the project modules to the `adaptive-traffic-signal-system` branch.
- Pushed the branch to GitHub.
- Removed the old remote branch `feature/vehicle-module` after creating and pushing the replacement branch.
- Kept the `main` branch separate from the working branch.

## Current Project Status / Progress

The project has a C++ source-code structure containing separate files for vehicle management, graph and route management, emergency response, traffic signals, file handling, and the main program.

Completed progress so far:

- Implemented and organized the main C++ modules.
- Added file-handling functions to save and load vehicle data.
- Added graph data save/load functionality for junctions, roads, and facilities.
- Built the program using the GCC C++ compiler during development.
- Committed the relevant source files to Git.
- Pushed the working branch to GitHub.
- Set up a separate working branch named `adaptive-traffic-signal-system`.

## Repository Structure

```text
adaptive-traffic-signal-system/
├── PHASE-2/
├── PHASE-2 copy/
│   ├── main.cpp
│   ├── Vehicle.cpp
│   ├── Vehicle.h
│   ├── Graph.cpp
│   ├── Graph.h
│   ├── EmergencyResponse.cpp
│   ├── EmergencyResponse.h
│   ├── TrafficSignal.cpp
│   ├── TrafficSignal.h
│   ├── FileManager.cpp
│   └── FileManager.h
└── README.md
```

*Note: The structure above highlights the known project folders and source files. Additional files may exist in the repository.*

## Future Improvements

- Improve adaptive signal timing based on traffic density.
- Enhance emergency vehicle priority handling.
- Test alternative route selection when roads are blocked.
- Verify data persistence across multiple program runs.
- Test the complete system with different traffic and emergency scenarios.
- Improve documentation and add screenshots of program execution.

## Conclusion

This project demonstrates the application of C++, OOP, Data Structures, and File Handling to a simulated traffic management problem. It brings together vehicle management, road network management, emergency response, and traffic signal control in a modular project structure.
