#include "Vehicle.h"
#include "Graph.h"
#include "TrafficSignal.h"
#include "FileManager.h"

int main(){
    Vehicle v1;
    TrafficSignal t1;
    FileManager f1;

    v1.inputVehicle();
    v1.displayVehicle();
    
    //-- Added multiple road connections in graph --//
    int n;
    cout << "\nEnter number of roads (max 20): ";
    cin >> n;

    if(n<1 || n>20){
        cout << "Invalid number of roads. Please enter a number between 1 and 20." << endl;
        return 0;
    }

    Graph roads[20];
    for(int i = 0; i < n; i++){
        cout << "\nEnter details for road " << (i + 1) << ":" << endl;
        roads[i].inputRoad();
    }
    cout << "\n-- Road details --" << endl;
    for(int i = 0; i < n; i++){
        roads[i].displayRoad();
    }
    
    t1.inputSignal();
    t1.displaySignal();
    
    f1.saveData();

    return 0;
}