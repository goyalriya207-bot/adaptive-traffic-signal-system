
#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
#include "Graph.h"
#include "TrafficSignal.h"
#include "FileManager.h"

using namespace std;

int main()
{
    // ---------------- VEHICLE MODULE ----------------

    int no_of_vehicles = 0;
    int choice;

    vector<Vehicle> vehicles;  // Dynamically managed memory

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
                            if (enteredID == vehicles[j].get_vehicle_id())
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

                no_of_vehicles = static_cast<int>(vehicles.size());
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
                cout << "Update vehicle details is not implemented yet.\n";
                break;

            // -------- OPTION 6: REMOVE VEHICLE --------
            case 6:
                cout << "Remove vehicle is not implemented yet.\n";
                break;

            // -------- OPTION 7: VEHICLE STATISTICS --------
            case 7:
                cout << "Vehicle statistics are not implemented yet.\n";
                break;

            // -------- OPTION 8: SAVE VEHICLES --------
            case 8:
                cout << "Vehicle-specific saving needs FileManager integration.\n";
                break;

            // -------- OPTION 9: LOAD VEHICLES --------
            case 9:
                cout << "Vehicle-specific loading needs FileManager integration.\n";
                break;

            // -------- EXIT VEHICLE MENU --------
            case 0:
                cout << "Leaving Vehicle Module menu.\n";
                break;

            default:
                cout << "Invalid choice. Please try again.\n";
        }

    } while (choice != 0);


    // ---------------- ROUTE MODULE ----------------
    // Existing Graph module operations can continue here.

    int no_of_roads;

    cout << "\nEnter number of roads (max 20): ";
    cin >> no_of_roads;

    if (no_of_roads < 1 || no_of_roads > 20)
    {
        cout << "Invalid number of roads. "
             << "Please enter a number between 1 and 20.\n";

        return 1;
    }

    Graph roads[20];

    for (int i = 0; i < no_of_roads; i++)
    {
        cout << "\nEnter details for road " << i + 1 << ":\n";
        roads[i].inputRoad();
    }

    cout << "\n===== ROAD DETAILS =====\n";

    for (int i = 0; i < no_of_roads; i++)
    {
        roads[i].displayRoad();
    }


    // ---------------- TRAFFIC SIGNAL MODULE ----------------

    TrafficSignal t1;

    t1.inputSignal();
    t1.displaySignal();


    // ---------------- EMERGENCY RESPONSE MODULE ----------------
    // Add the agreed Emergency Response module operations here.


    // ---------------- FILE MANAGEMENT MODULE ----------------

    FileManager f1;

    // Keep the existing call until FileManager's interface is integrated.
    f1.saveData();

    return 0;
}
