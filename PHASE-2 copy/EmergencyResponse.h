
#ifndef EMERGENCYRESPONSE_H
#define EMERGENCYRESPONSE_H

#include <iostream>
#include <string>
#include <vector>
#include "Vehicle.h"
using namespace std;

const int MAX_INCIDENTS = 100;

struct Incident
{
    int emergencyID;
    string emergencyType;
    int junctionID;
    int peopleAffected;
    string severity;
    string verificationStatus;
    string incidentStatus;
    int estimatedResponseVehicles;
    string assignedVehicles[10];
    int assignedCount;  
};

class EmergencyResponse
{
private:
    Incident incidents[MAX_INCIDENTS];
    vector<Vehicle>* registeredVehicles = nullptr;
    int totalIncidents;
    int nextEmergencyID;

public:
    EmergencyResponse();
    void setVehicleList(vector<Vehicle>* vehicleList);
    void runMenu();
    void reportEmergency();
    void displayAllIncidents();
    void searchIncident();
    void updateIncident();
    void verifyRejectIncident();
    void estimateResponse();
    void updateIncidentStatus();
    void displayStatistics();
    void assignEmergencyVehicle();
    void unassignEmergencyVehicle();
    void requestEmergencyRoute();
    void requestSignalPriority();
    void saveIncidents();
    void loadIncidents();
};

#endif
