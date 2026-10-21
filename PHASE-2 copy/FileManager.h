#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Graph.h"

using namespace std;

class FileManager
{
public:
    void saveData(const vector<Vehicle>& vehicles);
    void loadData(vector<Vehicle>& vehicles);
    void saveGraphData(const Graph roads[], int roadCount,
                   const Junction junctions[], int junctionCount,
                   const Facility facilities[], int facilityCount);

    void loadGraphData(Graph roads[], int& roadCount,
                   Junction junctions[], int& junctionCount,
                   Facility facilities[], int& facilityCount);
};

#endif