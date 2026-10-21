
#include "TrafficSignal.h"
#include <cctype>

TrafficSignal::TrafficSignal() {
    signal_ID = 0;
    signal_Status = "Red";
    greenLightDuration = 30;
    redLightDuration = 30;
    yellowLightDuration = 5;
}

void TrafficSignal::inputSignal() {
    cout << "\nEnter Signal ID: ";
    cin >> signal_ID;

    while (signal_ID <= 0) {
        cout << "Signal ID must be positive. Enter again: ";
        cin >> signal_ID;
    }

    do {
        cout << "Enter signal status (Red/Green/Yellow): ";
        cin >> signal_Status;

        for (char &ch : signal_Status) {
            ch = static_cast<char>(
                tolower(static_cast<unsigned char>(ch))
            );
        }

        if (signal_Status == "red" ||
            signal_Status == "green" ||
            signal_Status == "yellow") {

            signal_Status[0] = static_cast<char>(
                toupper(static_cast<unsigned char>(signal_Status[0]))
            );

            break;
        }

        cout << "Invalid signal status! Please try again.\n";

    } while (true);

    cout << "Valid signal status accepted: "
         << signal_Status << endl;
}

void TrafficSignal::displaySignal() {
    cout << "\n--- Traffic Signal Details ---\n";
    cout << "Signal ID: " << signal_ID << endl;
    cout << "Signal Status: " << signal_Status << endl;

    if (signal_Status == "Red") {
        cout << "Red Light Duration: "
             << redLightDuration << " seconds\n";
    }
    else if (signal_Status == "Green") {
        cout << "Green Light Duration: "
             << greenLightDuration << " seconds\n";
    }
    else if (signal_Status == "Yellow") {
        cout << "Yellow Light Duration: "
             << yellowLightDuration << " seconds\n";
    }
}

void TrafficSignal::setSignalDurations() {
    cout << "\nEnter Green Light Duration (seconds): ";
    cin >> greenLightDuration;

    while (greenLightDuration <= 0) {
        cout << "Duration must be positive. Enter again: ";
        cin >> greenLightDuration;
    }

    cout << "Enter Yellow Light Duration (seconds): ";
    cin >> yellowLightDuration;

    while (yellowLightDuration <= 0) {
        cout << "Duration must be positive. Enter again: ";
        cin >> yellowLightDuration;
    }

    cout << "Enter Red Light Duration (seconds): ";
    cin >> redLightDuration;

    while (redLightDuration <= 0) {
        cout << "Duration must be positive. Enter again: ";
        cin >> redLightDuration;
    }

    cout << "\nSignal durations updated successfully!\n";
}

void TrafficSignal::nextSignal() {
    if (signal_Status == "Red") {
        signal_Status = "Green";
    }
    else if (signal_Status == "Green") {
        signal_Status = "Yellow";
    }
    else {
        signal_Status = "Red";
    }

    cout << "\nSignal changed to: "
         << signal_Status << endl;
}

void TrafficSignal::setAdaptiveTiming() {
    int trafficLevel;

    cout << "\nSelect Traffic Level:\n";
    cout << "1. Low Traffic\n";
    cout << "2. Moderate Traffic\n";
    cout << "3. High Traffic\n";
    cout << "Enter choice: ";
    cin >> trafficLevel;

    while (trafficLevel < 1 || trafficLevel > 3) {
        cout << "Invalid choice. Enter 1, 2, or 3: ";
        cin >> trafficLevel;
    }

    if (trafficLevel == 1) {
        greenLightDuration = 20;
        cout << "Low traffic: Green duration set to 20 seconds.\n";
    }
    else if (trafficLevel == 2) {
        greenLightDuration = 40;
        cout << "Moderate traffic: Green duration set to 40 seconds.\n";
    }
    else {
        greenLightDuration = 60;
        cout << "High traffic: Green duration set to 60 seconds.\n";
    }
}

void TrafficSignal::giveEmergencyPriority(bool isEmergency) {
    if (!isEmergency) {
        cout << "\nNo emergency vehicle. Normal signal operation.\n";
        return;
    }

    cout << "\nEmergency vehicle detected!\n";
    cout << "Emergency priority requested.\n";

    if (signal_Status != "Green") {
        signal_Status = "Green";
        cout << "Emergency priority acknowledged.\n";
    }
    else {
        cout << "Signal is already Green. Priority acknowledged.\n";
    }

    cout << "Current signal status: "
         << signal_Status << endl;
}
int TrafficSignal::getSignalID() {
    return signal_ID;
}

string TrafficSignal::getSignalStatus() {
    return signal_Status;
}

int TrafficSignal::getGreenDuration() {
    return greenLightDuration;
}

int TrafficSignal::getRedDuration() {
    return redLightDuration;
}

int TrafficSignal::getYellowDuration() {
    return yellowLightDuration;
}

TrafficSignal& getActiveTrafficSignal()
{
    static TrafficSignal signal;
    return signal;
}

void runTrafficSignalMenu()
{   
    static TrafficSignal* activeSignal = nullptr;
    TrafficSignal& signal = getActiveTrafficSignal();
    int choice;

    do
    {
        cout << "\n===== TRAFFIC SIGNAL MANAGEMENT =====\n";
        cout << "1. Enter Signal Details\n";
        cout << "2. Display Signal\n";
        cout << "3. Set Signal Durations\n";
        cout << "4. Change to Next Signal\n";
        cout << "5. Set Adaptive Timing\n";
        cout << "6. Give Emergency Priority\n";
        cout << "0. Return to Main Menu\n";
        cout << "Enter choice: ";

        cin >> choice;

        switch (choice)
        {
            case 1:
                signal.inputSignal();
                break;

            case 2:
                signal.displaySignal();
                break;

            case 3:
                signal.setSignalDurations();
                break;

            case 4:
                signal.nextSignal();
                break;

            case 5:
                signal.setAdaptiveTiming();
                break;

            case 6:
            {
                char answer;
                cout << "Is an emergency vehicle present? (y/n): ";
                cin >> answer;

                signal.giveEmergencyPriority(
                    answer == 'y' || answer == 'Y'
                );
                break;
            }

            case 0:
                cout << "Returning to Main Menu...\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 0);
}



void requestEmergencySignalPriority()
{ TrafficSignal& signal = getActiveTrafficSignal();
    signal.giveEmergencyPriority(true);
}