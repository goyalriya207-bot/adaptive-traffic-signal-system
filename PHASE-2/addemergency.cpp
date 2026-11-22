#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>

using namespace std;

// --------------------------------------------------
// SHARED DATA STRUCTURES
// --------------------------------------------------

struct Location
{
    string id;
    string name;
    string type;
};

struct Road
{
    int from;
    int to;
    double distance;
    double speedLimit;
    int capacity;
    int currentVehicles;
};

struct Vehicle
{
    string type;
    string registration;
    double preferredSpeed;
};

struct RouteResult
{
    bool found;
    vector<int> path;
    double totalDistance;
    double estimatedMinutes;
};

extern vector<Location> locations;
extern vector<Road> roads;

int locationIndex(const string& id);
void initializeLocations();
void initializeRoads();

RouteResult findShortestRoute(
    int source,
    int destination,
    const Vehicle& vehicle
);

// --------------------------------------------------
// EMERGENCY AND RESOURCE TYPES
// --------------------------------------------------

enum EmergencyType
{
    MEDICAL,
    FIRE,
    EARTHQUAKE
};

enum ResourceType
{
    AMBULANCE,
    FIRE_TRUCK,
    POLICE_JEEP,
    RESCUE_VAN
};

enum FireSeverity
{
    LOW = 1,
    MEDIUM,
    HIGH
};

// --------------------------------------------------
// EMERGENCY CLASS
// --------------------------------------------------

class Emergency
{
private:
    int emergencyId;
    EmergencyType type;

    int injuredPeople;
    int peopleToRescue;

    int peopleTrapped;
    int peopleToEvacuate;
    int fireSeverity;

    string location;
    string description;
    int priority;

    string status;
    bool processed;

public:

    Emergency(int id, EmergencyType t, int injured, int rescue, string loc, string desc,
          int severity = 0, int trapped = 0, int evacuation = 0)
    {
        emergencyId = id;
        type = t;
        injuredPeople = injured;
        peopleToRescue = rescue;
        location = loc;
        description = desc;
        fireSeverity = severity;
        peopleTrapped = trapped;
        peopleToEvacuate = evacuation;
        priority = 0;
        status = "Reported";
        processed = false;
    }

    int getId() const
    {
        return emergencyId;
    }

    EmergencyType getType() const
    {
        return type;
    }

    int getInjuredPeople() const
    {
        return injuredPeople;
    }

    int getPeopleToRescue() const
    {
        return peopleToRescue;
    }

    int getPeopleTrapped() const
    {
        return peopleTrapped;
    }

    int getPeopleToEvacuate() const
    {
        return peopleToEvacuate;
    }

    int getFireSeverity() const
    {
        return fireSeverity;
    }

    string getLocation() const
    {
        return location;
    }

    string getDescription() const
    {
        return description;
    }

    int getPriority() const
    {
        return priority;
    }

    string getStatus() const
    {
        return status;
    }

    bool isProcessed() const
    {
        return processed;
    }

    void setPriority(int p)
    {
        priority = p;
    }

    void setStatus(string s)
    {
        status = s;
    }

    void setProcessed(bool value)
    {
        processed = value;
    }
};

// --------------------------------------------------
// VEHICLE REQUIREMENT AND PRIORITY
// --------------------------------------------------

int vehiclesRequired(int people, int capacity)
{
    if (people <= 0)
        return 0;

    return (people + capacity - 1) / capacity;
}

int getResourceWeight(ResourceType resource)
{
    if (resource == AMBULANCE)
        return 4;

    if (resource == RESCUE_VAN)
        return 3;

    return 2;
}

int calculatePriority(int injured, ResourceType resource)
{
    return injured * 6 + getResourceWeight(resource);
}

int getEmergencyPriority(const Emergency& emergency)
{
    if (emergency.getType() == MEDICAL)
    {
        return calculatePriority(
            emergency.getInjuredPeople(), AMBULANCE);
    }

    if (emergency.getType() == FIRE)
    {
        return emergency.getFireSeverity() * 20
            + emergency.getInjuredPeople() * 2
            + getResourceWeight(FIRE_TRUCK);
    }

    return emergency.getPeopleTrapped() * 6
       + emergency.getInjuredPeople() * 6
       + emergency.getPeopleToEvacuate() * 6
       + getResourceWeight(RESCUE_VAN);
}

