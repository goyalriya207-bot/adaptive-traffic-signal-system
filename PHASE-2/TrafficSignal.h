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
};
#endif 