
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <limits>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cmath>

using namespace std;

// Adaptive Traffic System and Emergency Evacuation Support
// Traffic counts are maintained internally.
// Users only enter vehicle details, source, and destination.

struct Location {
    string id;
    string name;
    string type;
};

struct Road {
    int from;
    int to;
    double distance;
    double speedLimit;
    int capacity;
    int currentVehicles;
};

struct Vehicle {
    string type;
    string registration;
    double preferredSpeed;
};

struct RouteResult {
    bool found;
    vector<int> path;
    double totalDistance;
    double estimatedMinutes;
};

vector<Location> locations;
vector<Road> roads;

// --------------------------------------------------
// LOCATION DATA
// --------------------------------------------------

void addLocation(string id, string name, string type) {
    locations.push_back({id, name, type});
}

void initializeLocations() {
    addLocation("J1", "Clock Tower Chowk", "Junction");
    addLocation("J2", "Prince Chowk", "Junction");
    addLocation("J3", "Saharanpur Chowk", "Junction");
    addLocation("J4", "Balliwala Chowk", "Junction");
    addLocation("J5", "Karghi Chowk", "Junction");
    addLocation("J6", "Vidhan Sabha Twin Junction", "Junction");
    addLocation("J7", "ISBT Chowk", "Junction");
    addLocation("J8", "Bindal River Junction", "Junction");
    addLocation("J9", "Jogiwala Chowk", "Junction");
    addLocation("J10", "Araghar Junction", "Junction");
    addLocation("J11", "Ballupur Chowk", "Junction");
    addLocation("J12", "Ashley Hall Junction", "Junction");
    addLocation("J13", "Kishan Nagar Junction", "Junction");
    addLocation("J14", "Sahastradhara Crossing", "Junction");
    addLocation("J15", "Employment Office Crossing", "Junction");

    addLocation("H1", "Doon Hospital", "Hospital");
    addLocation("H2", "Shri Mahant Indiresh Hospital", "Hospital");
    addLocation("H3", "Max Super Speciality Hospital", "Hospital");
    addLocation("H4", "Graphic Era Hospital", "Hospital");
    addLocation("H5", "Synergy Hospital", "Hospital");
    addLocation("H6", "Coronation Hospital", "Hospital");
    addLocation("H7", "Combined Medical Institute", "Hospital");
    addLocation("H8", "Prem Sukh Hospital", "Hospital");
    addLocation("H9", "Uttaranchal Hospital", "Hospital");

    addLocation("P1", "Dalanwala Police Station", "Police Station");
    addLocation("P2", "Nehru Colony Police Station", "Police Station");
    addLocation("P3", "Patel Nagar Police Station", "Police Station");
    addLocation("P4", "Rajpur Police Station", "Police Station");
    addLocation("P5", "Clement Town Police Station", "Police Station");

    addLocation("F1", "Dehradun Fire Station", "Fire Station");
    addLocation("F2", "Doiwala Fire Station", "Fire Station");
    addLocation("F3", "Selaqui Fire Station", "Fire Station");
    addLocation("F4", "Mussoorie Fire Station", "Fire Station");

    addLocation("R1", "Dehradun Central Emergency Rescue Hub", "Rescue Hub");
    addLocation("R2", "Saharanpur Chowk Emergency Rescue Hub", "Rescue Hub");
}

// --------------------------------------------------
// ROAD DATA
// Values are illustrative demo data, not live traffic.
// Roads are bidirectional.
// --------------------------------------------------

int locationIndex(const string& id) {
    for (int i = 0; i < (int)locations.size(); i++) {
        if (locations[i].id == id) return i;
    }
    return -1;
}

void addRoad(string from, string to, double distance,
             double speedLimit, int capacity, int currentVehicles) {
    int a = locationIndex(from);
    int b = locationIndex(to);

    if (a != -1 && b != -1) {
        roads.push_back({a, b, distance, speedLimit,
                         capacity, currentVehicles});
    }
}