// --------------------------------------------------
// EMERGENCY LIST
// --------------------------------------------------

vector<Emergency> emergencyList;

void addEmergency(Emergency emergency)
{
    emergency.setPriority(getEmergencyPriority(emergency));
    emergencyList.push_back(emergency);
}

void sortEmergencies()
{
    stable_sort(emergencyList.begin(), emergencyList.end(),
         [](const Emergency& a, const Emergency& b)
         {
             return a.getPriority() > b.getPriority();
         });
}

// --------------------------------------------------
// RESOURCE STATION DATA
// --------------------------------------------------

struct ResourceStation
{
    string id;
    string name;
    string type;
    int locationIndex;

    int availableAmbulances;
    int availableFireTrucks;
    int availablePoliceJeeps;
    int availableRescueVans;
    int availableBeds;
    int availableRescueCapacity;
};

vector<ResourceStation> resourceStations;

// --------------------------------------------------
// ADD RESOURCE STATION
// --------------------------------------------------

void addResourceStation(string id, string name, string type,
                        int location, int ambulances,
                        int fireTrucks, int policeJeeps,
                        int rescueVans, int beds,
                        int rescueCapacity)
{
    if (location == -1)
        return;

    resourceStations.push_back({
        id, name, type, location,
        ambulances, fireTrucks, policeJeeps,
        rescueVans, beds, rescueCapacity
    });
}

// --------------------------------------------------
// INITIALIZE RESOURCE STATIONS
// --------------------------------------------------

void initializeResourceStations()
{
    resourceStations.clear();

    // Hospitals

    addResourceStation("H1", "Doon Hospital", "Hospital",
        locationIndex("H1"), 9, 0, 0, 0, 25, 0);

    addResourceStation("H2", "Shri Mahant Indiresh Hospital", "Hospital",
        locationIndex("H2"), 9, 0, 0, 0, 25, 0);

    addResourceStation("H3", "Max Super Speciality Hospital", "Hospital",
        locationIndex("H3"), 9, 0, 0, 0, 25, 0);

    addResourceStation("H4", "Graphic Era Hospital", "Hospital",
        locationIndex("H4"), 9, 0, 0, 0, 25, 0);

    addResourceStation("H5", "Synergy Hospital", "Hospital",
        locationIndex("H5"), 9, 0, 0, 0, 25, 0);

    addResourceStation("H6", "Coronation Hospital", "Hospital",
        locationIndex("H6"), 6, 0, 0, 0, 18, 0);

    addResourceStation("H7", "Combined Medical Institute", "Hospital",
        locationIndex("H7"), 6, 0, 0, 0, 18, 0);

    addResourceStation("H8", "Prem Sukh Hospital", "Hospital",
        locationIndex("H8"), 6, 0, 0, 0, 18, 0);

    addResourceStation("H9", "Uttaranchal Hospital", "Hospital",
        locationIndex("H9"), 6, 0, 0, 0, 18, 0);

    // Police Stations

    addResourceStation("P1", "Dalanwala Police Station", "Police Station",
        locationIndex("P1"), 0, 0, 3, 0, 0, 0);

    addResourceStation("P2", "Nehru Colony Police Station", "Police Station",
        locationIndex("P2"), 0, 0, 3, 0, 0, 0);

    addResourceStation("P3", "Patel Nagar Police Station", "Police Station",
        locationIndex("P3"), 0, 0, 3, 0, 0, 0);

    addResourceStation("P4", "Rajpur Police Station", "Police Station",
        locationIndex("P4"), 0, 0, 3, 0, 0, 0);

    addResourceStation("P5", "Clement Town Police Station", "Police Station",
        locationIndex("P5"), 0, 0, 3, 0, 0, 0);

    // Fire Stations

    addResourceStation("F1", "Dehradun Fire Station", "Fire Station",
        locationIndex("F1"), 0, 2, 0, 0, 0, 0);

    addResourceStation("F2", "Doiwala Fire Station", "Fire Station",
        locationIndex("F2"), 0, 2, 0, 0, 0, 0);

    addResourceStation("F3", "Selaqui Fire Station", "Fire Station",
        locationIndex("F3"), 0, 2, 0, 0, 0, 0);

    addResourceStation("F4", "Mussoorie Fire Station", "Fire Station",
        locationIndex("F4"), 0, 2, 0, 0, 0, 0);

    // Rescue Hubs

    addResourceStation("R1", "Dehradun Central Emergency Rescue Hub",
        "Rescue Hub", locationIndex("R1"),
        0, 0, 0, 20, 0, 500);

    addResourceStation("R2", "Saharanpur Chowk Emergency Rescue Hub",
        "Rescue Hub", locationIndex("R2"),
        0, 0, 0, 13, 0, 300);
}

