#include "Graph.h"
#include <limits>
#include <iomanip>
#include <cstdlib>
#include "FileManager.h"
using namespace std;

// Helper functions used by the Graph functions are kept here.
namespace {
const int MAX_JUNCTIONS = 15;
const int MAX_ROADS = 105;
const int MAX_FACILITIES = 7;
Graph roads[MAX_ROADS];
Junction junctions[MAX_JUNCTIONS];
Facility facilities[MAX_FACILITIES];

int roadCount = 0;
int junctionCount = 0;
int facilityCount = 0;
const double INF = numeric_limits<double>::max() / 4.0;

// Find a junction in the array. Return -1 if it is not present.
int findJunction(Junction junctions[], int count, const string &id) {
    for (int i = 0; i < count; i++) {
        if (junctions[i].junctionID == id) return i;
    }
    return -1;
}

// Check whether an ID is already used by a facility.
bool facilityIDExists(Facility facilities[], int count, const string &id) {
    for (int i = 0; i < count; i++) {
        if (facilities[i].facilityID == id) return true;
    }
    return false;
}

// Ask for a valid traffic level.
string readTrafficLevel() {
    int choice;
    do {
        cout << "Traffic level (1 Low, 2 Moderate, 3 High): ";
        choice = readInt();
        if (choice < 1 || choice > 3) cout << "Please enter 1, 2, or 3.\n";
    } while (choice < 1 || choice > 3);

    if (choice == 1) return "Low";
    if (choice == 2) return "Moderate";
    return "High";
}

// Ask for a valid junction type.
string readJunctionType() {
    int choice;
    do {
        cout << "Junction type (1 Normal, 2 Hospital, 3 Police Station): ";
        choice = readInt();
        if (choice < 1 || choice > 3) cout << "Please enter 1, 2, or 3.\n";
    } while (choice < 1 || choice > 3);

    if (choice == 1) return "Normal";
    if (choice == 2) return "Hospital";
    return "Police Station";
}

// Convert traffic into a small extra cost for suitable-route calculations.
double trafficCost(const string &level) {
    if (level == "Moderate") return 3.0;
    if (level == "High") return 8.0;
    return 0.0;
}

// Dijkstra's algorithm finds a low-cost route. Suitable mode also considers traffic.
// skipRoad lets the alternative-route function ignore one road temporarily.
bool calculateRoute(Graph roads[], int roadCount, Junction junctions[],
                    int junctionCount, int start, int finish, bool suitable,
                    int skipRoad, int path[], int &pathLength, double &totalDistance) {
    double cost[MAX_JUNCTIONS];
    double distance[MAX_JUNCTIONS];
    bool visited[MAX_JUNCTIONS] = {};
    int previous[MAX_JUNCTIONS];

    for (int i = 0; i < junctionCount; i++) {
        cost[i] = INF;
        distance[i] = INF;
        previous[i] = -1;
    }
    cost[start] = 0;
    distance[start] = 0;

    // Choose the unvisited junction with the lowest cost.
    for (int round = 0; round < junctionCount; round++) {
        int current = -1;
        for (int i = 0; i < junctionCount; i++) {
            if (!visited[i] && (current == -1 || cost[i] < cost[current])) {
                current = i;
            }
        }

        if (current == -1 || cost[current] == INF) break;
        if (current == finish) break;
        visited[current] = true;

        // Check connected roads. Ignore blocked roads and respect one-way direction.
        for (int r = 0; r < roadCount; r++) {
            if (r == skipRoad || roads[r].isBlocked) continue;

            int next = -1;
            if (roads[r].junction1 == junctions[current].junctionID) {
                next = findJunction(junctions, junctionCount, roads[r].junction2);
            } else if (!roads[r].isOneWay &&
                       roads[r].junction2 == junctions[current].junctionID) {
                next = findJunction(junctions, junctionCount, roads[r].junction1);
            }

            if (next == -1 || visited[next]) continue;

            double extra = roads[r].distance;
            if (suitable) extra += trafficCost(roads[r].trafficLevel);

            if (cost[current] + extra < cost[next]) {
                cost[next] = cost[current] + extra;
                distance[next] = distance[current] + roads[r].distance;
                previous[next] = current;
            }
        }
    }

    if (cost[finish] == INF) return false;

    // Build the route backwards from the destination, then reverse it.
    int reversePath[MAX_JUNCTIONS];
    int length = 0;
    for (int at = finish; at != -1; at = previous[at]) {
        reversePath[length++] = at;
        if (at == start) break;
    }

    if (reversePath[length - 1] != start) return false;

    pathLength = 0;
    for (int i = length - 1; i >= 0; i--) path[pathLength++] = reversePath[i];
    totalDistance = distance[finish];
    return true;
}

void printPath(int path[], int length, Junction junctions[]) {
    for (int i = 0; i < length; i++) {
        cout << junctions[path[i]].junctionID;
        if (i < length - 1) cout << " -> ";
    }
    cout << '\n';
}

// Add a hospital or police station after checking its junction.
void addFacility(Facility facilities[], int &facilityCount,
                 Junction junctions[], int junctionCount, bool hospital) {
    if (facilityCount >= MAX_FACILITIES) {
        cout << "Facility limit reached.\n";
        return;
    }
    if (junctionCount == 0) {
        cout << "Add a junction before adding a facility.\n";
        return;
    }

    Facility item;
    cout << "Enter facility ID (" << (hospital ? "H1-H4" : "P1-P3") << "): ";
    cin >> item.facilityID;

    if (facilityIDExists(facilities, facilityCount, item.facilityID)) {
        cout << "That facility ID is already used.\n";
        return;
    }

    if (hospital) {
        if (item.facilityID != "H1" && item.facilityID != "H2" &&
            item.facilityID != "H3" && item.facilityID != "H4") {
            cout << "Use an ID from H1 to H4.\n";
            return;
        }
        cout << "Hospital type (1 Small, 2 Big): ";
        int type;
        type = readInt();
        while (type != 1 && type != 2) {
            cout << "Enter 1 for Small or 2 for Big: ";
            type = readInt();
        }
        item.facilityType = (type == 1) ? "Small Hospital" : "Big Hospital";
    } else {
        if (item.facilityID != "P1" && item.facilityID != "P2" &&
            item.facilityID != "P3") {
            cout << "Use an ID from P1 to P3.\n";
            return;
        }
        item.facilityType = "Police Station";
    }

    cout << "Enter facility name: ";
    getline(cin >> ws, item.facilityName);
    cout << "Enter the junction ID where it is located: ";
    cin >> item.junctionID;

    if (findJunction(junctions, junctionCount, item.junctionID) == -1) {
        cout << "That junction has not been added.\n";
        return;
    }

    facilities[facilityCount++] = item;
    cout << "Facility added successfully.\n";
}
}

