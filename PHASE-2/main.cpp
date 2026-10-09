#include "Vehicle.h"
#include "Graph.h"
#include "TrafficSignal.h"
#include "FileManager.h"

int main(){
    Vehicle v1;
    Graph g1;
    TrafficSignal t1;
    FileManager f1;

    v1.inputVehicle();
    v1.displayVehicle();
    
    g1.inputRoad();
    g1.displayRoad();

    t1.inputSignal();
    t1.displaySignal();
    
    f1.saveData();

    return 0;
}