void initializeRoads()
{
    roads.clear();

    // ==========================================
    // HORIZONTAL CONNECTIONS (30)
    // ==========================================

    addRoad("J1", "H1", 3, 30, 60, 25);
    addRoad("H1", "P1", 4, 35, 80, 45);
    addRoad("P1", "J2", 5, 40, 100, 65);
    addRoad("J2", "H2", 3, 30, 60, 52);
    addRoad("H2", "F1", 6, 40, 100, 90);
    addRoad("F1", "J3", 4, 35, 80, 30);

    addRoad("H6", "J4", 5, 40, 100, 75);
    addRoad("J4", "R1", 3, 30, 60, 18);
    addRoad("R1", "H3", 4, 35, 80, 70);
    addRoad("H3", "J5", 6, 40, 100, 95);
    addRoad("J5", "P2", 3, 30, 60, 48);
    addRoad("P2", "F2", 5, 40, 100, 55);

    addRoad("P4", "H4", 4, 35, 80, 25);
    addRoad("H4", "J6", 5, 40, 100, 82);
    addRoad("J6", "P3", 3, 30, 60, 58);
    addRoad("P3", "H7", 6, 40, 100, 35);
    addRoad("H7", "R2", 4, 35, 80, 72);
    addRoad("R2", "J7", 5, 40, 100, 105);

    addRoad("F4", "J8", 3, 30, 60, 20);
    addRoad("J8", "H5", 6, 40, 100, 88);
    addRoad("H5", "J9", 4, 35, 80, 42);
    addRoad("J9", "P5", 5, 40, 100, 98);
    addRoad("P5", "H8", 3, 30, 60, 55);
    addRoad("H8", "J10", 7, 40, 100, 35);

    addRoad("J11", "H9", 4, 35, 80, 60);
    addRoad("H9", "J12", 5, 40, 100, 25);
    addRoad("J12", "J13", 6, 40, 100, 20);
    addRoad("J13", "J14", 7, 30, 80, 70);
    addRoad("J14", "J15", 5, 40, 100, 50);
    addRoad("J15", "F3", 4, 35, 80, 90);


    // ==========================================
    // VERTICAL CONNECTIONS (28)
    // ==========================================

    addRoad("J1", "H6", 5, 40, 100, 40);
    addRoad("H6", "P4", 4, 35, 80, 65);
    addRoad("P4", "F4", 6, 40, 100, 85);
    addRoad("F4", "J11", 3, 30, 60, 30);

    addRoad("H1", "J4", 4, 35, 80, 55);
    addRoad("J4", "H4", 5, 40, 100, 95);
    addRoad("H4", "J8", 3, 30, 60, 15);
    addRoad("J8", "H9", 6, 40, 100, 75);

    addRoad("P1", "R1", 3, 30, 60, 35);
    addRoad("R1", "J6", 5, 40, 100, 60);
    addRoad("J6", "H5", 4, 35, 80, 78);
    addRoad("H5", "J12", 7, 40, 100, 110);

    addRoad("J2", "H3", 4, 35, 80, 45);
    addRoad("H3", "P3", 5, 40, 100, 80);
    addRoad("P3", "J9", 3, 30, 60, 50);
    addRoad("J9", "J13", 6, 40, 100, 92);

    addRoad("H2", "J5", 5, 40, 100, 30);
    addRoad("J5", "H7", 4, 35, 80, 62);
    addRoad("H7", "P5", 6, 40, 100, 100);
    addRoad("P5", "J14", 3, 30, 60, 25);

    addRoad("F1", "P2", 4, 35, 80, 70);
    addRoad("P2", "R2", 5, 40, 100, 40);
    addRoad("R2", "H8", 3, 30, 60, 58);
    addRoad("H8", "J15", 6, 40, 100, 85);

    addRoad("J3", "F2", 5, 40, 100, 65);
    addRoad("F2", "J7", 4, 35, 80, 20);
    addRoad("J7", "J10", 7, 40, 100, 95);
    addRoad("J10", "F3", 3, 30, 60, 42);


    // ==========================================
    // DIAGONAL CONNECTIONS (12)
    // ==========================================

    addRoad("J1", "J4", 6, 40, 100, 45);
    addRoad("J4", "J6", 4, 35, 80, 75);
    addRoad("H2", "P2", 5, 40, 100, 55);
    addRoad("H3", "J3", 3, 30, 60, 35);
    addRoad("J5", "R2", 6, 40, 100, 105);
    addRoad("P4", "J8", 4, 35, 80, 50);
    addRoad("J6", "J9", 5, 40, 100, 85);
    addRoad("J6", "H3", 3, 30, 60, 65);
    addRoad("P2", "J7", 7, 40, 100, 95);
    addRoad("J8", "J12", 5, 35, 80, 30);
    addRoad("J9", "J14", 6, 40, 100, 72);
    addRoad("F4", "H9", 4, 30, 60, 55);

    cout << "\nTotal roads initialized: " << roads.size() << endl;
}


// --------------------------------------------------
// VEHICLE VALIDATION
// First two characters must be letters.
// Remaining characters must be letters or digits.
// --------------------------------------------------

bool validRegistration(string registration) {
    if (registration.length() < 3) return false;

    if (!isalpha((unsigned char)registration[0]) ||
        !isalpha((unsigned char)registration[1])) {
        return false;
    }

    for (char c : registration) {
        if (!isalnum((unsigned char)c)) return false;
    }

    return true;
}

