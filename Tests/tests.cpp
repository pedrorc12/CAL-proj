#include "tests.h"

void test1(Graph<int> &graph, GraphViewer &viewer) {

    vector<Donation<int>*> donations;
    donations.push_back(new Donation<int>(graph.findVertex(11), graph.findVertex(21)));

    vector<Volunteer<int>*> volunteers;
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(6)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(7)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(16)));

    Solver<int> solver;

    vector<DonationSolution<int>*> solution = solver.solveProblem(graph, volunteers, donations);

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
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(6)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(10)));
    volunteers.push_back(new Volunteer<int>(0, 1000, graph.findVertex(20)));

    Solver<int> solver;

    vector<DonationSolution<int>*> solution = solver.solveProblem(graph, volunteers, donations);

    for (DonationSolution<int>* ds : solution) {
        ds->printSolution();

        cout << endl << endl;
    }
}