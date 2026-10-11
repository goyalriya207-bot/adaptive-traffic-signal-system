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
};

#endif