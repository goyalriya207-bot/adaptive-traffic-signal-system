
#include "EmergencyResponse.h"
#include <fstream>
#include "Graph.h"
#include "TrafficSignal.h"
#include "Vehicle.h"
#include <vector>

// Constructor
EmergencyResponse::EmergencyResponse()
{
    totalIncidents = 0;
    nextEmergencyID = 1;
}


void EmergencyResponse::setVehicleList(vector<Vehicle>* vehicleList)
{
    registeredVehicles = vehicleList;
}


// Main Emergency Module Menu
void EmergencyResponse::runMenu()
{
    int choice;

    do
    {
        cout << "\n===== EMERGENCY RESPONSE MODULE =====\n";
        cout << "1. Report New Emergency\n";
        cout << "2. Display All Incidents\n";
        cout << "3. Search Incident by ID\n";
        cout << "4. Update Incident Details\n";
        cout << "5. Verify / Reject Report\n";
        cout << "6. Estimate Response Requirements\n";
        cout << "7. Update Incident Status\n";
        cout << "8. Display Statistics\n";
        cout << "9. Assign Emergency Vehicle\n";
        cout << "10. Unassign Emergency Vehicle\n";
        cout << "11. Request Emergency Route\n";
        cout << "12. Request Signal Priority\n";
        cout << "13. Save Incident Data\n";
        cout << "14. Load Incident Data\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                reportEmergency();
                break;

            case 2:
                displayAllIncidents();
                break;

            case 3:
                searchIncident();
                break;

            case 4:
                updateIncident();
                break;

            case 5:
                verifyRejectIncident();
                break;

            case 6:
                estimateResponse();
                break;

            case 7:
                updateIncidentStatus();
                break;

            case 8:
                displayStatistics();
                break;
            
            case 9:
                 assignEmergencyVehicle();
                 break;

            case 10:
                  unassignEmergencyVehicle();
                  break;

            case 11:
                  requestEmergencyRoute();
                  break;

            case 12:
                  requestSignalPriority();
                  break;

            case 13:
                  saveIncidents();
                   break;

            case 14:
                  loadIncidents();
                   break;

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}

// 1. Report New Emergency
void EmergencyResponse::reportEmergency()
{
    if (totalIncidents >= MAX_INCIDENTS)
    {
        cout << "Maximum incident limit reached.\n";
        return;
    }

    Incident newIncident;

    newIncident.emergencyID = nextEmergencyID++;

    cout << "\nSelect Emergency Type:\n";
    cout << "1. Earthquake\n";
    cout << "2. Medical Emergency\n";
    cout << "3. Fire Breakdown\n";
    cout << "Enter choice: ";

    int typeChoice;
    cin >> typeChoice;

    if (typeChoice == 1)
        newIncident.emergencyType = "Earthquake";
    else if (typeChoice == 2)
        newIncident.emergencyType = "Medical Emergency";
    else if (typeChoice == 3)
        newIncident.emergencyType = "Fire Breakdown";
    else
    {
        cout << "Invalid emergency type.\n";
        return;
    }

    cout << "Enter Junction ID (1-15): ";
    cin >> newIncident.junctionID;

    if (newIncident.junctionID < 1 ||
        newIncident.junctionID > 15)
    {
        cout << "Invalid Junction ID.\n";
        return;
    }

    cout << "Enter number of people affected: ";
    cin >> newIncident.peopleAffected;

    if (newIncident.peopleAffected < 0)
    {
        cout << "People affected cannot be negative.\n";
        return;
    }

    cout << "Enter Severity (Low / Medium / High): ";
    cin >> newIncident.severity;

    if (newIncident.severity != "Low" &&
        newIncident.severity != "Medium" &&
        newIncident.severity != "High")
    {
        cout << "Invalid severity.\n";
        return;
    }

    newIncident.verificationStatus = "Pending";
    newIncident.incidentStatus = "Reported";
    newIncident.estimatedResponseVehicles = 0;
    newIncident.assignedCount = 0;

    incidents[totalIncidents] = newIncident;
    totalIncidents++;

    cout << "\nEmergency reported successfully!\n";
    cout << "Generated Emergency ID: "
         << newIncident.emergencyID << endl;
}

// 2. Display All Incidents
void EmergencyResponse::displayAllIncidents()
{
    if (totalIncidents == 0)
    {
        cout << "No incidents found.\n";
        return;
    }

    int i;

    for ( i = 0; i < totalIncidents; i++)
    {
        cout << "\n--- Incident " << i + 1 << " ---\n";
        cout << "Emergency ID: "
             << incidents[i].emergencyID << endl;
        cout << "Type: "
             << incidents[i].emergencyType << endl;
        cout << "Junction: "
             << incidents[i].junctionID << endl;
        cout << "People Affected: "
             << incidents[i].peopleAffected << endl;
        cout << "Severity: "
             << incidents[i].severity << endl;
        cout << "Verification: "
             << incidents[i].verificationStatus << endl;
        cout << "Status: "
             << incidents[i].incidentStatus << endl;
        cout << "Estimated Response Vehicles: "
             << incidents[i].estimatedResponseVehicles << endl;
    }

        cout << "Assigned Vehicles: "
             << incidents[i].assignedCount << endl;

            for (int j = 0; j < incidents[i].assignedCount; j++)
            {
            cout << incidents[i].assignedVehicles[j] << endl;
             }
}

// 3. Search Incident by ID
void EmergencyResponse::searchIncident()
{
    int id;
    bool found = false;

    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            cout << "\nIncident Found!\n";
            cout << "Type: "
                 << incidents[i].emergencyType << endl;
            cout << "Junction: "
                 << incidents[i].junctionID << endl;
            cout << "Severity: "
                 << incidents[i].severity << endl;
            cout << "Verification: "
                 << incidents[i].verificationStatus << endl;
            cout << "Status: "
                 << incidents[i].incidentStatus << endl;

            found = true;
            break;
        }
    }

    if (!found)
        cout << "Incident ID not found.\n";
}

