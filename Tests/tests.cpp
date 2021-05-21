#include "tests.h"
#include "../GraphController.h"

void test1() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/GridGraphs/4x4/nodes.txt",
              "/home/victor/Documentos/CAL/Projeto/GridGraphs/4x4/edges.txt"
              );

    /*
    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/GridGraphs/4x4/nodes.txt",
              "/home/pedro/Projects/CAL/CAL-proj/GridGraphs/4x4/edges.txt"
              );
     */

    cout << "Starting the test..." << endl;

    vector<Donation<int>*> donations;
    donations.push_back(new Donation<int>(graph.findVertex(11), graph.findVertex(21)));

    vector<Volunteer<int>*> volunteers;
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(6)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(7)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(16)));

    Solver<int> solver;

    cout << "Solver Created" << endl;

    //vector<DonationSolution<int>*> solution = solver.solveProblemDijkstra(graph, volunteers, donations);
    vector<DonationSolution<int>*> solution = solver.solveProblemFloydWarshall(graph, volunteers, donations);

    cout << "Solution Vector size " << solution.size() << endl;

    for (DonationSolution<int>* ds : solution) {
        ds->printSolution();

        cout << endl << endl;
    }

    colorNodes(gv, volunteers, donations, solution);

    gv.createWindow(1000, 1000);
    gv.join();
}

void test2() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/GridGraphs/4x4/nodes.txt",
              "/home/victor/Documentos/CAL/Projeto/GridGraphs/4x4/edges.txt"
    );

    /*
    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/GridGraphs/4x4/nodes.txt",
              "/home/pedro/Projects/CAL/CAL-proj/GridGraphs/4x4/edges.txt"
              );
     */

    vector<Donation<int>*> donations;
    donations.push_back(new Donation<int>(graph.findVertex(16), graph.findVertex(24)));

    vector<Volunteer<int>*> volunteers;
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(5)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(1)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(10)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(20)));

    Solver<int> solver;

    //vector<DonationSolution<int>*> solution = solver.solveProblemDijkstra(graph, volunteers, donations);
    vector<DonationSolution<int>*> solution = solver.solveProblemFloydWarshall(graph, volunteers, donations);

    cout << "Solution Vector size " << solution.size() << endl;


    for (DonationSolution<int>* ds : solution) {
        ds->printSolution();

        cout << endl << endl;
    }

    colorNodes(gv, volunteers, donations, solution);

    gv.createWindow(1000, 1000);
    gv.join();
}

//Easy test for Porto Map
void test3() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/edges_porto.txt"
    );

    /*
    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/edges_porto.txt"
              );
     */

    vector<Donation<int>*> donations;
    donations.push_back(new Donation<int>(graph.findVertex(560409305), graph.findVertex(560409296)));

    vector<Volunteer<int>*> volunteers;
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(560401003)));

    Solver<int> solver;

    vector<DonationSolution<int>*> solution = solver.solveProblemDijkstra(graph, volunteers, donations);
    //vector<DonationSolution<int>*> solution = solver.solveProblemFloydWarshall(graph, volunteers, donations);

    cout << "Solution Vector size " << solution.size() << endl;


    for (DonationSolution<int>* ds : solution) {
        ds->printSolution();

        cout << endl << endl;
    }

    colorNodes(gv, volunteers, donations, solution);

    gv.createWindow(1000, 1000);
    gv.join();
}

//Easy test for Porto Map
void test4() {

    Graph<int> graph;
    GraphViewer gv;

    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/edges_porto.txt"
    );

    /*
    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/edges_porto.txt"
              );
     */

    Vertex<int>* vertex = graph.findVertex(560409305);

    graph.colorReachableNodes(gv, vertex);

    gv.createWindow(1000, 1000);
    gv.join();
}