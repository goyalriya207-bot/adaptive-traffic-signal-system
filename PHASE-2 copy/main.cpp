

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Graph.h"
#include "TrafficSignal.h"
#include "FileManager.h"
#include "EmergencyResponse.h"


using namespace std;
void runVehicleMenu(vector<Vehicle>& vehicles);
void runVehicleMenu(vector<Vehicle>& vehicles)
{
    int choice;
    FileManager f1;

   do
    {
        cout << "\n========== VEHICLE MODULE MENU ==========\n";
        cout << "1. Add New Vehicle\n";
        cout << "2. Display All Vehicles\n";
        cout << "3. Search Vehicle by ID\n";
        cout << "4. Search Vehicle by Registration Number\n";
        cout << "5. Update Vehicle Details\n";
        cout << "6. Remove Vehicle\n";
        cout << "7. Vehicle Statistics\n";
        cout << "8. Save Vehicle Data\n";
        cout << "9. Load Vehicle Data\n";
        cout << "0. Continue to Main Program\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice)
        {
            // -------- OPTION 1: ADD VEHICLES --------
            case 1:
            {
                int count;

                do
                {
                    cout << "How many vehicles do you want to add? ";
                    cin >> count;

                    if (count <= 0 || count > 500)
                    {
                        cout << "Enter a number between 1 and 500.\n";
                    }

                } while (count <= 0 || count > 500);

                for (int i = 0; i < count; i++)
                {
                    Vehicle newVehicle;
                    string enteredID;
                    bool duplicate;

                    cout << "\nEnter details for new vehicle:\n";

                    // Validate ID before collecting other details
                    do
                    {
                        duplicate = false;

                        enteredID = newVehicle.inputVehicleID();

                        for (int j = 0; j < static_cast<int>(vehicles.size()); j++)
                        {
                            if (enteredID == vehicles[j].get_vehicle_id ())
                            {
                                cout << "Duplicate Vehicle ID! "
                                     << "Please enter another ID.\n";

                                duplicate = true;
                                break;
                            }
                        }

                    } while (duplicate);

                    // Collect type and registration details
                    newVehicle.inputVehicle();

                    // Store the completed vehicle
                    vehicles.push_back(newVehicle);

                    cout << "Vehicle added successfully.\n";
                }

              
                break;
            }

            // -------- OPTION 2: DISPLAY VEHICLES --------
            case 2:
            {
                if (vehicles.empty())
                {
                    cout << "No vehicles have been added yet.\n";
                }
                else
                {
                    cout << "\n===== ALL REGISTERED VEHICLES =====\n";

                    for (int i = 0; i < static_cast<int>(vehicles.size()); i++)
                    {
                        cout << "\nVehicle " << i + 1 << ":\n";
                        vehicles[i].displayVehicle();
                    }
                }

                break;
            }

            // -------- OPTION 3: SEARCH BY ID --------
        
            case 3:
            {
                string searchID;
                bool found = false;

                cout << "Enter Vehicle ID to search: ";
                cin >> searchID;

                for (int i = 0; i < static_cast<int>(vehicles.size()); i++)
                {
                    if (searchID == vehicles[i].get_vehicle_id())
                    {
                        cout << "\nVehicle found!\n";
                        vehicles[i].displayVehicle();
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Vehicle ID not found.\n";
                }

                break;
            }

               

            // -------- OPTION 4: SEARCH BY REGISTRATION --------
           
            case 4:
            {
                string searchRegistration;
                bool found = false;

                cout << "Enter Vehicle Registration Number to search: ";
                cin >> searchRegistration;

                for (int i = 0; i < static_cast<int>(vehicles.size()); i++)
                {
                    if (searchRegistration == vehicles[i].get_vehicle_registration_number())
                    {
                        cout << "\nVehicle found!\n";
                        vehicles[i].displayVehicle();
                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Vehicle registration number not found.\n";
                }

                break;
            }


            // -------- OPTION 5: UPDATE VEHICLE --------
            
            case 5:
            {
                string searchID;
                bool found = false;

                cout << "Enter Vehicle ID to update: ";
                cin >> searchID;

                for (int i = 0; i < static_cast<int>(vehicles.size()); i++)
                {
                    if (searchID == vehicles[i].get_vehicle_id())
                    {
                        cout << "\nVehicle found! Existing details:\n";
                        vehicles[i].displayVehicle();

                        cout << "\nEnter updated vehicle details:\n";
                        vehicles[i].inputVehicle();

                        cout << "\nVehicle details updated successfully.\n";

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Vehicle ID not found. Cannot update details.\n";
                }

                break;
            }


            // -------- OPTION 6: REMOVE VEHICLE --------
             
            case 6:
            {
                string searchID;
                char confirmation;
                bool found = false;

                cout << "Enter Vehicle ID to remove: ";
                cin >> searchID;

                for (int i = 0; i < static_cast<int>(vehicles.size()); i++)
                {
                    if (searchID == vehicles[i].get_vehicle_id())
                    {
                        cout << "\nVehicle found:\n";
                        vehicles[i].displayVehicle();

                        cout << "\nAre you sure you want to remove this vehicle? (Y/N): ";
                        cin >> confirmation;

                        if (confirmation == 'Y' || confirmation == 'y')
                        {
                            vehicles.erase(vehicles.begin() + i);
                            cout << "Vehicle removed successfully.\n";
                        }
                        else
                        {
                            cout << "Vehicle removal cancelled.\n";
                        }

                        found = true;
                        break;
                    }
                }

                if (!found)
                {
                    cout << "Vehicle ID not found. Cannot remove vehicle.\n";
                }

                break;
            }

            // -------- OPTION 7: VEHICLE STATISTICS --------
             
            case 7:
            {
                int totalVehicles = static_cast<int>(vehicles.size());
                int normalVehicles = 0;
                int emergencyVehicles = 0;

                int carCount = 0;
                int busCount = 0;
                int bikeCount = 0;
                int bicycleCount = 0;
                int truckCount = 0;
                int ambulanceCount = 0;
                int fireTruckCount = 0;
                int policeVehicleCount = 0;

                if (vehicles.empty())
                {
                    cout << "No vehicles available for statistics.\n";
                    break;
                }

                for (int i = 0; i < totalVehicles; i++)
                {
                    if (vehicles[i].get_vehicle_type() == "Car")
                        carCount++;
                    else if (vehicles[i].get_vehicle_type() == "Bus")
                        busCount++;
                    else if (vehicles[i].get_vehicle_type() == "Bike")
                        bikeCount++;
                    else if (vehicles[i].get_vehicle_type() == "Bicycle")
                        bicycleCount++;
                    else if (vehicles[i].get_vehicle_type() == "Truck")
                        truckCount++;
                    else if (vehicles[i].get_vehicle_type() == "Ambulance")
                        ambulanceCount++;
                    else if (vehicles[i].get_vehicle_type() == "FireTruck")
                        fireTruckCount++;
                    else if (vehicles[i].get_vehicle_type() == "PoliceVehicle")
                        policeVehicleCount++;

                    if (vehicles[i].is_emergency_vehicle())
                        emergencyVehicles++;
                    else
                        normalVehicles++;
                }

                cout << "\n===== VEHICLE STATISTICS =====\n";
                cout << "Total Vehicles: " << totalVehicles << '\n';
                cout << "Normal Vehicles: " << normalVehicles << '\n';
                cout << "Emergency Vehicles: " << emergencyVehicles << '\n';

                cout << "\n--- Vehicle Type Breakdown ---\n";
                cout << "Cars: " << carCount << '\n';
                cout << "Buses: " << busCount << '\n';
                cout << "Bikes: " << bikeCount << '\n';
                cout << "Bicycles: " << bicycleCount << '\n';
                cout << "Trucks: " << truckCount << '\n';
                cout << "Ambulances: " << ambulanceCount << '\n';
                cout << "Fire Trucks: " << fireTruckCount << '\n';
                cout << "Police Vehicles: " << policeVehicleCount << '\n';

                break;
            }
 

            // -------- OPTION 8: SAVE VEHICLES --------
            
           case 8:
            {
                f1.saveData(vehicles);
                break;
            }


            // -------- OPTION 9: LOAD VEHICLES --------
          
            case 9:
            {
                f1.loadData(vehicles);
                break;
            }

            // -------- EXIT VEHICLE MENU --------
            case 0:
                cout << "Leaving Vehicle Module menu.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);
}


void runFileManagementMenu(vector<Vehicle>& vehicles)
{
    FileManager fileManager;
    int choice;

    do
    {
        cout << "\n===== FILE MANAGEMENT =====\n";
        cout << "1. Save Vehicle Data\n";
        cout << "2. Load Vehicle Data\n";
        cout << "3. Save Graph Data\n";
        cout << "4. Load Graph Data\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                fileManager.saveData(vehicles);
                break;

            case 2:
                fileManager.loadData(vehicles);
                break;

           case 3:
                saveCurrentGraphData();
                break;

            case 4:
                loadCurrentGraphData();
                break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}


int main()
{
    
    vector<Vehicle> vehicles;
    EmergencyResponse emergency;
    emergency.setVehicleList(&vehicles);

    FileManager fileManager;
    fileManager.loadData(vehicles);
    int choice;


    do {
        cout << "\n===== ADAPTIVE TRAFFIC SYSTEM =====\n";
        cout << "1. Vehicle Management\n";
        cout << "2. Graph & Route Planning\n";
        cout << "3. Emergency Response\n";
        cout << "4. Traffic Signal Management\n";
        cout << "5. File Management\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";

        cin >> choice;

        switch (choice) {
            case 1:
                runVehicleMenu(vehicles);
                break;

            case 2:
                runGraphMenu();
                break;

            case 3:
                emergency.runMenu();
                break;
            
            case 4:
                runTrafficSignalMenu();
                break;

            case 5:
               runFileManagementMenu(vehicles);
               break;
            case 0:
                cout << "Exiting system...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);

    return 0;
}
