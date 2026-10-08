#include "Vehicle.h"

Vehicle::Vehicle() {
    vehicle_registration_number = 0;
    vehicle_Type = "Unknown";
    isEmergencyVehicle = false;
}

void Vehicle::inputVehicle() {
    cout << "\nEnter vehicle registration number: ";
    cin >> vehicle_registration_number;
    cout << "Enter vehicle type: ";
    cin >> vehicle_Type;
    cout << "Is this an emergency vehicle? (1 for yes, 0 for no): ";
    cin >> isEmergencyVehicle;
}

void Vehicle::displayVehicle() {
    cout << "\nVehicle Registration Number: " << vehicle_registration_number << endl;
    cout << "Vehicle Type: " << vehicle_Type << endl;
    cout << "Is Emergency Vehicle: ";
    if(isEmergencyVehicle) 
        cout << "Yes" << endl;
    else
        cout << "No" << endl;
}