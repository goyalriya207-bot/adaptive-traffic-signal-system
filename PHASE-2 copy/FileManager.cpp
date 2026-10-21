#include "FileManager.h"
#include <fstream>

void FileManager::saveData(const vector<Vehicle>& vehicles)
{
    ofstream file("vehicles.txt");

    if (!file.is_open())
    {
        cout << "Error: Could not open vehicles.txt for saving.\n";
        return;
    }

    for (int i = 0; i < static_cast<int>(vehicles.size()); i++)
    {
        file << vehicles[i].get_vehicle_id() << "|"
             << vehicles[i].get_vehicle_type() << "|"
             << vehicles[i].get_vehicle_registration_number() << "|"
             << vehicles[i].is_emergency_vehicle() << "\n";
    }

    file.close();
    cout << "Vehicle data saved successfully!\n";
}

void FileManager::loadData(vector<Vehicle>& vehicles)
{
    ifstream file("vehicles.txt");

    if (!file.is_open())
    {
        cout << "No saved vehicle file found. Add vehicles and save first.\n";
        return;
    }

    vector<Vehicle> loadedVehicles;
    string id, type, registration;
    string emergencyText;

    while (getline(file, id, '|') &&
           getline(file, type, '|') &&
           getline(file, registration, '|') &&
           getline(file, emergencyText))
    {
        bool emergency = (emergencyText == "1");

        Vehicle v;
        v.setVehicleData(id, type, registration, emergency);
        loadedVehicles.push_back(v);
    }

    file.close();

    vehicles = loadedVehicles;

    cout << loadedVehicles.size()
         << " vehicle(s) loaded successfully!\n";
}

void FileManager::saveGraphData(
    const Graph roads[], int roadCount,
    const Junction junctions[], int junctionCount,
    const Facility facilities[], int facilityCount)
{
    ofstream file("graph_data.txt");

    if (!file.is_open())
    {
        cout << "Error: Could not open graph_data.txt for saving.\n";
        return;
    }

    file << junctionCount << "\n";

    for (int i = 0; i < junctionCount; i++)
    {
        file << junctions[i].junctionID << "|"
             << junctions[i].junctionName << "|"
             << junctions[i].junctionType << "\n";
    }

    file << roadCount << "\n";

    for (int i = 0; i < roadCount; i++)
    {
        file << roads[i].roadID << "|"
             << roads[i].junction1 << "|"
             << roads[i].junction2 << "|"
             << roads[i].road_Name << "|"
             << roads[i].distance << "|"
             << roads[i].road_type << "|"
             << roads[i].isBlocked << "|"
             << roads[i].isOneWay << "|"
             << roads[i].trafficLevel << "\n";
    }

    file << facilityCount << "\n";

    for (int i = 0; i < facilityCount; i++)
    {
        file << facilities[i].facilityID << "|"
             << facilities[i].facilityName << "|"
             << facilities[i].facilityType << "|"
             << facilities[i].junctionID << "\n";
    }

    file.close();
    cout << "Graph data saved successfully to graph_data.txt!\n";
}

void FileManager::loadGraphData(
    Graph roads[], int& roadCount,
    Junction junctions[], int& junctionCount,
    Facility facilities[], int& facilityCount)
{
    ifstream file("graph_data.txt");

    if (!file.is_open())
    {
        cout << "No saved graph file found. Save graph data first.\n";
        return;
    }

    int loadedJunctionCount, loadedRoadCount, loadedFacilityCount;

    if (!(file >> loadedJunctionCount) ||
        loadedJunctionCount < 0 || loadedJunctionCount > 15)
    {
        cout << "Invalid junction data in file.\n";
        return;
    }
    file.ignore(10000, '\n');

    for (int i = 0; i < loadedJunctionCount; i++)
    {
        getline(file, junctions[i].junctionID, '|');
        getline(file, junctions[i].junctionName, '|');
        getline(file, junctions[i].junctionType);

        if (!file)
        {
            cout << "Error reading junction data.\n";
            return;
        }
    }

    if (!(file >> loadedRoadCount) ||
        loadedRoadCount < 0 || loadedRoadCount > 105)
    {
        cout << "Invalid road data in file.\n";
        return;
    }
    file.ignore(10000, '\n');

    for (int i = 0; i < loadedRoadCount; i++)
    {
        string blockedText, oneWayText;

        if (!(file >> roads[i].roadID))
        {
            cout << "Error reading road data.\n";
            return;
        }
        file.ignore(1, '|');

        getline(file, roads[i].junction1, '|');
        getline(file, roads[i].junction2, '|');
        getline(file, roads[i].road_Name, '|');

        if (!(file >> roads[i].distance))
        {
            cout << "Error reading road distance.\n";
            return;
        }
        file.ignore(1, '|');

        getline(file, roads[i].road_type, '|');

        if (!(file >> roads[i].isBlocked))
        {
            cout << "Error reading road status.\n";
            return;
        }
        file.ignore(1, '|');

        if (!(file >> roads[i].isOneWay))
        {
            cout << "Error reading road direction.\n";
            return;
        }
        file.ignore(1, '|');

        getline(file, roads[i].trafficLevel);
    }

    if (!(file >> loadedFacilityCount) ||
        loadedFacilityCount < 0 || loadedFacilityCount > 7)
    {
        cout << "Invalid facility data in file.\n";
        return;
    }
    file.ignore(10000, '\n');

    for (int i = 0; i < loadedFacilityCount; i++)
    {
        getline(file, facilities[i].facilityID, '|');
        getline(file, facilities[i].facilityName, '|');
        getline(file, facilities[i].facilityType, '|');
        getline(file, facilities[i].junctionID);

        if (!file)
        {
            cout << "Error reading facility data.\n";
            return;
        }
    }

    file.close();

    junctionCount = loadedJunctionCount;
    roadCount = loadedRoadCount;
    facilityCount = loadedFacilityCount;

    cout << "Graph data loaded successfully!\n";
}