// --------------------------------------------------
// EMERGENCY RESOURCE REQUIREMENTS
// --------------------------------------------------

struct ResourceRequirement
{
    int ambulances;
    int fireTrucks;
    int policeJeeps;
    int rescueVans;
    int hospitalBeds;
    int rescueCapacity;
};

// --------------------------------------------------
// CALCULATE REQUIRED RESOURCES
// --------------------------------------------------

ResourceRequirement calculateRequirements(const Emergency& emergency)
{
    ResourceRequirement required = {0, 0, 0, 0, 0, 0};

    int injured = emergency.getInjuredPeople();

    required.ambulances = vehiclesRequired(injured, 3);
    required.hospitalBeds = injured;

    if (emergency.getType() == FIRE)
    {
        int severity = emergency.getFireSeverity();

        if (severity == LOW)
            required.fireTrucks = 1;
        else if (severity == MEDIUM)
            required.fireTrucks = 2;
        else
            required.fireTrucks = 3;
        
        required.policeJeeps = 1;
        required.rescueVans = vehiclesRequired(emergency.getPeopleToRescue(), 25);
        required.rescueCapacity = emergency.getPeopleToRescue();
    }

    else if (emergency.getType() == EARTHQUAKE)
    {
        required.rescueVans =
            vehiclesRequired(emergency.getPeopleToRescue(), 25);

        required.rescueCapacity =
            emergency.getPeopleToRescue();

        required.policeJeeps = 1;
    }

    return required;
}

// --------------------------------------------------
// ALLOCATION RESULT
// --------------------------------------------------

struct AllocatedResource
{
    string stationId;
    string stationName;
    int quantity;
    double travelTime;
    vector<int> path;
};

struct AllocationResult
{
    vector<AllocatedResource> ambulances;
    vector<AllocatedResource> fireTrucks;
    vector<AllocatedResource> policeJeeps;
    vector<AllocatedResource> rescueVans;
    vector<AllocatedResource> hospitals;
    vector<AllocatedResource> rescueHubs;

    int missingAmbulances = 0;
    int missingFireTrucks = 0;
    int missingPoliceJeeps = 0;
    int missingRescueVans = 0;
    int missingHospitalBeds = 0;
    int missingRescueCapacity = 0;

    bool fullyAllocated = false;
};

// --------------------------------------------------
// GET AVAILABLE VEHICLE COUNT
// --------------------------------------------------

int getAvailableResource(const ResourceStation& station,
                         ResourceType resource)
{
    if (resource == AMBULANCE)
        return station.availableAmbulances;

    if (resource == FIRE_TRUCK)
        return station.availableFireTrucks;

    if (resource == POLICE_JEEP)
        return station.availablePoliceJeeps;

    if (resource == RESCUE_VAN)
        return station.availableRescueVans;

    return 0;
}

// --------------------------------------------------
// ALLOCATE VEHICLES FROM NEAREST STATIONS
// --------------------------------------------------