// 4. Update Incident Details
void EmergencyResponse::updateIncident()
{
    int id;
    cout << "Enter Emergency ID to update: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            cout << "Enter new number of people affected: ";
            int people;
            cin >> people;

            if (people < 0)
            {
                cout << "Invalid number.\n";
                return;
            }

            cout << "Enter new severity (Low / Medium / High): ";
            string severity;
            cin >> severity;

            if (severity != "Low" &&
                severity != "Medium" &&
                severity != "High")
            {
                cout << "Invalid severity.\n";
                return;
            }

            incidents[i].peopleAffected = people;
            incidents[i].severity = severity;

            cout << "Incident details updated.\n";
            return;
        }
    }

    cout << "Incident ID not found.\n";
}

// 5. Verify / Reject Incident Report
void EmergencyResponse::verifyRejectIncident()
{
    int id;
    int choice;

    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            cout << "1. Verify Report\n";
            cout << "2. Reject Report\n";
            cout << "Enter choice: ";
            cin >> choice;

            if (choice == 1)
            {
                incidents[i].verificationStatus = "Verified";
                cout << "Report verified.\n";
            }
            else if (choice == 2)
            {
                incidents[i].verificationStatus = "Rejected";
                incidents[i].incidentStatus = "Rejected";
                incidents[i].estimatedResponseVehicles = 0;
                cout << "Report rejected.\n";
            }
            else
            {
                cout << "Invalid choice.\n";
            }

            return;
        }
    }

    cout << "Incident ID not found.\n";
}

