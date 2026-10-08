#include "Vehicle.h"

Vehicle::Vehicle() {
    vehicle_registration_number = 0;
    vehicle_Type = "Unknown";
}

void Vehicle::inputVehicle() {
    cout << "Enter vehicle registration number: ";
    cin >> vehicle_registration_number;
    cout << "Enter vehicle type: ";
    cin >> vehicle_Type;
}

void Vehicle::displayVehicle() {
    cout << "Vehicle Registration Number: " << vehicle_registration_number << endl;
    cout << "Vehicle Type: " << vehicle_Type << endl;
}