vector<AllocatedResource> allocateVehicles(
    int emergencyLocation,
    ResourceType resource,
    int requiredQuantity,
    double vehicleSpeed,
    int& missingQuantity)
{
    vector<AllocatedResource> allocation;
    vector<pair<double, int>> stationOrder;

    missingQuantity = requiredQuantity;

    if (requiredQuantity <= 0)
    {
        missingQuantity = 0;
        return allocation;
    }

    string vehicleType;

    if (resource == AMBULANCE)
        vehicleType = "Ambulance";
    else if (resource == FIRE_TRUCK)
        vehicleType = "Fire Truck";
    else if (resource == POLICE_JEEP)
        vehicleType = "Police Jeep";
    else
        vehicleType = "Rescue Van";

    Vehicle vehicle = {vehicleType, "", vehicleSpeed};

    for (int i = 0; i < (int)resourceStations.size(); i++)
    {
        ResourceStation& station = resourceStations[i];

        if (getAvailableResource(station, resource) <= 0)
            continue;

        RouteResult route = findShortestRoute(station.locationIndex, emergencyLocation, vehicle);

        if (route.found)
        {
            stationOrder.push_back({route.estimatedMinutes, i});
        }
    }

    sort(stationOrder.begin(), stationOrder.end());

    for (int i = 0;
         i < (int)stationOrder.size() && missingQuantity > 0;
         i++)
    {
        int index = stationOrder[i].second;
        ResourceStation& station = resourceStations[index];

        int available = getAvailableResource(station, resource);
        int quantity = min(available, missingQuantity);

        if (quantity > 0)
        {
            RouteResult route = findShortestRoute(station.locationIndex, emergencyLocation, vehicle);

            allocation.push_back({
                station.id,
                station.name,
                quantity,
                route.estimatedMinutes,
                route.path
            });

            missingQuantity -= quantity;
        }
    }

    return allocation;
}

// --------------------------------------------------
// PLAN VEHICLE ALLOCATION
// --------------------------------------------------

void planVehicleAllocation(
    const Emergency& emergency,
    int emergencyLocation,
    AllocationResult& result)
{
    ResourceRequirement required = calculateRequirements(emergency);

    result.ambulances = allocateVehicles(
        emergencyLocation, AMBULANCE,
        required.ambulances, 50,
        result.missingAmbulances
    );

    result.fireTrucks = allocateVehicles(
        emergencyLocation, FIRE_TRUCK,
        required.fireTrucks, 40,
        result.missingFireTrucks
    );

    result.policeJeeps = allocateVehicles(
        emergencyLocation, POLICE_JEEP,
        required.policeJeeps, 45,
        result.missingPoliceJeeps
    );

    result.rescueVans = allocateVehicles(
        emergencyLocation, RESCUE_VAN,
        required.rescueVans, 35,
        result.missingRescueVans
    );
}

// --------------------------------------------------
// PLAN HOSPITAL BEDS AND RESCUE CAPACITY
// --------------------------------------------------

void planCapacityAllocation(
    const Emergency& emergency,
    int emergencyLocation,
    AllocationResult& result)
{
    ResourceRequirement required = calculateRequirements(emergency);

    int bedsNeeded = required.hospitalBeds;
    int rescueNeeded = required.rescueCapacity;

    vector<pair<double, int>> hospitalOrder;
    vector<pair<double, int>> rescueHubOrder;

    Vehicle ambulance = {"Ambulance", "", 50};
    Vehicle rescueVan = {"Rescue Van", "", 35};

    for (int i = 0; i < (int)resourceStations.size(); i++)
    {
        ResourceStation& station = resourceStations[i];

        if (station.type != "Hospital" ||
            station.availableBeds <= 0)
            continue;

        RouteResult route = findShortestRoute(
            emergencyLocation, station.locationIndex, ambulance
        );

        if (route.found)
            hospitalOrder.push_back({route.estimatedMinutes, i});
    }

    sort(hospitalOrder.begin(), hospitalOrder.end());

    for (int i = 0; i < (int)hospitalOrder.size() && bedsNeeded > 0; i++)
    {
        int index = hospitalOrder[i].second;
        ResourceStation& station = resourceStations[index];

        int beds = min(station.availableBeds, bedsNeeded);

        RouteResult route = findShortestRoute(
            emergencyLocation, station.locationIndex, ambulance
        );

        result.hospitals.push_back({
            station.id,
            station.name,
            beds,
            route.estimatedMinutes,
            route.path
        });

        bedsNeeded -= beds;
    }

    result.missingHospitalBeds = bedsNeeded;

    for (int i = 0; i < (int)resourceStations.size(); i++)
    {
        ResourceStation& station = resourceStations[i];

        if (station.type != "Rescue Hub" ||
            station.availableRescueCapacity <= 0)
            continue;

        RouteResult route = findShortestRoute(
            emergencyLocation, station.locationIndex, rescueVan
        );

        if (route.found)
            rescueHubOrder.push_back({route.estimatedMinutes, i});
    }

    sort(rescueHubOrder.begin(), rescueHubOrder.end());

    for (int i = 0;
         i < (int)rescueHubOrder.size() && rescueNeeded > 0;
         i++)
    {
        int index = rescueHubOrder[i].second;
        ResourceStation& station = resourceStations[index];

        int capacity = min(
            station.availableRescueCapacity,
            rescueNeeded
        );

        RouteResult route = findShortestRoute(
            emergencyLocation, station.locationIndex, rescueVan
        );

        result.rescueHubs.push_back({
            station.id,
            station.name,
            capacity,
            route.estimatedMinutes,
            route.path
        });

        rescueNeeded -= capacity;
    }

    result.missingRescueCapacity = rescueNeeded;
}