// 6. Estimate Response Requirements
void EmergencyResponse::estimateResponse()
{
    int id;
    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            if (incidents[i].verificationStatus != "Verified")
            {
                cout << "Verify the incident before estimation.\n";
                return;
            }

            int vehicles = 1;

            if (incidents[i].severity == "Medium")
                vehicles = 2;
            else if (incidents[i].severity == "High")
                vehicles = 3;

            if (incidents[i].peopleAffected >= 10)
                vehicles++;

            incidents[i].estimatedResponseVehicles = vehicles;

            cout << "Estimated emergency-response vehicles: "
                 << vehicles << endl;
            cout << "This is a simulation estimate.\n";
            return;
        }
    }

    cout << "Incident ID not found.\n";
}

// 7. Update Incident Status
void EmergencyResponse::updateIncidentStatus()
{
    int id;
    int choice;

    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            if (incidents[i].verificationStatus != "Verified")
            {
                cout << "Only verified incidents can progress.\n";
                return;
            }

            cout << "1. Assigned\n";
            cout << "2. Responding\n";
            cout << "3. Resolved\n";
            cout << "Enter new status: ";
            cin >> choice;

            if (choice == 1)
                incidents[i].incidentStatus = "Assigned";
            else if (choice == 2 &&
                     incidents[i].incidentStatus == "Assigned")
                incidents[i].incidentStatus = "Responding";
            else if (choice == 3 &&
                     incidents[i].incidentStatus == "Responding")
                incidents[i].incidentStatus = "Resolved";
            else
            {
                cout << "Invalid status choice or status transition.\n";
                return;
            }

            cout << "Incident status updated to "
                 << incidents[i].incidentStatus << ".\n";
            return;
        }
    }

    cout << "Incident ID not found.\n";
}

// 8. Display Incident Statistics
void EmergencyResponse::displayStatistics()
{
    int low = 0, medium = 0, high = 0;
    int pending = 0, verified = 0, rejected = 0;
    int totalPeople = 0;
    int totalVehicles = 0;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].severity == "Low")
            low++;
        else if (incidents[i].severity == "Medium")
            medium++;
        else if (incidents[i].severity == "High")
            high++;

        if (incidents[i].verificationStatus == "Pending")
            pending++;
        else if (incidents[i].verificationStatus == "Verified")
            verified++;
        else if (incidents[i].verificationStatus == "Rejected")
            rejected++;

        totalPeople += incidents[i].peopleAffected;
        totalVehicles += incidents[i].estimatedResponseVehicles;
    }

    cout << "\n===== INCIDENT STATISTICS =====\n";
    cout << "Total incidents: " << totalIncidents << endl;
    cout << "Low severity: " << low << endl;
    cout << "Medium severity: " << medium << endl;
    cout << "High severity: " << high << endl;
    cout << "Pending reports: " << pending << endl;
    cout << "Verified reports: " << verified << endl;
    cout << "Rejected reports: " << rejected << endl;
    cout << "Total people affected: " << totalPeople << endl;
    cout << "Total estimated vehicles: " << totalVehicles << endl;
}


