#include "Graph.h"

Graph::Graph() {
    junction1 = "";
    junction2 = "";
    roadName = "";
}

void Graph::inputRoad() {
    cout << "\nEnter junction 1: ";
    cin >> junction1;
    cout << "Enter junction 2: ";
    cin >> junction2;
    cout << "Enter road name: ";
    cin >> roadName;
}

void Graph::displayRoad() {
    cout << "\nRoad Name: " << roadName << endl;
    cout << "Road connection: " << junction1 << " --> " << junction2 << endl;
}