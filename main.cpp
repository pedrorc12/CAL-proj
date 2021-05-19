#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Graph.h"
#include "graphviewer.h"
#include "GraphReader.h"

#include "Tests/tests.h"

int main() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv);

    test1(graph, gv);
    //test2(graph, gv);

    gv.createWindow(1000, 1000);
    gv.join();

    return 0;
}