void EmergencyResponse::assignEmergencyVehicle()
{
    if (registeredVehicles == nullptr || registeredVehicles->empty())
    {
        cout << "No registered vehicles available. Add and load vehicles first.\n";
        return;
    }

    int id;
    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            if (incidents[i].verificationStatus != "Verified")
            {
                cout << "Verify the incident first.\n";
                return;
            }

            if (incidents[i].assignedCount >= 10)
            {
                cout << "Maximum vehicles assigned to this incident.\n";
                return;
            }

            cout << "\n--- Available Emergency Vehicles ---\n";
            bool found = false;

            for (size_t j = 0; j < registeredVehicles->size(); j++)
            {
                Vehicle& v = (*registeredVehicles)[j];

                if (v.is_emergency_vehicle())
                {
                    found = true;
                    cout << "Vehicle ID: " << v.get_vehicle_id()
                         << " | Type: " << v.get_vehicle_type()
                         << " | Registration: "
                         << v.get_vehicle_registration_number() << '\n';
                }
            }

            if (!found)
            {
                cout << "No registered emergency vehicles found.\n";
                return;
            }

            string vehicleID;
            cout << "Enter Vehicle ID to assign: ";
            cin >> vehicleID;

            for (size_t j = 0; j < registeredVehicles->size(); j++)
            {
                Vehicle& v = (*registeredVehicles)[j];

                if (v.get_vehicle_id() == vehicleID)
                {
                    if (!v.is_emergency_vehicle())
                    {
                        cout << "This is not an emergency vehicle.\n";
                        return;
                    }

                    string registration =
                        v.get_vehicle_registration_number();

                    for (int k = 0; k < incidents[i].assignedCount; k++)
                    {
                        if (incidents[i].assignedVehicles[k] == registration)
                        {
                            cout << "This vehicle is already assigned to this incident.\n";
                            return;
                        }
                    }

                    incidents[i].assignedVehicles[
                        incidents[i].assignedCount
                    ] = registration;

                    incidents[i].assignedCount++;
                    incidents[i].incidentStatus = "Assigned";

                    cout << v.get_vehicle_type()
                         << " (" << registration
                         << ") assigned successfully!\n";
                    return;
                }
            }

            cout << "Vehicle ID not found.\n";
            return;
        }
    }

    cout << "Emergency ID not found.\n";
}


void EmergencyResponse::requestEmergencyRoute()
{
    int id;
    int destinationJunction;

    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            if (incidents[i].verificationStatus != "Verified")
            {
                cout << "Verify the incident first.\n";
                return;
            }

            cout << "Incident junction: "
                 << incidents[i].junctionID << endl;

            cout << "Enter destination junction (1-15): ";
            cin >> destinationJunction;

            if (destinationJunction < 1 ||
                destinationJunction > 15)
            {
                cout << "Invalid destination junction.\n";
                return;
            }

            if (destinationJunction == incidents[i].junctionID)
            {
                cout << "Destination is the same as the incident junction.\n";
                return;
            }

            cout << "Emergency route request recorded.\n";
            cout << "Source junction: "
                 << incidents[i].junctionID << endl;
            cout << "Destination junction: "
                 << destinationJunction << endl;

            findEmergencyRoute(
                incidents[i].junctionID,
                destinationJunction
            );
            return;
        }
    }

    cout << "Emergency ID not found.\n";
}


void EmergencyResponse::requestSignalPriority()
{
    int id;

    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            if (incidents[i].verificationStatus != "Verified")
            {
                cout << "Verify the incident first.\n";
                return;
            }

            if (incidents[i].assignedCount == 0)
            {
                cout << "Assign an emergency vehicle first.\n";
                return;
            }

            cout << "\nSignal Priority Request Created!\n";
            cout << "Emergency ID: "
                 << incidents[i].emergencyID << endl;
            cout << "Junction ID: "
                 << incidents[i].junctionID << endl;
            cout << "Severity: "
                 << incidents[i].severity << endl;
             requestEmergencySignalPriority();

            return;
        }
    }

    cout << "Emergency ID not found.\n";
}


void EmergencyResponse::unassignEmergencyVehicle()
{
    int id;
    string registrationNumber;

    cout << "Enter Emergency ID: ";
    cin >> id;

    for (int i = 0; i < totalIncidents; i++)
    {
        if (incidents[i].emergencyID == id)
        {
            if (incidents[i].assignedCount == 0)
            {
                cout << "No vehicles are assigned to this incident.\n";
                return;
            }

            cout << "\n--- Assigned Vehicles ---\n";

            for (int j = 0; j < incidents[i].assignedCount; j++)
            {
                cout << j + 1 << ". "
                     << incidents[i].assignedVehicles[j] << '\n';
            }

            cout << "Enter registration number to unassign: ";
            cin >> registrationNumber;

            for (int j = 0; j < incidents[i].assignedCount; j++)
            {
                if (incidents[i].assignedVehicles[j] == registrationNumber)
                {
                    for (int k = j; k < incidents[i].assignedCount - 1; k++)
                    {
                        incidents[i].assignedVehicles[k] =
                            incidents[i].assignedVehicles[k + 1];
                    }

                    incidents[i].assignedCount--;

                    incidents[i].assignedVehicles[
                        incidents[i].assignedCount
                    ] = "";

                    if (incidents[i].assignedCount == 0)
                    {
                        incidents[i].incidentStatus = "Verified";
                    }

                    cout << "Vehicle unassigned successfully!\n";
                    return;
                }
            }

            cout << "Registration number not found for this incident.\n";
            return;
        }
    }

    cout << "Emergency ID not found.\n";
}



