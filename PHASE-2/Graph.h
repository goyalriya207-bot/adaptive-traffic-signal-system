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
    public:
        Graph();
        void inputRoad();
        void displayRoad();
};

#endif