// --------------------------------------------------
// PLAN COMPLETE EMERGENCY ALLOCATION
// --------------------------------------------------

AllocationResult planEmergency(
    const Emergency& emergency,
    int emergencyLocation)
{
    AllocationResult result;

    if (emergency.getInjuredPeople() < 0 ||
        emergency.getPeopleToRescue() < 0 ||
        emergencyLocation < 0 ||
        emergencyLocation >= (int)locations.size() ||
        locations[emergencyLocation].id != emergency.getLocation())
    {
        return result;
    }

    planVehicleAllocation(emergency, emergencyLocation, result);

    planCapacityAllocation(emergency, emergencyLocation, result);

    result.fullyAllocated =
        result.missingAmbulances == 0 &&
        result.missingFireTrucks == 0 &&
        result.missingPoliceJeeps == 0 &&
        result.missingRescueVans == 0 &&
        result.missingHospitalBeds == 0 &&
        result.missingRescueCapacity == 0;

    return result;
}

// --------------------------------------------------
// FIND RESOURCE STATION
// --------------------------------------------------

int findResourceStation(const string& stationId)
{
    for (int i = 0; i < (int)resourceStations.size(); i++)
    {
        if (resourceStations[i].id == stationId)
            return i;
    }

    return -1;
}

// --------------------------------------------------
// RESERVE ALLOCATED RESOURCES
// --------------------------------------------------

bool reserveResources(const AllocationResult& result)
{
    if (!result.fullyAllocated)
        return false;

    // Check ambulance availability

    for (const auto& item : result.ambulances)
    {
        int index = findResourceStation(item.stationId);

        if (index == -1 ||
            resourceStations[index].availableAmbulances < item.quantity)
            return false;
    }

    // Check fire truck availability

    for (const auto& item : result.fireTrucks)
    {
        int index = findResourceStation(item.stationId);

        if (index == -1 ||
            resourceStations[index].availableFireTrucks < item.quantity)
            return false;
    }

    // Check police jeep availability

    for (const auto& item : result.policeJeeps)
    {
        int index = findResourceStation(item.stationId);

        if (index == -1 ||
            resourceStations[index].availablePoliceJeeps < item.quantity)
            return false;
    }

    // Check rescue van availability

    for (const auto& item : result.rescueVans)
    {
        int index = findResourceStation(item.stationId);

        if (index == -1 ||
            resourceStations[index].availableRescueVans < item.quantity)
            return false;
    }

    // Check hospital beds

    for (const auto& item : result.hospitals)
    {
        int index = findResourceStation(item.stationId);

        if (index == -1 ||
            resourceStations[index].availableBeds < item.quantity)
            return false;
    }

    // Check rescue hub capacity

    for (const auto& item : result.rescueHubs)
    {
        int index = findResourceStation(item.stationId);

        if (index == -1 ||
            resourceStations[index].availableRescueCapacity < item.quantity)
            return false;
    }

    // Deduct resources only after all checks pass

    for (const auto& item : result.ambulances)
        resourceStations[findResourceStation(item.stationId)].availableAmbulances -= item.quantity;

    for (const auto& item : result.fireTrucks)
        resourceStations[findResourceStation(item.stationId)].availableFireTrucks -= item.quantity;

    for (const auto& item : result.policeJeeps)
        resourceStations[findResourceStation(item.stationId)].availablePoliceJeeps -= item.quantity;

    for (const auto& item : result.rescueVans)
        resourceStations[findResourceStation(item.stationId)].availableRescueVans -= item.quantity;

    for (const auto& item : result.hospitals)
        resourceStations[findResourceStation(item.stationId)].availableBeds -= item.quantity;

    for (const auto& item : result.rescueHubs)
        resourceStations[findResourceStation(item.stationId)].availableRescueCapacity -= item.quantity;

    return true;
}

