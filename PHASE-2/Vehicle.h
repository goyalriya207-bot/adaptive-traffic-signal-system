#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <string>
using namespace std;

class Vehicle {
    private:
        string vehicle_Type;
        int vehicle_registration_number;
        bool isEmergencyVehicle;
    public:
        Vehicle();
        void inputVehicle();
        void displayVehicle();
};

#endif