int readInt() {
    int value;
    while (!(cin >> value)) {
        if (cin.eof()) exit(0);               // input ended, stop cleanly
        cin.clear();                           // clear the error state
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // throw away bad text
        cout << "Invalid input. Enter a number: ";
    }
    return value;
}

double readDouble() {
    double value;
    while (!(cin >> value)) {
        if (cin.eof()) exit(0);
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. Enter a number: ";
    }
    return value;
}

Graph::Graph() {
    roadID = 0;
    junction1 = "";
    junction2 = "";
    road_Name = "";
    distance = 0;
    road_type = "Normal";
    isBlocked = false;
    isOneWay = false;
    trafficLevel = "Low";
}

bool Graph::isDuplicate_RoadID(Graph roads[], int roadCount, int id) {
    for (int i = 0; i < roadCount; i++) {
        if (roads[i].roadID == id) return true;
    }
    return false;
}

// Add a junction after checking its ID and collecting its details.
void Graph::addJunction(Junction junctions[], int &junctionCount) {
    if (junctionCount >= MAX_JUNCTIONS) {
        cout << "All 15 junctions have already been added.\n";
        return;
    }

    Junction item;
    cout << "Enter junction ID (J1-J15): ";
    cin >> item.junctionID;

    if (item.junctionID.size() < 2 || item.junctionID[0] != 'J') {
        cout << "Invalid junction ID.\n";
        return;
    }
    for (int i = 1; i < (int)item.junctionID.size(); i++) {
        if (item.junctionID[i] < '0' || item.junctionID[i] > '9') {
            cout << "Invalid junction ID.\n";
            return;
        }
    }
    // At most 2 digits and no leading zero, so "J01" is not accepted.
    if (item.junctionID.size() > 3 || item.junctionID[1] == '0') {
        cout << "Junction ID must be between J1 and J15.\n";
        return;
    }
    int number = item.junctionID[1] - '0';
    if (item.junctionID.size() == 3)
        number = number * 10 + (item.junctionID[2] - '0');
    if (number < 1 || number > 15 ||
        findJunction(junctions, junctionCount, item.junctionID) != -1) {
        cout << "Junction ID must be unused and between J1 and J15.\n";
        return;
    }

    cout << "Enter junction name: ";
    getline(cin >> ws, item.junctionName);
    item.junctionType = readJunctionType();

    junctions[junctionCount++] = item;
    cout << "Junction added successfully.\n";
}

