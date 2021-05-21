#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Graph.h"
#include "graphviewer.h"

#include "Tests/tests.h"

int main() {

    Graph<int> graph;
    GraphViewer gv;

    //test1(graph, gv);
    //test2(graph, gv);
    test3(graph, gv);

    gv.createWindow(1000, 1000);
    gv.join();

    return 0;
}
