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
    //baseStore is tmp value dont forget to change later
    vector<DonationSolution<int>*> solution = solver.solveProblemDijkstra(graph, volunteers, donations, graph.findVertex(130214695));
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
    //baseStore is tmp value dont forget to change later
    vector<DonationSolution<int>*> solution = solver.solveProblemFloydWarshall(graph, volunteers, donations, graph.findVertex(130214695));

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

    /*
    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/edges_porto.txt",
              true
    );
    */

    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/edges_porto.txt",
              true
              );


    vector<Donation<int>*> donations;
    donations.push_back(new Donation<int>(graph.findVertex(122452434), graph.findVertex(1202110497)));
    donations.push_back(new Donation<int>(graph.findVertex(1270263272), graph.findVertex(129548931)));
    donations.push_back(new Donation<int>(graph.findVertex(429432776), graph.findVertex(335561262)));

    vector<Volunteer<int>*> volunteers;
    volunteers.push_back(new Volunteer<int>(14, 18, graph.findVertex(130214695)));
    volunteers.push_back(new Volunteer<int>(14, 15, graph.findVertex(343646769)));
    volunteers.push_back(new Volunteer<int>(15, 17, graph.findVertex(129548931)));

    Solver<int> solver;

    vector<DonationSolution<int>*> solution = solver.solveProblemDijkstra(graph, volunteers, donations, graph.findVertex(475333883));
    //vector<DonationSolution<int>*> solution = solver.solveProblemFloydWarshall(graph, volunteers, donations);

    cout << "Solution Vector size " << solution.size() << endl;


    for (DonationSolution<int>* ds : solution) {
        ds->printSolution();

        cout << endl << endl;
    }

    colorNodes(gv, volunteers, donations, solution);

    for(Donation<int>* donation: donations){
        delete donation;
    }
    for(Volunteer<int>* volunteer: volunteers){
        delete volunteer;
    }

    gv.createWindow(1000, 1000);
    gv.join();
}

//Connectivity test
void test4() {

    Graph<int> graph;
    GraphViewer gv;
    /*
    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/edges_porto.txt"
    );
    */

    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/edges_porto.txt",
              true
              );


    Vertex<int>* vertex = graph.findVertex(474690461);

    graph.colorReachableNodes(gv, vertex);

    gv.createWindow(1000, 1000);
    gv.join();
}
/*
 * Complexity analysis increasing the number of volunteer at each iteration*/
void test5(){
    Graph<int> graph;
    GraphViewer gv;
    /*
    readGraph(graph, gv,
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/edges_porto.txt"
    );
    */

    readGraph(graph, gv,
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/nodes_x_y_porto.txt",
              "/home/pedro/Projects/CAL/CAL-proj/PortugalMaps/Porto/edges_porto.txt",
              true
    );

    vector<Volunteer<int>*> newVolunteers;
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(475347095)));
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(311889489)));
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(497871073)));
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(411831029)));
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(299592374)));
    //newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(414016790)));
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(311886935)));
    //newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(11506653)));
    newVolunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(26122712)));

    vector<Donation<int>*> donations;
    donations.push_back(new Donation<int>(graph.findVertex(122452434), graph.findVertex(1202110497)));

    vector<Volunteer<int>*> volunteers;
    volunteers.push_back(new Volunteer<int>(0, 20, graph.findVertex(343646831)));

    Solver<int> solver;

    for(Volunteer<int>* newVolunteer : newVolunteers){
        cout << "Number of volunteers = " << volunteers.size() << endl;
        vector<DonationSolution<int>*> solution = solver.solveProblemDijkstra(graph, volunteers, donations, graph.findVertex(475333883));
        volunteers.push_back(newVolunteer);
    }


}