// Find a junction and update its name, type, and importance.
void Graph::updateJunction(Junction junctions[], int junctionCount) {
    if (junctionCount == 0) {
        cout << "No junctions have been added.\n";
        return;
    }

    string id;
    cout << "Enter junction ID to update: ";
    cin >> id;
    int index = findJunction(junctions, junctionCount, id);
    if (index == -1) {
        cout << "Junction not found.\n";
        return;
    }

    cout << "Current name: " << junctions[index].junctionName << '\n';
    cout << "Enter new name: ";
    getline(cin >> ws, junctions[index].junctionName);
    junctions[index].junctionType = readJunctionType();
    cout << "Junction updated successfully.\n";
}

// Show junction details and the roads connected to each junction.
void Graph::displayJunctions(Junction junctions[], int junctionCount,
                             Graph roads[], int roadCount) {
    if (junctionCount == 0) {
        cout << "No junctions to display.\n";
        return;
    }

    for (int i = 0; i < junctionCount; i++) {
        cout << "\nJunction: " << junctions[i].junctionID << '\n';
        cout << "Name: " << junctions[i].junctionName << '\n';
        cout << "Type: " << junctions[i].junctionType << '\n';
        cout << "Connected roads: ";

        bool found = false;
        for (int r = 0; r < roadCount; r++) {
            if (roads[r].junction1 == junctions[i].junctionID ||
                roads[r].junction2 == junctions[i].junctionID) {
                if (found) cout << ", ";
                cout << roads[r].road_Name << " (" << roads[r].junction1
                     << " - " << roads[r].junction2 << ")";
                if (roads[r].isBlocked) cout << " [Blocked]";
                found = true;
            }
        }
        if (!found) cout << "None";
        cout << '\n';
    }
}

// Add a road between two junctions that already exist.
void Graph::inputRoad(Graph roads[], int &roadCount,
                      Junction junctions[], int junctionCount) {
    if (roadCount >= MAX_ROADS) {
        cout << "Road limit reached.\n";
        return;
    }
    if (junctionCount < 2) {
        cout << "Add at least two junctions before adding a road.\n";
        return;
    }

    Graph item;
    cout << "Enter road ID: ";
    item.roadID = readInt();
    if (item.roadID <= 0 || isDuplicate_RoadID(roads, roadCount, item.roadID)) {
        cout << "Road ID must be positive and unique.\n";
        return;
    }

    cout << "Enter starting junction ID: ";
    cin >> item.junction1;
    cout << "Enter ending junction ID: ";
    cin >> item.junction2;

    if (item.junction1 == item.junction2 ||
        findJunction(junctions, junctionCount, item.junction1) == -1 ||
        findJunction(junctions, junctionCount, item.junction2) == -1) {
        cout << "Choose two different junctions that already exist.\n";
        return;
    }

    // Do not add the same connection twice, even if endpoints are reversed.
    for (int i = 0; i < roadCount; i++) {
        bool sameWay = roads[i].junction1 == item.junction1 &&
                       roads[i].junction2 == item.junction2;
        bool reverseWay = roads[i].junction1 == item.junction2 &&
                          roads[i].junction2 == item.junction1;
        if (sameWay || reverseWay) {
            cout << "A road between these junctions already exists.\n";
            return;
        }
    }

    cout << "Enter road name: ";
    getline(cin >> ws, item.road_Name);
    cout << "Enter distance in km: ";
    item.distance = readDouble();
    while (item.distance <= 0) {
        cout << "Distance must be greater than zero: ";
        item.distance = readDouble();
    }

    // Road type is separate from blocked status and direction.
    item.road_type = "Normal";
    int oneWay, blocked;
    cout << "Is this road one-way? (1 Yes, 0 No): ";
    oneWay = readInt();
    while (oneWay != 0 && oneWay != 1) {
        cout << "Enter 1 or 0: ";
        oneWay = readInt();
    }
    item.isOneWay = (oneWay == 1);

    cout << "Is this road blocked? (1 Yes, 0 No): ";
    blocked = readInt();
    while (blocked != 0 && blocked != 1) {
        cout << "Enter 1 or 0: ";
        blocked = readInt();
    }
    item.isBlocked = (blocked == 1);
    item.trafficLevel = readTrafficLevel();

    roads[roadCount++] = item;
    cout << "Road added successfully.\n";
}

