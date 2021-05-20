#include "tests.h"

void test1(Graph<int> &graph, GraphViewer &viewer) {

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
}

void test2(Graph<int> &graph, GraphViewer &viewer) {

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
}