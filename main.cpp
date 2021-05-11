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
    nodes.open("nodes.txt");
    if (!nodes.is_open()) perror("what");
    while(getline(nodes, info)){
        pos = info.find_first_of(digits);
        end = info.find_first_of(',');
        //int ID = std::atoi(info.substr(pos, end).c_str());
        std::cout << "ID : " << info << endl;
    }
    nodes.close();
    return 0;
}
