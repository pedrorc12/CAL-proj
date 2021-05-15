#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include "Graph.h"
#include "graphviewer.h"
#include "GraphReader.h"
#include "Volunteer.h"
#include "Donation.h"
#include "DonationSolution.h"

int main() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv);

    return 0;
}
