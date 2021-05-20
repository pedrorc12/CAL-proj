#ifndef CAL_PROJECT_GRAPHREADER_H
#define CAL_PROJECT_GRAPHREADER_H

#include <fstream>
#include <string>
#include "Graph.h"
#include "graphviewer.h"

void readGraph(Graph<int> &graph, GraphViewer &gv) {
    gv.setCenter(sf::Vector2f(300, 300));

    ifstream nodes;
    ifstream edges;
    string info;
    string digits = "0123456789";
    size_t pos;
    size_t end;

    //nodes.open("/home/pedro/Projects/CAL/CAL-proj/GridGraphs/4x4/nodes.txt");
    //nodes.open("/home/victor/Documentos/CAL/Projeto/GridGraphs/4x4/nodes.txt");
    nodes.open("/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/nodes_lat_lon_porto.txt");
    if (!nodes.is_open()) perror("Failed to open file nodes");
    getline(nodes, info);
    while(getline(nodes, info)){
        pos = info.find_first_of(digits);
        end = info.find_first_of(',');
        int id = std::atoi(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(',', pos);
        double lati = std::atof(info.substr(pos, end).c_str());
        pos = info.find_first_of(digits, end);
        end = info.find_first_of(')', pos);
        double longi = std::atof(info.substr(pos, end).c_str());

        //cout << "(id, latitude, longitude) " << "(" << id << ", " << lati  << ", " << longi << ")" << endl;

        graph.addVertex(id, lati, longi);

        GraphViewer::Node &node = gv.addNode(id, sf::Vector2f(lati, longi));
        node.setColor(GraphViewer::BLUE);
        node.setLabel(to_string(id));
    }
    nodes.close();

    //edges.open("/home/pedro/Projects/CAL/CAL-proj/GridGraphs/4x4/edges.txt");
    //edges.open("/home/victor/Documentos/CAL/Projeto/GridGraphs/4x4/edges.txt");
    edges.open("/home/victor/Documentos/CAL/Projeto/PortugalMaps/Porto/edges_porto.txt");
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

        graph.addEdge(source, dest, distance);

        GraphViewer::Edge &edge = gv.addEdge(id, gv.getNode(source), gv.getNode(dest), GraphViewer::Edge::EdgeType::DIRECTED);
        edge.setColor(GraphViewer::YELLOW);
        edge.setWeight(distance);

        id++;
    }
    edges.close();

}

#endif //CAL_PROJECT_GRAPHREADER_H
