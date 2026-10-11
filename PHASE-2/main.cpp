#include "Vehicle.h"
#include "Graph.h"
#include "TrafficSignal.h"
#include "FileManager.h"
#include <vector>

int main(){

   // ----------------------------VEHICLE MODULE PART------------------------------------------
   int no_of_vehicles;  // Suggested initial maximum: 500

   do {
            cout << "Enter number of vehicles you want to enter: ";
            cin >> no_of_vehicles;

            if (no_of_vehicles <= 0) {
                cout << "Enter a valid number of vehicles.\n";
            }

   } while (no_of_vehicles <= 0 || no_of_vehicles > 500);


    vector<Vehicle> vehicles(no_of_vehicles);     //dynamically allocated memory

    // taking input from user
    for(int i=0 ;i < no_of_vehicles ;i++){

          cout << "\nEnter details for vehicle " << i + 1 << ":\n";
          vehicles[i].inputVehicle();
    }

  

    //displaying all the details of vehicle

    cout << "\n===== All Registered Vehicles =====\n";

    for (int i = 0; i < no_of_vehicles; i++) {
        cout << "\nVehicle " << i + 1 << ":\n";
        vehicles[i].displayVehicle();
    }

     //------------------------------------ROUTE MODULE PART-------------------------------------- 
    
    //-- Added multiple road connections in graph --//
    int no_of_roads;    
    cout << "\nEnter number of roads (max 20): ";
    cin >> no_of_roads;  ;

    if(no_of_roads<1 || no_of_roads>20){
        cout << "Invalid number of roads. Please enter a number between 1 and 20." << endl;
        return 0;
    }

    Graph roads[20];
    for(int i = 0; i < no_of_roads; i++){
        cout << "\nEnter details for road " << (i + 1) << ":" << endl;
        roads[i].inputRoad();
    }
    cout << "\n-- Road details --" << endl;
    for(int i = 0; i < no_of_roads; i++){
        roads[i].displayRoad();
    }

    //--------------------------------------TRAFFIC MODULE PART-----------------------------------
    
    
    TrafficSignal t1;
    FileManager f1;
    
    t1.inputSignal();
    t1.displaySignal();
    
    f1.saveData();

    //--------------------------------------EMERGENCY MODULE PART----------------------------------










    //--------------------------------------FILE MANAGEMENT PART-------------------------------------



    return 0;
}