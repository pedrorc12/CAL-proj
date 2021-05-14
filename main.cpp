#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Graph.h"
#include "graphviewer.h"
#include "graphReader.h"

int main() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv);

    return 0;
}
