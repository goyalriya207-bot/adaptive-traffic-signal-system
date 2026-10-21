 
#ifndef TRAFFIC_SIGNAL_H
#define TRAFFIC_SIGNAL_H

#include<iostream>
#include<string>
using namespace std;

class TrafficSignal {
private:
    int signal_ID;
    string signal_Status; //Red, Green, Yellow
    int greenLightDuration;
    int redLightDuration;
    int yellowLightDuration;
public:
    TrafficSignal();
    void inputSignal();
    void displaySignal();
    void setSignalDurations();
    void nextSignal();
    void setAdaptiveTiming();
    void giveEmergencyPriority(bool isEmergency);
    int getSignalID();
    string getSignalStatus();
    int getGreenDuration();
    int getRedDuration();
    int getYellowDuration();



};

void runTrafficSignalMenu();
TrafficSignal& getActiveTrafficSignal();
void requestEmergencySignalPriority();

#endif