bool createVehicle(string type, string registration, Vehicle& vehicle) {
    if (type == "Car") {
        vehicle = {type, registration, 40};
    } else if (type == "Truck") {
        vehicle = {type, registration, 30};
    } else if (type == "Bus") {
        vehicle = {type, registration, 35};
    } else if (type == "Ambulance") {
        vehicle = {type, registration, 50};
    } else if (type == "Fire Truck") {
        vehicle = {type, registration, 40};
    } else if (type == "Police Van") {
        vehicle = {type, registration, 45};
    } else if (type == "Bike") {
        vehicle = {type, registration, 35};
    } else if (type == "Bicycle") {
        vehicle = {type, registration, 15};
    } else {
        return false;
    }

    if (type == "Bicycle") {
        vehicle.registration = "Not required";
        return true;
    }

    if (!validRegistration(registration)) {
        cout << "\nInvalid registration number.\n";
        cout << "Use two letters followed by letters or numbers.\n";
        return false;
    }

    return true;
}

// --------------------------------------------------
// TRAFFIC AND CONGESTION
// The user never enters vehicle counts.
// These are internal demo traffic values.
// --------------------------------------------------

double congestionPercent(const Road& road) {
    if (road.capacity <= 0) return 100.0;
    return 100.0 * road.currentVehicles / road.capacity;
}

double effectiveSpeed(const Road& road, const Vehicle& vehicle) {
    double speed = min(road.speedLimit, vehicle.preferredSpeed);
    double congestion = congestionPercent(road);

    if (congestion >= 100.0) {
        speed *= 0.40;
    } else if (congestion >= 80.0) {
        speed *= 0.60;
    } else if (congestion >= 50.0) {
        speed *= 0.80;
    }

    return max(speed, 5.0);
}

string congestionLabel(const Road& road) {
    double value = congestionPercent(road);

    if (value >= 100.0) return "Full";
    if (value >= 80.0) return "High";
    if (value >= 50.0) return "Moderate";
    return "Low";
}


// --------------------------------------------------
// FASTEST ROUTE USING DIJKSTRA
// Dijkstra minimizes estimated travel time.
// Travel time accounts for vehicle speed and congestion.
// --------------------------------------------------

