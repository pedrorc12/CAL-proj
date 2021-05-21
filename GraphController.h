#ifndef CAL_PROJECT_GRAPHCONTROLLER_H
#define CAL_PROJECT_GRAPHCONTROLLER_H

#include <fstream>
#include <string>
#include "Graph.h"
#include "graphviewer.h"
#include "Volunteer.h"
#include "Donation.h"
#include "DonationSolution.h"

void readGraph(Graph<int> &graph, GraphViewer &gv, string nodesPath, string edgesPath) {

    ifstream nodes;
    ifstream edges;
    string info;
    string digits = "0123456789";
    size_t pos;
    size_t end;


    nodes.open(nodesPath);
    if (!nodes.is_open()) perror("Failed to open file nodes");
    getline(nodes, info);
    double x;
    double y;
    while(getline(nodes, info)){
        pos = info.find_first_of(digits);
        end = info.find_first_of(',');
        int id = std::atoi(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(',', pos);
        x = std::atof(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(')', pos);
        y = std::atof(info.substr(pos, end).c_str());

        //cout << "(id, latitude, longitude) " << "(" << id << ", " << x  << ", " << y << ")" << endl;

        graph.addVertex(id, x, y);

        GraphViewer::Node &node = gv.addNode(id, sf::Vector2f(x, y));
        node.setColor(GraphViewer::YELLOW);
        //node.setLabel(to_string(id));
    }
    gv.setCenter(sf::Vector2f(x, y));
    nodes.close();

    edges.open(edgesPath);
    if (!edges.is_open()) perror("Failed to open file edges");
    getline(edges, info);
    int id = 0;
    while(getline(edges, info)){
        pos = info.find_first_of(digits);
        end = info.find_first_of(',');
        int source = std::atoi(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(')', pos);
        int dest = std::atoi(info.substr(pos, end).c_str());

        //cout << "(source, dest) " << "(" << source <<  ", " << dest << ")" << endl;

        double distance = (graph.findVertex(source)->getDistance(graph.findVertex(dest)));

        graph.addEdge(id, source, dest, distance);

        GraphViewer::Edge &edge = gv.addEdge(id, gv.getNode(source), gv.getNode(dest), GraphViewer::Edge::EdgeType::DIRECTED);
        edge.setColor(GraphViewer::YELLOW);
        edge.setWeight(distance);

        id++;
    }
    edges.close();
}

void colorNodes(GraphViewer &gv, const vector<Volunteer<int>*> &volunteers,
                                 const vector<Donation<int>*> &donations,
                                 const vector<DonationSolution<int>*> &solution) {

    //Color initial volunteers position with blue
    for (Volunteer<int>* volunteer : volunteers) {
        int id = volunteer->getInitialLocation()->getInfo();
        gv.getNode(id).setColor(GraphViewer::BLUE);
    }

    //Color initial donations position with green and final with red;
    for (Donation<int>* donation : donations) {
        int idInitial = donation->getInitialLocation()->getInfo();
        int idFinal = donation->getDestination()->getInfo();
        gv.getNode(idInitial).setColor(GraphViewer::GREEN);
        gv.getNode(idFinal).setColor(GraphViewer::RED);
    }

    //Color the volunteers' path with blue
    for (DonationSolution<int>* ds : solution) {
        for (int i = 0; i < ds->getPath().size() - 1; i++) {
            for (Edge<int>* edge : ds->getPath()[i]->getAdj()) {
                if (edge->getDest() == ds->getPath()[i + 1]) {
                    gv.getEdge(edge->getId()).setColor(GraphViewer::BLUE);
                    break;
                }
            }
        }
    }
}

#endif //CAL_PROJECT_GRAPHCONTROLLER_H