void Graph::displayRoad() {
    cout << "\nRoad ID: " << roadID << '\n';
    cout << "Road name: " << road_Name << '\n';
    cout << "Connection: " << junction1;
    if (isBlocked) cout << " -X- ";
    else if (isOneWay) cout << " --> ";
    else cout << " <--> ";
    cout << junction2 << '\n';
    cout << "Distance: " << distance << " km\n";
    cout << "Direction: " << (isOneWay ? "One-way" : "Two-way") << '\n';
    cout << "Status: " << (isBlocked ? "Blocked" : "Open") << '\n';
    cout << "Traffic: " << trafficLevel << '\n';
}

void Graph::displayAllRoads(Graph roads[], int roadCount) {
    if (roadCount == 0) {
        cout << "No roads to display.\n";
        return;
    }
    for (int i = 0; i < roadCount; i++) {
        cout << "\nRoad " << i + 1 << ":\n";
        roads[i].displayRoad();
    }
}

void Graph::searchRoad(Graph roads[], int roadCount) {
    int id;
    cout << "Enter road ID to search: ";
    id = readInt();
    for (int i = 0; i < roadCount; i++) {
        if (roads[i].roadID == id) {
            roads[i].displayRoad();
            return;
        }
    }
    cout << "Road not found.\n";
}

// Update the details of a road selected by its ID.
void Graph::updateRoad(Graph roads[], int roadCount,
                       Junction junctions[], int junctionCount) {
    if (roadCount == 0) {
        cout << "No roads to update.\n";
        return;
    }

    int id;
    cout << "Enter road ID to update: ";
    id = readInt();
    int index = -1;
    for (int i = 0; i < roadCount; i++) {
        if (roads[i].roadID == id) index = i;
    }
    if (index == -1) {
        cout << "Road not found.\n";
        return;
    }

    string first, second;
    cout << "Enter new starting junction: ";
    cin >> first;
    cout << "Enter new ending junction: ";
    cin >> second;
    if (first == second || findJunction(junctions, junctionCount, first) == -1 ||
        findJunction(junctions, junctionCount, second) == -1) {
        cout << "Invalid junctions. Road was not changed.\n";
        return;
    }
    for (int i = 0; i < roadCount; i++) {
        if (i == index) continue;
        if ((roads[i].junction1 == first && roads[i].junction2 == second) ||
            (roads[i].junction1 == second && roads[i].junction2 == first)) {
            cout << "A road between these junctions already exists. Road was not changed.\n";
            return;
        }
    }

    cout << "Enter new road name: ";
    string name;
    getline(cin >> ws, name);
    double km;
    cout << "Enter new distance in km: ";
    km = readDouble();
    if (km <= 0) {
        cout << "Distance must be greater than zero. Road was not changed.\n";
        return;
    }

    int oneWay;
    cout << "One-way road? (1 Yes, 0 No): ";
    oneWay = readInt();
    while (oneWay != 0 && oneWay != 1) {
        cout << "Enter 1 or 0: ";
        oneWay = readInt();
    }

    // Change the road only after its new details pass validation.
    roads[index].junction1 = first;
    roads[index].junction2 = second;
    roads[index].road_Name = name;
    roads[index].distance = km;
    roads[index].isOneWay = (oneWay == 1);
    roads[index].trafficLevel = readTrafficLevel();

    int blocked;
    cout << "Is the road blocked? (1 Yes, 0 No): ";
    blocked = readInt();
    while (blocked != 0 && blocked != 1) {
        cout << "Enter 1 or 0: ";
        blocked = readInt();
    }
    roads[index].isBlocked = (blocked == 1);
    cout << "Road updated successfully.\n";
}