RouteResult findShortestRoute(int source, int destination,
                              const Vehicle& vehicle) {
    const double INF = numeric_limits<double>::max();
    int n = (int)locations.size();

    // Validate source and destination
    if (source < 0 || source >= n ||
        destination < 0 || destination >= n) {
        return {false, {}, 0, 0};
    }

    // Store minimum travel time instead of distance
    vector<double> minTime(n, INF);
    vector<int> parent(n, -1);

    priority_queue<
        pair<double, int>,
        vector<pair<double, int>>,
        greater<pair<double, int>>
    > pq;

    minTime[source] = 0;
    pq.push({0, source});

    // Dijkstra algorithm: find minimum travel time
    while (!pq.empty()) {
        int current = pq.top().second;
        double currentTime = pq.top().first;
        pq.pop();

        if (currentTime > minTime[current]) continue;

        if (current == destination) break;

        for (const Road& road : roads) {
            int next = -1;

            if (road.from == current)
                next = road.to;
            else if (road.to == current)
                next = road.from;

            if (next == -1) continue;

            // Calculate effective speed considering congestion
            double speed = effectiveSpeed(road, vehicle);

            if (speed <= 0) continue;

            // Calculate travel time for this road in minutes
            double roadTime =
                (road.distance / speed) * 60.0;

            // Add road time to current route time
            double newTime = currentTime + roadTime;

            // Update if a faster route is found
            if (newTime < minTime[next]) {
                minTime[next] = newTime;
                parent[next] = current;
                pq.push({newTime, next});
            }
        }
    }

    // Check whether destination is reachable
    if (minTime[destination] == INF) {
        return {false, {}, 0, 0};
    }

    // Reconstruct the selected route
    vector<int> path;

    for (int at = destination; at != -1; at = parent[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    // Calculate total distance of the fastest route
    double totalDistance = 0;

    for (int i = 0; i + 1 < (int)path.size(); i++) {
        int a = path[i];
        int b = path[i + 1];

        for (const Road& road : roads) {
            bool match =
                (road.from == a && road.to == b) ||
                (road.from == b && road.to == a);

            if (match) {
                totalDistance += road.distance;
                break;
            }
        }
    }

    // Return route, total distance and minimum travel time
    return {true, path, totalDistance, minTime[destination]};
}


// --------------------------------------------------
// DISPLAY FUNCTIONS
// --------------------------------------------------

void displayLocations() {
    cout << "\n========== AVAILABLE LOCATIONS ==========\n";

    for (const Location& location : locations) {
        cout << left << setw(5) << location.id
             << " - " << location.name
             << " [" << location.type << "]\n";
    }
}

void displayRoadStatus() {
    cout << "\n========== ROAD TRAFFIC STATUS ==========\n";
    cout << fixed << setprecision(1);

    for (const Road& road : roads) {
        cout << locations[road.from].id << " <-> "
             << locations[road.to].id
             << " | Distance: " << road.distance << " km"
             << " | Traffic: " << road.currentVehicles
             << "/" << road.capacity
             << " | Congestion: " << congestionPercent(road) << "%"
             << " | Status: " << congestionLabel(road) << "\n";
    }
}

void displayRoute(const RouteResult& result) {
    if (!result.found) {
        cout << "\nNo route is available between those locations.\n";
        return;
    }

    cout << fixed << setprecision(1);
    cout << "\n========== ROUTE RESULT ==========\n";

    cout << "Shortest path: ";
    for (int i = 0; i < (int)result.path.size(); i++) {
        if (i > 0) cout << " -> ";
        cout << locations[result.path[i]].id;
    }

    cout << "\n\nRoute details:\n";
    for (int index : result.path) {
        cout << "  " << locations[index].id
             << " - " << locations[index].name << "\n";
    }

    cout << "\nTotal distance: " << result.totalDistance << " km\n";
    cout << "Estimated travel time: "
         << result.estimatedMinutes << " minutes\n";
}

// --------------------------------------------------
// USER WORKFLOW
// No option for manually entering traffic counts.
// --------------------------------------------------

void registerVehicleAndFindRoute() {
    string type, registration, sourceId, destinationId;

    cout << "\n========== FIND ROUTE ==========\n";
    cout << "Vehicle types: Car, Truck, Bus, Ambulance,\n";
    cout << "               Fire Truck, Police Van, Bike, Bicycle\n";

    cout << "\nEnter vehicle type: ";
    getline(cin >> ws, type);

    cout << "Enter registration number (enter - for Bicycle): ";
    getline(cin, registration);

    Vehicle vehicle;

    if (type == "Bicycle") {
        registration = "";
    } else if (registration == "-") {
        cout << "Registration number is required for this vehicle.\n";
        return;
    }

    if (!createVehicle(type, registration, vehicle)) {
        cout << "Vehicle details are invalid. Please try again.\n";
        return;
    }

    displayLocations();

    cout << "\nEnter source location ID (e.g. J1): ";
    cin >> sourceId;

    cout << "Enter destination location ID (e.g. J15): ";
    cin >> destinationId;

    transform(sourceId.begin(), sourceId.end(), sourceId.begin(),
              [](unsigned char c) { return (char)toupper(c); });

    transform(destinationId.begin(), destinationId.end(),
              destinationId.begin(),
              [](unsigned char c) { return (char)toupper(c); });

    int source = locationIndex(sourceId);
    int destination = locationIndex(destinationId);

    if (source == -1 || destination == -1) {
        cout << "Invalid source or destination ID.\n";
        return;
    }

    if (source == destination) {
        cout << "Source and destination must be different.\n";
        return;
    }

    cout << "\nCalculating route...\n";
    RouteResult result = findShortestRoute(source, destination, vehicle);
    displayRoute(result);
}

// --------------------------------------------------
// MAIN MENU
// --------------------------------------------------
#ifndef SERVER_BUILD
int main() {
    initializeLocations();
    initializeRoads();

    int choice;

    do {
        cout << "\n============================================\n";
        cout << " ADAPTIVE TRAFFIC SYSTEM - DEHRADUN\n";
        cout << " Emergency Evacuation Support\n";
        cout << "============================================\n";
        cout << "1. Display all locations\n";
        cout << "2. Display road traffic status\n";
        cout << "3. Add vehicle and find shortest route\n";
        cout << "0. Exit\n";
        cout << "--------------------------------------------\n";
        cout << "Enter your choice: ";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid menu number.\n";
            continue;
        }

        switch (choice) {
            case 1:
                displayLocations();
                break;

            case 2:
                displayRoadStatus();
                break;

            case 3:
                registerVehicleAndFindRoute();
                break;

            case 0:
                cout << "Exiting the system. Goodbye!\n";
                break;

            default:
                cout << "Invalid choice. Please select 0, 1, 2, or 3.\n";
        }

    } while (choice != 0);

    return 0;
}
#endif