// --------------------------------------------------
// DISPLAY ROUTE
// --------------------------------------------------

void displayPath(const vector<int>& path)
{
    for (int i = 0; i < (int)path.size(); i++)
    {
        if (i > 0)
            cout << " -> ";

        cout << locations[path[i]].id;
    }
}

// --------------------------------------------------
// DISPLAY ALLOCATION
// --------------------------------------------------

void displayResourceList(const string& heading, const vector<AllocatedResource>& resources,
    const string& quantityLabel = "Quantity")
{
    for (const auto& item : resources)
    {
        cout << "\n" << heading << ": "
             << item.stationName;

        cout << "\n" << quantityLabel << ": "
             << item.quantity;

        cout << "\nEstimated travel time: "
             << item.travelTime << " minutes";

        cout << "\nRoute: ";
        displayPath(item.path);

        cout << "\n";
    }
}

void displayAllocation(const AllocationResult& result)
{
    if (!result.fullyAllocated)
    {
        cout << "\nAll required resources are not available.\n";

        cout << "Missing ambulances: "
             << result.missingAmbulances << endl;

        cout << "Missing fire trucks: "
             << result.missingFireTrucks << endl;

        cout << "Missing police jeeps: "
             << result.missingPoliceJeeps << endl;

        cout << "Missing rescue vans: "
             << result.missingRescueVans << endl;

        cout << "Missing hospital beds: "
             << result.missingHospitalBeds << endl;

        cout << "Missing rescue capacity: "
             << result.missingRescueCapacity << endl;

        return;
    }

    cout << "\nAll required resources are available.\n";
displayResourceList("Ambulance", result.ambulances);

displayResourceList("Fire Truck", result.fireTrucks);

displayResourceList("Police Jeep", result.policeJeeps);

displayResourceList("Rescue Van dispatched from", result.rescueVans);

displayResourceList("Hospital", result.hospitals, "Beds allocated");

displayResourceList("Rescue Shelter", result.rescueHubs, "People accommodated");
}

// --------------------------------------------------
// PROCESS EMERGENCIES
// --------------------------------------------------

void processEmergencies()
{
    sortEmergencies();

    for (int i = 0; i < (int)emergencyList.size(); i++)
    {
        Emergency& emergency = emergencyList[i];

        if (emergency.isProcessed())
            continue;

        cout << "\n====================================\n";
        cout << "EMERGENCY ID: " << emergency.getId() << endl;
        cout << "PRIORITY: " << emergency.getPriority() << endl;
        cout << "LOCATION: " << emergency.getLocation() << endl;
        cout << "DESCRIPTION: " << emergency.getDescription() << endl;
        cout << "====================================\n";

        int emergencyLocation =
            locationIndex(emergency.getLocation());

        if (emergencyLocation == -1)
        {
            cout << "Invalid emergency location.\n";
            continue;
        }

        AllocationResult result =
            planEmergency(emergency, emergencyLocation);

        displayAllocation(result);

        if (result.fullyAllocated)
        {
            if (reserveResources(result))
            {
                emergency.setProcessed(true);

                emergency.setStatus("Resources Allocated");

                cout << "\nResources successfully allocated.\n";
                cout << "Emergency report has been processed.\n";
            }
            else
            {
                cout << "\nResources could not be reserved.\n";
            }
        }
        else
        {
            cout << "\nRequired resources are not fully available.\n";
            cout << "Emergency remains pending.\n";
        }
    }
}

// --------------------------------------------------
// TERMINAL TESTING
// --------------------------------------------------

#ifndef SERVER_BUILD

int nextEmergencyId = 1;