// Update only whether a road is blocked and its traffic level.
void Graph::updateRoadConditions(Graph roads[], int roadCount) {
    if (roadCount == 0) {
        cout << "No roads available.\n";
        return;
    }
    int id;
    cout << "Enter road ID: ";
    id = readInt();

    for (int i = 0; i < roadCount; i++) {
        if (roads[i].roadID == id) {
            int blocked;
            cout << "Is it blocked? (1 Yes, 0 No): ";
            blocked = readInt();
            while (blocked != 0 && blocked != 1) {
                cout << "Enter 1 or 0: ";
                blocked = readInt();
            }
            roads[i].isBlocked = (blocked == 1);
            roads[i].trafficLevel = readTrafficLevel();
            cout << "Road conditions updated.\n";
            return;
        }
    }
    cout << "Road not found.\n";
}

// Remove a road by ID after asking the user to confirm.
void Graph::removeRoad(Graph roads[], int &roadCount) {
    if (roadCount == 0) {
        cout << "No roads to remove.\n";
        return;
    }
    int id, index = -1;
    cout << "Enter road ID to remove: ";
    id = readInt();
    for (int i = 0; i < roadCount; i++) {
        if (roads[i].roadID == id) index = i;
    }
    if (index == -1) {
        cout << "Road not found.\n";
        return;
    }

    char confirm;
    cout << "Remove this road? (Y/N): ";
    cin >> confirm;
    if (confirm != 'Y' && confirm != 'y') {
        cout << "Removal cancelled.\n";
        return;
    }
    for (int i = index; i < roadCount - 1; i++) roads[i] = roads[i + 1];
    roadCount--;
    cout << "Road removed.\n";
}

void Graph::addHospital(Facility facilities[], int &facilityCount,
                        Junction junctions[], int junctionCount) {
    addFacility(facilities, facilityCount, junctions, junctionCount, true);
}

void Graph::addPoliceStation(Facility facilities[], int &facilityCount,
                             Junction junctions[], int junctionCount) {
    addFacility(facilities, facilityCount, junctions, junctionCount, false);
}

void Graph::displayFacilities(Facility facilities[], int facilityCount) {
    if (facilityCount == 0) {
        cout << "No facilities have been added.\n";
        return;
    }
    for (int i = 0; i < facilityCount; i++) {
        cout << "\n" << facilities[i].facilityID << " - "
             << facilities[i].facilityName << '\n';
        cout << "Type: " << facilities[i].facilityType << '\n';
        cout << "Junction: " << facilities[i].junctionID << '\n';
    }
}

// Find the shortest-distance route or a route that also considers traffic.
void Graph::findShortestRoute(Graph roads[], int roadCount,
                              Junction junctions[], int junctionCount) {
    if (junctionCount < 2) {
        cout << "Add at least two junctions first.\n";
        return;
    }
    string from, to;
    int mode;
    cout << "Starting junction ID: ";
    cin >> from;
    cout << "Destination junction ID: ";
    cin >> to;
    int start = findJunction(junctions, junctionCount, from);
    int finish = findJunction(junctions, junctionCount, to);
    if (start == -1 || finish == -1 || start == finish) {
        cout << "Enter two different junctions that exist.\n";
        return;
    }

    cout << "Route type (1 shortest distance, 2 suitable for traffic): ";
    mode = readInt();
    while (mode != 1 && mode != 2) {
        cout << "Enter 1 or 2: ";
        mode = readInt();
    }

    int path[MAX_JUNCTIONS], length = 0;
    double km = 0;
    bool found = calculateRoute(roads, roadCount, junctions, junctionCount,
                                start, finish, mode == 2, -1, path, length, km);
    if (!found) {
        cout << "No route is available. Blocked roads and one-way directions were checked.\n";
        return;
    }

    cout << "\nRoute: ";
    printPath(path, length, junctions);
    cout << fixed << setprecision(2) << "Total distance: " << km << " km\n";
    if (mode == 2) cout << "This route also considers traffic levels.\n";
}

