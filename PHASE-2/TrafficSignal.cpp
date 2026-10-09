#include "TrafficSignal.h"
#include<cctype>

TrafficSignal::TrafficSignal() {
    signal_ID = 0;
    signal_Status = "Unknown";
    greenLightDuration = 0;
    redLightDuration = 0;
    yellowLightDuration = 0;
}

void TrafficSignal::inputSignal() {
    cout << "\nEnter signal ID: ";
    cin >> signal_ID;
    cout << "Enter signal status (Red/Yellow/Green): ";
    cin >> signal_Status;

    for(int i = 0; i < signal_Status.length(); i++) {
        signal_Status[i] = tolower(signal_Status[i]);
    }
    if(signal_Status == "green") {
        cout << "Enter green light duration (in seconds): ";
        cin >> greenLightDuration;
    } else if(signal_Status == "red") {
        cout << "Enter red light duration (in seconds): ";
        cin >> redLightDuration;
    } else if(signal_Status == "yellow") {
        cout << "Enter yellow light duration (in seconds): ";
        cin >> yellowLightDuration;
    } else {
        cout << "Invalid signal status entered!" << endl;
    }
}

void TrafficSignal::displaySignal() {
    cout << "\nSignal ID: " << signal_ID << endl;
    cout << "Signal Status: " << signal_Status << endl;
     if(signal_Status == "green") {
        cout << "Green light duration: " << greenLightDuration << " seconds" << endl;
    } else if(signal_Status == "red") {
        cout << "Red light duration: " << redLightDuration << " seconds" << endl;
    } else if(signal_Status == "yellow") {
        cout << "Yellow light duration: " << yellowLightDuration << " seconds" << endl;
    } else {
        cout << "Invalid signal status entered!" << endl;
    }
}