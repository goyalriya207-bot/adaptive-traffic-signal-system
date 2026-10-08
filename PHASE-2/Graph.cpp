#include "Graph.h"

Graph::Graph() {
    junction1 = "";
    junction2 = "";
}

void Graph::inputRoad() {
    cout << "\nEnter junction 1: ";
    cin >> junction1;
    cout << "Enter junction 2: ";
    cin >> junction2;
}

void Graph::displayRoad() {
    cout << "Road connection: " << junction1 << " --> " << junction2 << endl;
}