// Find an alternative by temporarily ignoring roads from the shortest route.
void Graph::findAlternativeRoute(Graph roads[], int roadCount,
                                 Junction junctions[], int junctionCount) {
    if (junctionCount < 2 || roadCount == 0) {
        cout << "Add junctions and roads first.\n";
        return;
    }
    string from, to;
    cout << "Starting junction ID: ";
    cin >> from;
    cout << "Destination junction ID: ";
    cin >> to;
    int start = findJunction(junctions, junctionCount, from);
    int finish = findJunction(junctions, junctionCount, to);
    if (start == -1 || finish == -1 || start == finish) {
        cout << "Enter two different junctions that exist.\n";
        return;
    }

    int firstPath[MAX_JUNCTIONS], firstLength = 0;
    double firstDistance = 0;
    if (!calculateRoute(roads, roadCount, junctions, junctionCount,
                        start, finish, false, -1, firstPath, firstLength, firstDistance)) {
        cout << "No route is available between these junctions.\n";
        return;
    }

    bool foundAlternative = false;
    double bestDistance = INF;
    int bestPath[MAX_JUNCTIONS], bestLength = 0;

    // Try removing each road used by the shortest route, one at a time.
    for (int p = 0; p < firstLength - 1; p++) {
        int roadIndex = -1;
        for (int r = 0; r < roadCount; r++) {
            bool match = roads[r].junction1 == junctions[firstPath[p]].junctionID &&
                         roads[r].junction2 == junctions[firstPath[p + 1]].junctionID;
            bool reverseMatch = !roads[r].isOneWay &&
                         roads[r].junction2 == junctions[firstPath[p]].junctionID &&
                         roads[r].junction1 == junctions[firstPath[p + 1]].junctionID;
            if (match || reverseMatch) {
                roadIndex = r;
                break;
            }
        }
        if (roadIndex == -1) continue;

        int path[MAX_JUNCTIONS], length = 0;
        double km = 0;
        if (calculateRoute(roads, roadCount, junctions, junctionCount,
                           start, finish, false, roadIndex, path, length, km) &&
            km < bestDistance) {
            foundAlternative = true;
            bestDistance = km;
            bestLength = length;
            for (int i = 0; i < length; i++) bestPath[i] = path[i];
        }
    }

    cout << "Shortest route: ";
    printPath(firstPath, firstLength, junctions);
    cout << "Distance: " << firstDistance << " km\n";

    if (!foundAlternative) {
        cout << "No different alternative route is available.\n";
        return;
    }
    cout << "Alternative route: ";
    printPath(bestPath, bestLength, junctions);
    cout << "Distance: " << bestDistance << " km\n";
}

// List junctions reachable from a selected starting junction.
void Graph::detectUnreachable(Graph roads[], int roadCount,
                              Junction junctions[], int junctionCount) {
    if (junctionCount == 0) {
        cout << "No junctions have been added.\n";
        return;
    }
    string from;
    cout << "Starting junction ID: ";
    cin >> from;
    int start = findJunction(junctions, junctionCount, from);
    if (start == -1) {
        cout << "Junction not found.\n";
        return;
    }

    cout << "Reachable from " << from << ": ";
    bool anyReachable = false;
    for (int i = 0; i < junctionCount; i++) {
        if (i == start) continue;
        int path[MAX_JUNCTIONS], length = 0;
        double km = 0;
        if (calculateRoute(roads, roadCount, junctions, junctionCount,
                           start, i, false, -1, path, length, km)) {
            if (anyReachable) cout << ", ";
            cout << junctions[i].junctionID;
            anyReachable = true;
        }
    }
    if (!anyReachable) cout << "None";
    cout << '\n';
}