void displayEmergencyLocations()
{
    cout << "\nSELECT EMERGENCY LOCATION\n";

    int count = 0;

    for (int i = 0; i < (int)locations.size(); i++)
    {
        if (locations[i].type == "Junction")
        {
            count++;
            cout << count << ". " << locations[i].name << " (" << locations[i].id << ")\n";
        }
    }
}
void submitEmergency()
{
    int type;
    int injured = 0;
    int rescue = 0;
    int severity = 0;
    int trapped = 0;
    int evacuation = 0;
    int locationChoice;
    string description;

    cout << "\nSELECT EMERGENCY TYPE\n";
    cout << "1. Medical\n";
    cout << "2. Fire\n";
    cout << "3. Earthquake\n";
    cout << "Enter choice: ";
    cin >> type;

    if (type < 1 || type > 3)
    {
        cout << "Invalid emergency type.\n";
        return;
    }

    EmergencyType emergencyType;

    if (type == 1)
    {
        emergencyType = MEDICAL;

        cout << "Enter number of injured people: ";
        cin >> injured;

        if (injured <= 0)
        {
            cout << "Invalid number of injured people.\n";
            return;
        }
    }

    else if (type == 2)
    {
        emergencyType = FIRE;

        cout << "\nSelect fire severity:\n";
        cout << "1. Low\n";
        cout << "2. Medium\n";
        cout << "3. High\n";
        cout << "Enter choice: ";
        cin >> severity;

        if (severity < 1 || severity > 3)
        {
            cout << "Invalid severity.\n";
            return;
        }

        cout << "Enter number of injured people: ";
        cin >> injured;

        cout << "Enter number of people trapped inside: ";
        cin >> trapped;

        if (injured < 0 || trapped < 0 ||
            (injured == 0 && trapped == 0))
        {
            cout << "Enter valid numbers.\n";
            return;
        }

        rescue = trapped;
    }

    else
    {
        emergencyType = EARTHQUAKE;

        cout << "\nEnter number of people trapped: ";
        cin >> trapped;

        cout << "Enter number of injured people: ";
        cin >> injured;

        cout << "Enter number of additional people requiring evacuation: ";
        cin >> evacuation;

        if (trapped < 0 || injured < 0 || evacuation < 0)
        {
            cout << "Invalid number.\n";
            return;
        }

        if (trapped == 0 && injured == 0 && evacuation == 0)
        {
            cout << "Enter valid emergency details.\n";
            return;
        }

        rescue = trapped + evacuation;
    }

cout << "\nEnter a short emergency description: ";
cin >> ws;
getline(cin, description);

displayEmergencyLocations();

cout << "\nEnter location number: ";
cin >> locationChoice;

int junctionCount = 0;
int selectedLocation = -1;

for (int i = 0; i < (int)locations.size(); i++)
{
    if (locations[i].type == "Junction")
    {
        junctionCount++;

        if (junctionCount == locationChoice)
        {
            selectedLocation = i;
            break;
        }
    }
}

if (selectedLocation == -1)
{
    cout << "Invalid location selection.\n";
    return;
}

string location = locations[selectedLocation].id;

    Emergency emergency(
        nextEmergencyId++,
        emergencyType,
        injured,
        rescue,
        location,
        description,
        severity,
        trapped,
        evacuation
    );

    addEmergency(emergency);

    cout << "\nEmergency successfully reported.\n";
    cout << "Emergency ID: " << emergencyList.back().getId() << endl;

    processEmergencies();
}

void displayAllEmergencies()
{
    if (emergencyList.empty())
    {
        cout << "\nNo emergencies reported yet.\n";
        return;
    }

    cout << "\n========== ALL EMERGENCIES ==========\n";

    for (const auto& emergency : emergencyList)
    {
        cout << "\nEmergency ID: " << emergency.getId();

        cout << "\nLocation: " << emergency.getLocation();

        cout << "\nPriority: " << emergency.getPriority();

        cout << "\nStatus: " << emergency.getStatus();

        if (emergency.getType() == MEDICAL)
            cout << "\nType: Medical";

        else if (emergency.getType() == FIRE)
            cout << "\nType: Fire";

        else
            cout << "\nType: Earthquake";

        cout << "\n";
    }
}

int main()
{
    initializeLocations();
    initializeRoads();
    initializeResourceStations();

    int choice;

    cout << "\n========================================\n";
    cout << " ADAPTIVE TRAFFIC & EMERGENCY SYSTEM\n";
    cout << "========================================\n";

    do
    {
        cout << "\n1. Report an Emergency\n";
        cout << "0. Exit\n";

        cout << "\nEnter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                submitEmergency();
                break;

            case 0:
                cout << "\nThank you for using the system.\n";
                break;

            default:
                cout << "\nInvalid choice.\n";
        }

    } while (choice != 0);

    return 0;
}

#endif