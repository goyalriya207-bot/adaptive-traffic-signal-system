#include "TrafficSignal.h"

TrafficSignal::TrafficSignal() {
    signal_ID = 0;
    signal_Status = "Unknown";
    greenLightDuration = 0;
}

void TrafficSignal::inputSignal() {
    cout << "\nEnter signal ID: ";
    cin >> signal_ID;
    cout << "Enter signal status (Red/Yellow/Green): ";
    cin >> signal_Status;
    cout << "Enter green light duration (in seconds): ";
    cin >> greenLightDuration;
}

void TrafficSignal::displaySignal() {
    cout << "\nSignal ID: " << signal_ID << endl;
    cout << "Signal Status: " << signal_Status << endl;
    cout << "Green Light Duration: " << greenLightDuration << " seconds" << endl;
}