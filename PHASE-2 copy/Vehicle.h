#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle
{
private:
    string vehicleID;
    string vehicle_Type;
    string vehicle_registration_number;
    bool isEmergencyVehicle;   

public:
    Vehicle();

    void inputVehicle();
    void displayVehicle();
    string inputVehicleID();
    string get_vehicle_id() const;  // getter method to access the vehicle id for checking duplication
    string get_vehicle_registration_number() const;
    string get_vehicle_type() const;
    bool is_emergency_vehicle() const;
    void setVehicleData(string id, string type, string registration, bool emergency);

};

#endif