void EmergencyResponse::saveIncidents()
{
    ofstream file("emergency_data.txt");

    if (!file)
    {
        cout << "Error opening file for saving.\n";
        return;
    }

    file << totalIncidents << endl;
    file << nextEmergencyID << endl;

    for (int i = 0; i < totalIncidents; i++)
    {
        file << incidents[i].emergencyID << endl;
        file << incidents[i].emergencyType << endl;
        file << incidents[i].junctionID << endl;
        file << incidents[i].peopleAffected << endl;
        file << incidents[i].severity << endl;
        file << incidents[i].verificationStatus << endl;
        file << incidents[i].incidentStatus << endl;
        file << incidents[i].estimatedResponseVehicles << endl;

        file << incidents[i].assignedCount << endl;

        for (int j = 0; j < incidents[i].assignedCount; j++)
        {
            file << incidents[i].assignedVehicles[j] << endl;
        }
    }

    file.close();

    cout << "Incident data saved successfully.\n";
}


void EmergencyResponse::loadIncidents()
{
    ifstream file("emergency_data.txt");

    if (!file)
    {
        cout << "No saved incident file found.\n";
        return;
    }

    int savedCount;
    int savedNextID;

    if (!(file >> savedCount >> savedNextID))
    {
        cout << "Invalid saved data.\n";
        return;
    }

    file.ignore(1000, '\n');

    if (savedCount < 0 || savedCount > MAX_INCIDENTS)
    {
        cout << "Invalid incident count in file.\n";
        return;
    }

    Incident loadedIncidents[MAX_INCIDENTS];

    for (int i = 0; i < savedCount; i++)
    {
        if (!(file >> loadedIncidents[i].emergencyID))
        {
            cout << "Error reading incident data.\n";
            return;
        }

        file.ignore(1000, '\n');

        getline(file, loadedIncidents[i].emergencyType);

        if (!(file >> loadedIncidents[i].junctionID
                   >> loadedIncidents[i].peopleAffected))
        {
            cout << "Error reading incident data.\n";
            return;
        }

        file.ignore(1000, '\n');

        getline(file, loadedIncidents[i].severity);
        getline(file, loadedIncidents[i].verificationStatus);
        getline(file, loadedIncidents[i].incidentStatus);

        if (!(file >> loadedIncidents[i].estimatedResponseVehicles
                   >> loadedIncidents[i].assignedCount))
        {
            cout << "Error reading incident data.\n";
            return;
        }

        if (loadedIncidents[i].assignedCount < 0 ||
            loadedIncidents[i].assignedCount > 10)
        {
            cout << "Invalid assigned vehicle count.\n";
            return;
        }

        file.ignore(1000, '\n');

        for (int j = 0; j < loadedIncidents[i].assignedCount; j++)
        {
            getline(file, loadedIncidents[i].assignedVehicles[j]);

            if (!file)
            {
                cout << "Error reading assigned vehicles.\n";
                return;
            }
        }
    }

    file.close();

    for (int i = 0; i < savedCount; i++)
    {
        incidents[i] = loadedIncidents[i];
    }

    totalIncidents = savedCount;
    nextEmergencyID = savedNextID;

    cout << "Incident data loaded successfully.\n";
}