// Compare hospital routes and recommend the nearest reachable hospital.
void Graph::findHospitalRoute(Graph roads[], int roadCount,
                              Junction junctions[], int junctionCount,
                              Facility facilities[], int facilityCount) {
    if (facilityCount == 0 || junctionCount == 0) {
        cout << "Add junctions and hospitals first.\n";
        return;
    }
    string from;
    cout << "Emergency starting junction ID: ";
    cin >> from;
    int start = findJunction(junctions, junctionCount, from);
    if (start == -1) {
        cout << "Starting junction not found.\n";
        return;
    }

    bool found = false;
    double bestDistance = INF;
    int bestPath[MAX_JUNCTIONS], bestLength = 0;
    string bestHospital;

    // Compare routes to each hospital and choose the nearest reachable one.
    for (int f = 0; f < facilityCount; f++) {
        if (facilities[f].facilityType != "Small Hospital" &&
            facilities[f].facilityType != "Big Hospital") continue;
        int destination = findJunction(junctions, junctionCount, facilities[f].junctionID);
        if (destination == -1) continue;

        int path[MAX_JUNCTIONS], length = 0;
        double km = 0;
        if (calculateRoute(roads, roadCount, junctions, junctionCount,
                           start, destination, false, -1, path, length, km) &&
            km < bestDistance) {
            found = true;
            bestDistance = km;
            bestLength = length;
            bestHospital = facilities[f].facilityName + " (" + facilities[f].facilityID + ")";
            for (int i = 0; i < length; i++) bestPath[i] = path[i];
        }
    }

    if (!found) {
        cout << "No reachable hospital was found.\n";
        return;
    }
    cout << "Recommended hospital: " << bestHospital << '\n';
    cout << "Route: ";
    printPath(bestPath, bestLength, junctions);
    cout << "Distance: " << bestDistance << " km\n";
}

// Count roads, traffic levels, junctions, and facilities for the summary.
void Graph::showNetworkInformation(Graph roads[], int roadCount,
                                   Junction[], int junctionCount,
                                   Facility facilities[], int facilityCount) {
    int blocked = 0, low = 0, moderate = 0, high = 0;
    for (int i = 0; i < roadCount; i++) {
        if (roads[i].isBlocked) blocked++;
        if (roads[i].trafficLevel == "Low") low++;
        else if (roads[i].trafficLevel == "Moderate") moderate++;
        else if (roads[i].trafficLevel == "High") high++;
    }

    int hospitals = 0, police = 0;
    for (int i = 0; i < facilityCount; i++) {
        if (facilities[i].facilityType == "Police Station") police++;
        else hospitals++;
    }

    cout << "\n===== NETWORK INFORMATION =====\n";
    cout << "Junctions: " << junctionCount << '\n';
    cout << "Roads: " << roadCount << '\n';
    cout << "Blocked roads: " << blocked << '\n';
    cout << "Low traffic roads: " << low << '\n';
    cout << "Moderate traffic roads: " << moderate << '\n';
    cout << "High traffic roads: " << high << '\n';
    cout << "Hospitals: " << hospitals << '\n';
    cout << "Police stations: " << police << '\n';
}

// Placeholder: connect this function to FileManager to save the arrays.
void Graph::saveGraphData(
    Graph roads[], int roadCount,
    Junction junctions[], int junctionCount,
    Facility facilities[], int facilityCount)
{
    FileManager fileManager;
    fileManager.saveGraphData(
        roads, roadCount,
        junctions, junctionCount,
        facilities, facilityCount);
}

// Placeholder: connect this function to FileManager to load the arrays.
void Graph::loadGraphData(
    Graph roads[], int& roadCount,
    Junction junctions[], int& junctionCount,
    Facility facilities[], int& facilityCount)
{
    FileManager fileManager;
    fileManager.loadGraphData(
        roads, roadCount,
        junctions, junctionCount,
        facilities, facilityCount);
}

void saveCurrentGraphData() {
    Graph graph;
    graph.saveGraphData(
        roads, roadCount,
        junctions, junctionCount,
        facilities, facilityCount
    );
}

void loadCurrentGraphData() {
    Graph graph;
    graph.loadGraphData(
        roads, roadCount,
        junctions, junctionCount,
        facilities, facilityCount
    );
}

