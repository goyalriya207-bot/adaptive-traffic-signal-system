
#include "Vehicle.h"

// Default constructor
Vehicle::Vehicle()
{
    vehicleID = "";
    vehicle_registration_number = "";
    vehicle_Type = "Unknown";
    isEmergencyVehicle = false;
}

void Vehicle::inputVehicle()
{
    // Input vehicle ID
    do
    {
        cout << "\nEnter unique system Vehicle ID: ";
        cin >> vehicleID;

        if (vehicleID.empty())
        {
            cout << "Vehicle ID cannot be empty. Try again.\n";
        }

    } while (vehicleID.empty());

    // Input and validate vehicle type
    do
    {
        cout << "Enter vehicle type "
             << "(Car, Bus, Bike, Bicycle, Truck, "
             << "Ambulance, FireTruck, PoliceVehicle): ";

        cin >> vehicle_Type;

        if (vehicle_Type != "Car" &&
            vehicle_Type != "Bus" &&
            vehicle_Type != "Bike" &&
            vehicle_Type != "Bicycle" &&
            vehicle_Type != "Truck" &&
            vehicle_Type != "Ambulance" &&
            vehicle_Type != "FireTruck" &&
            vehicle_Type != "PoliceVehicle")
        {
            cout << "Invalid vehicle type. Please try again.\n";
        }

    } while (vehicle_Type != "Car" &&
             vehicle_Type != "Bus" &&
             vehicle_Type != "Bike" &&
             vehicle_Type != "Bicycle" &&
             vehicle_Type != "Truck" &&
             vehicle_Type != "Ambulance" &&
             vehicle_Type != "FireTruck" &&
             vehicle_Type != "PoliceVehicle");

    // Bicycle does not require a motor vehicle registration number
    if (vehicle_Type == "Bicycle")
    {
        vehicle_registration_number = "Not Applicable";
        isEmergencyVehicle = false;

        cout << "Bicycle does not require a motor vehicle "
             << "registration number.\n";
        cout << "Normal vehicle registered.\n";
    }
    else
    {
        // Input registration number for other vehicle types
        do
        {
            cout << "Enter vehicle registration number: ";
            cin >> vehicle_registration_number;

            if (vehicle_registration_number.empty())
            {
                cout << "Registration number cannot be empty. "
                     << "Try again.\n";
            }

        } while (vehicle_registration_number.empty());

        // Classify vehicle according to its type
        if (vehicle_Type == "Ambulance" ||
            vehicle_Type == "FireTruck" ||
            vehicle_Type == "PoliceVehicle")
        {
            isEmergencyVehicle = true;
            cout << "Emergency-response vehicle identified.\n";
        }
        else
        {
            isEmergencyVehicle = false;
            cout << "Normal vehicle registered.\n";
        }
    }
}

void Vehicle::displayVehicle()
{
        cout << "\n--- Vehicle Details ---\n";

        cout << "Vehicle ID: "
            << vehicleID << endl;

        cout << "Vehicle Registration Number: "
            << vehicle_registration_number << endl;

        cout << "Vehicle Type: "
            << vehicle_Type << endl;

        cout << "Is Emergency-Response Vehicle: ";

        if (isEmergencyVehicle)
        {
            cout << "Yes" << endl;
        }
        else
        {
            cout << "No" << endl;
        }
}
