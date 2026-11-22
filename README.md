# Adaptive Traffic System With Emergency Evacuation Support

## Brief Description

Adaptive Traffic System With Emergency Evacuation Support is a project developed using C++ and web technologies. It demonstrates vehicle management, route calculation, traffic-condition visualization and emergency response support.

The project consists of two standalone C++ programs, `addvehicle.cpp` and `addemergency.cpp`, along with a web-based frontend developed using HTML, CSS and JavaScript.

The vehicle management program handles vehicle-related input and calculates suitable routes using a graph-based road network and Dijkstra's algorithm. The emergency management program handles emergency requests, checks available resources and selects suitable response routes.

The frontend provides an interactive interface for adding vehicles, viewing routes, observing traffic conditions and submitting emergency requests. It uses predefined JavaScript data to demonstrate these features.

**Note:** The C++ programs and frontend operate independently in the final project. There is no direct connection through a backend or database.

---

## Problem Statement / Objectives

Traffic congestion and delays can affect the movement of vehicles, especially during emergency situations. Emergency vehicles such as ambulances and fire trucks require suitable routes and timely resource allocation.

The objectives of this project are:

- Manage vehicle-related information.
- Represent the road network using graphs.
- Calculate suitable routes using Dijkstra's algorithm.
- Handle emergency requests.
- Check the availability of emergency response resources.
- Select suitable routes for emergency response.
- Display traffic conditions and routes through a web-based interface.
- Apply programming and Data Structures and Algorithms concepts to a practical problem.

---

## Team Members

- Riya Goyal
- Divya Smriti
- Anushka Verma
- Tanishka Soni

**Team Name:** Four Bytes

---

## Technologies / Tools Used

| Technology / Tool | Purpose |
|---|---|
| C++ | Vehicle and emergency management programs |
| Object-Oriented Programming | Program structure and implementation |
| Data Structures and Algorithms | Graph representation and route calculation |
| Dijkstra's Algorithm | Shortest-route calculation |
| HTML | Frontend structure |
| CSS | Frontend styling and layout |
| JavaScript | Frontend functionality and simulation |
| Git | Version control |
| GitHub | Repository management |
| Visual Studio Code | Development environment |
| g++ Compiler | Compiling and running C++ programs |
| Live Server | Running the frontend locally |

---

## Project Setup / Installation Instructions

### Requirements

1. Visual Studio Code or another code editor.
2. A C++ compiler such as g++.
3. A modern web browser.
4. Live Server extension in VS Code (optional).

### Step 1: Clone the Repository

```bash
git clone <https://github.com/goyalriya207-bot/adaptive-traffic-signal-system.git>
cd <PBL_AdaptiveTrafficSystem>
```

### Step 2: Open the Project

Open the project folder in Visual Studio Code.

The final project contains these five files:

```text
Adaptive-Traffic-System/
│
├── addvehicle.cpp
├── addemergency.cpp
│
├── index.html
├── style.css
└── script.js
```

### Step 3: Run the Frontend

1. Open `index.html` in VS Code.
2. Right-click inside the editor.
3. Select **Open with Live Server**.
4. The frontend will open in your browser.

Alternatively, open `index.html` directly in a browser.

### Step 4: Compile and Run the C++ Programs

**Vehicle Management:**

Compile:

```bash
g++ addvehicle.cpp -o addvehicle
```

Run on Windows:

```bash
addvehicle.exe
```

Run on Linux or macOS:

```bash
./addvehicle
```

**Emergency Management:**

Compile:

```bash
g++ addemergency.cpp -o addemergency
```

Run on Windows:

```bash
addemergency.exe
```

Run on Linux or macOS:

```bash
./addemergency
```

Both C++ programs run independently.

---

## Major Features / Modules

| Component | Features |
|---|---|
| Vehicle Management (`addvehicle.cpp`) | Vehicle-related input, graph-based road network and route calculation using Dijkstra's algorithm |
| Emergency Management (`addemergency.cpp`) | Emergency request handling, resource availability checking, resource allocation and response route selection |
| Frontend (`index.html`) | Structure and content of the web application |
| Frontend Styling (`style.css`) | Interface appearance, layout and responsive styling |
| Frontend Functionality (`script.js`) | Vehicle input, traffic simulation, route visualization and emergency response demonstrations |

---

## Working of the Project

### Vehicle Management Workflow

1. Vehicle details are entered.
2. The road network is represented using connected locations and roads.
3. Dijkstra's algorithm is used to calculate a suitable route.
4. Route-related information is displayed.

### Emergency Management Workflow

1. An emergency request is entered.
2. Emergency requirements are identified.
3. Available emergency resources are checked.
4. Suitable resources are selected.
5. A suitable response route is identified.

### Frontend Workflow

1. The user opens the web application.
2. Vehicle details can be entered.
3. Traffic conditions and routes can be viewed.
4. Emergency requests can be submitted.
5. Emergency response and resource information are displayed.

The frontend demonstrates these operations using its own predefined JavaScript data.

---

## Testing

The following functionalities can be tested separately:

- Vehicle input and registration.
- Route calculation using Dijkstra's algorithm.
- Display of traffic conditions.
- Frontend vehicle functionality.
- Emergency request handling.
- Emergency resource allocation.
- Emergency route display.
- Frontend layout and responsiveness.

Each functionality should be marked as successfully tested only after verifying it with the final project files.

---

## Current Project Status / Progress

- Vehicle management program developed in C++.
- Emergency management program developed in C++.
- Graph-based route calculation implemented.
- Dijkstra's algorithm used for route finding.
- Emergency resource allocation functionality developed.
- Web-based frontend developed using HTML, CSS and JavaScript.
- Vehicle, traffic, route and emergency demonstrations implemented in the frontend.
- Testing and debugging carried out on the individual components.

### Current Limitations

- The C++ programs operate separately.
- The frontend uses predefined JavaScript data.
- The frontend is not connected to the C++ programs.
- No backend API or MySQL database is integrated.
- Traffic and emergency information displayed by the frontend is demonstration data, not live real-world data.

---

## Future Improvements

- Connect the frontend with the C++ programs through a backend.
- Integrate a database to store vehicle, road and emergency information.
- Use live traffic information instead of predefined demonstration data.
- Improve route calculation and emergency response features.
- Add further testing and validation after integration.

---

## Conclusion

The Adaptive Traffic Signal System With Emergency Evacuation Support demonstrates the application of programming and Data Structures and Algorithms to traffic management and emergency response.

Through this project, we gained practical experience in C++ programming, graph representation, Dijkstra's algorithm, resource allocation, frontend development, testing and debugging.

The final project consists of two standalone C++ programs and a web-based frontend, demonstrating different aspects of vehicle management, traffic visualization and emergency response.