void runGraphMenu()
{
    int choice;
    Graph graph;

    do {
        cout << "\n===== GRAPH MODULE =====\n";
        cout << "1. Add Junction\n";
        cout << "2. Update Junction\n";
        cout << "3. Display Junctions\n";
        cout << "4. Add Road\n";
        cout << "5. Display All Roads\n";
        cout << "6. Search Road\n";
        cout << "7. Update Road\n";
        cout << "8. Update Road Conditions\n";
        cout << "9. Remove Road\n";  //added
        cout << "10. Add Hospital\n";
        cout << "11. Add Police Station\n";
        cout << "12. Display Facilities\n";
        cout << "13. Find Shortest Route\n";
        cout << "14. Find Alternative Route\n";
        cout << "15. Detect Unreachable Junctions\n"; //added
        cout << "16. Find Nearest Hospital\n"; //
        cout << "17. Network Information\n";
        cout << "18. Save Graph Data\n";
        cout << "19. Load Graph Data\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter choice: ";
        choice = readInt();

        switch (choice) {
            case 1:
               graph.addJunction(junctions, junctionCount);
                break;

            case 2:
                 graph.updateJunction(junctions, junctionCount);
                break;

            case 3:
                 graph.displayJunctions(junctions, junctionCount, roads, roadCount);
                break;
            
                
            case 4:
                graph.inputRoad(roads, roadCount, junctions, junctionCount);
                break;

            case 5:
                graph.displayAllRoads(roads, roadCount);
                break;

            case 6:
                graph.searchRoad(roads, roadCount);
                break;

            case 7:
                graph.updateRoad(roads, roadCount, junctions, junctionCount);
                break;

            case 8:
                graph.updateRoadConditions(roads, roadCount);
                break;

            case 9:
                graph.removeRoad(roads, roadCount);

                break;
            
            case 10:
                graph.addHospital(facilities, facilityCount, junctions, junctionCount);
                break;

            case 11:
                graph.addPoliceStation(facilities, facilityCount, junctions, junctionCount);
                break;

            case 12:
                graph.displayFacilities(facilities, facilityCount);
                break;

            case 13:
                graph.findShortestRoute(roads, roadCount, junctions, junctionCount);
                break;

            case 14:
                graph.findAlternativeRoute(roads, roadCount, junctions, junctionCount);
                break;

            case 15:
                graph.detectUnreachable(roads, roadCount, junctions, junctionCount);
                break;

            case 16:
                graph.findHospitalRoute(
                    roads, roadCount, junctions, junctionCount,
                    facilities, facilityCount
                );
                break;

            case 17:
                graph.showNetworkInformation(
                    roads, roadCount, junctions, junctionCount,
                    facilities, facilityCount
                );
                break;

            case 18:
                graph.saveGraphData(
                    roads, roadCount,
                    junctions, junctionCount,
                    facilities, facilityCount
                );
                break;

            case 19:
                graph.loadGraphData(
                    roads, roadCount,
                    junctions, junctionCount,
                    facilities, facilityCount
                );
                break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}



bool findEmergencyRoute(int sourceJunction, int destinationJunction)
{
    string sourceID = "J" + to_string(sourceJunction);
    string destinationID = "J" + to_string(destinationJunction);

    int start = findJunction(junctions, junctionCount, sourceID);
    int finish = findJunction(junctions, junctionCount, destinationID);

    if (start == -1 || finish == -1 || start == finish) {
        cout << "Invalid source or destination junction.\n";
        return false;
    }

    int path[MAX_JUNCTIONS];
    int pathLength = 0;
    double totalDistance = 0;

    bool found = calculateRoute(
        roads, roadCount,
        junctions, junctionCount,
        start, finish,
        true, -1,
        path, pathLength, totalDistance
    );

    if (!found) {
        cout << "No emergency route available. Check road connections and blocked roads.\n";
        return false;
    }

    cout << "\nEmergency route: ";
    printPath(path, pathLength, junctions);

    cout << fixed << setprecision(2)
         << "Total distance: " << totalDistance << " km\n";

    cout << "Traffic-aware route calculated successfully.\n";
    return true;
}

