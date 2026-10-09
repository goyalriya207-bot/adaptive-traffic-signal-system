#include "Graph.h"

Graph::Graph() {
    junction1 = "";
    junction2 = "";
    roadName = "";
    distance = 0;
}

void Graph::inputRoad() {
    cout << "\nEnter junction 1: ";
    cin >> junction1;
    cout << "Enter junction 2: ";
    cin >> junction2;
    cout << "Enter road name: ";
    cin >> roadName;
    cout << "Enter distance between junctions (in km): ";
    cin >> distance;
}

void Graph::displayRoad() {
    cout << "\nRoad Name: " << roadName << endl;
    cout << "Road connection: " << junction1 << " --> " << junction2 << endl;
    cout << "Distance: " << distance << " Km" << endl;
}