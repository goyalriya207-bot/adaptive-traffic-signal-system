#ifndef GRAPH_H
#define GRAPH_H

#include<iostream>
#include<string>
using namespace std;

class Graph{
    private:
        string junction1;
        string junction2;
        string roadName;
        int distance;
    public:
        Graph();
        void inputRoad();
        void displayRoad();
};

#endif