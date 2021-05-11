#include <iostream>
#include <cstdlib>
#include <fstream>
#include <String>
#include "Graph.h"

int main() {
    ifstream nodes;
    ifstream edges;
    string info;
    string digits = "0123456789";
    size_t pos;
    size_t end;

    Graph<int> graph;
    nodes.open(R"(C:\Users\Pedro\CLionProjects\CAL-project\GridGraphs\4x4\nodes.txt)");
    if (!nodes.is_open()) perror("Failed to open file nodes");
    getline(nodes, info);
    while(getline(nodes, info)){
        pos = info.find_first_of(digits);
        end = info.find_first_of(',');
        int ID = std::atoi(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(',', pos);
        int lati = std::atoi(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(')', pos);
        int longi = std::atoi(info.substr(pos, end).c_str());

        cout << "(ID, latitude, longitude) " << "(" << ID << ", " << lati  << ", " << longi << ")" << endl;

        graph.addVertex(ID);
    }
    nodes.close();

    edges.open(R"(C:\Users\Pedro\CLionProjects\CAL-project\GridGraphs\4x4\edges.txt)");
    if (!edges.is_open()) perror("Failed to open file edges");
    getline(edges, info);
    while(getline(edges, info)){
        pos = info.find_first_of(digits);
        end = info.find_first_of(',');
        int source = std::atoi(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(')', pos);
        int dest = std::atoi(info.substr(pos, end).c_str());

        cout << "(source, dest) " << "(" << source <<  ", " << dest << ")" << endl;


        //add edge
    }
    nodes.close();
    return 0;
}
