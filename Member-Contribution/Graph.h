#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <string>
using namespace std;

// Safe input helpers: they keep asking until the user types a valid number,
// so a letter typed by mistake can no longer cause an infinite loop.
int readInt();
double readDouble();

// Details of one junction.
struct Junction {
    string junctionID;
    string junctionName;
    string junctionType;
};

// Details of a hospital or police station.
struct Facility {
    string facilityID;
    string facilityName;
    string facilityType;
    string junctionID;
};

// Each Graph object stores one road. Its functions manage the whole network.
class Graph {
public:
    // Road details are public so the simple route helper can read them.
    int roadID;
    string junction1;
    string junction2;
    string road_Name;
    double distance;
    string road_type;
    bool isBlocked;
    bool isOneWay;
    string trafficLevel;

public:
    Graph();

    // Junction functions
    void addJunction(Junction junctions[], int &junctionCount);
    void updateJunction(Junction junctions[], int junctionCount);
    void displayJunctions(Junction junctions[], int junctionCount,
                          Graph roads[], int roadCount);

    // Road functions
    void inputRoad(Graph roads[], int &roadCount,
                   Junction junctions[], int junctionCount);
    void displayRoad();
    void displayAllRoads(Graph roads[], int roadCount);
    bool isDuplicate_RoadID(Graph roads[], int roadCount, int id);
    void searchRoad(Graph roads[], int roadCount);
    void updateRoad(Graph roads[], int roadCount,
                    Junction junctions[], int junctionCount);
    void updateRoadConditions(Graph roads[], int roadCount);
    void removeRoad(Graph roads[], int &roadCount);

    // Facility functions
    void addHospital(Facility facilities[], int &facilityCount,
                     Junction junctions[], int junctionCount);
    void addPoliceStation(Facility facilities[], int &facilityCount,
                          Junction junctions[], int junctionCount);
    void displayFacilities(Facility facilities[], int facilityCount);

    // Functions for finding routes through the road network.
    void findShortestRoute(Graph roads[], int roadCount,
                           Junction junctions[], int junctionCount);
    void findAlternativeRoute(Graph roads[], int roadCount,
                              Junction junctions[], int junctionCount);
    void detectUnreachable(Graph roads[], int roadCount,
                           Junction junctions[], int junctionCount);
    void findHospitalRoute(Graph roads[], int roadCount,
                           Junction junctions[], int junctionCount,
                           Facility facilities[], int facilityCount);

    // Prints a summary of the current network.
    void showNetworkInformation(Graph roads[], int roadCount,
                                Junction junctions[], int junctionCount,
                                Facility facilities[], int facilityCount);

    // These functions remain integration points until FileManager is connected.
    void saveGraphData(Graph roads[], int roadCount,
                       Junction junctions[], int junctionCount,
                       Facility facilities[], int facilityCount);
    void loadGraphData(Graph roads[], int &roadCount,
                       Junction junctions[], int &junctionCount,
                       Facility facilities[], int &facilityCount);
    
};

void runGraphMenu();
bool findEmergencyRoute(int sourceJunction, int destinationJunction);

void saveCurrentGraphData();
void loadCurrentGraphData();

#endif

