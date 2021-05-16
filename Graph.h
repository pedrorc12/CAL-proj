/*
 * Graph.h.
 * For implementation of the minimum cost flow algorithm.
 * See TODOs for code to add/adapt.
 * FEUP, CAL, 2017/18.
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <limits>
#include <iostream>
#include <cmath>
#include "MutablePriorityQueue.h"

using namespace std;

constexpr auto INF = std::numeric_limits<double>::max();

template <class T> class Vertex;
template <class T> class Edge;
template <class T> class Graph;

/*
 * ================================================================================================
 * Class Vertex
 * ================================================================================================
 */

template <class T>
class Vertex {
	T info;
    double latitude;
    double longitude;
    vector<Edge<T>*> adj;		// outgoing edges

	bool visited;  // for path finding
	Edge<T> *path; // for path finding
	double dist;   // for path finding
    int queueIndex = 0; 		// required by MutablePriorityQueue
    int vertexIndex = 0;

	Vertex(T in, double latitude, double longitude);
	void addEdge(Edge<T> *e);

public:
    double getDistance(Vertex<T>* vertex2);
	T getInfo() const;
	vector<Edge<T> *> getAdj() const;
    int getVertexIndex() const;
    void setVertexIndex(const int &index);

    bool operator<(Vertex<T> & vertex) const; // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};

template <class T>
Vertex<T>::Vertex(T in, double latitude, double longitude) : info(in), latitude(latitude), longitude(longitude) {}

template <class T>
double Vertex<T>::getDistance(Vertex<T>* vertex2) {
    return sqrt(pow((latitude - vertex2->latitude), 2) + pow((longitude - vertex2->longitude), 2));
}

template <class T>
void Vertex<T>::addEdge(Edge<T> *e) {
	adj.push_back(e);
}

template <class T>
bool Vertex<T>::operator<(Vertex<T> & vertex) const {
	return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const {
	return this->info;
}

template <class T>
vector<Edge<T> *>  Vertex<T>::getAdj() const {
	return this->adj;
}

template <class T>
int Vertex<T>::getVertexIndex() const {
    return this->vertexIndex;
}

template <class T>
void Vertex<T>::setVertexIndex(const int &index) {
    vertexIndex = index;
}


/* ================================================================================================
 * Class Edge
 * ================================================================================================
 */

template <class T>
class Edge {
	Vertex<T> * orig;
	Vertex<T> * dest;
	double weight;

	Edge(Vertex<T> *o, Vertex<T> *d, double weight);

public:
	friend class Graph<T>;
	friend class Vertex<T>;
};

template <class T>
Edge<T>::Edge(Vertex<T> *o, Vertex<T> *d, double weight):
	orig(o), dest(d), weight(weight) {}



/* ================================================================================================
 * Class Graph
 * ================================================================================================
 */

template <class T>
class Graph {
	vector<Vertex<T> *> vertexSet;
    vector<vector<double>> shortestPathTable;
    vector<vector<Vertex<T>*>> nextVertexTable;
    void resetTable();
    bool needUpdate = true;

public:
    vector<vector<double>> getShortestPathTable() { return shortestPathTable; }
    vector<vector<Vertex<T>*>> getNextVertexTable() { return nextVertexTable; }

	Vertex<T>* findVertex(const T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
    Vertex<T> *addVertex(const T &in, const double &lati, const double &longi);
    Edge<T> *addEdge(const T &source, const T &dest, double weight);
    int getNumVertex() const;

    void dijkstraShortestPath(Vertex<T> *s);
    void floydWarshallShortestPath();
    std::vector<Vertex<T>*> getFloydWarshallPath(Vertex<T>* vertex, Vertex<T>* end) const;
};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in, const double &lati, const double &longi) {
    Vertex<T> *v = findVertex(in);
    if (v != nullptr)
        return v;

    v = new Vertex<T>(in, lati, longi);
    v->setVertexIndex(vertexSet.size());
    vertexSet.push_back(v);

    needUpdate = true;

    return v;
}

template <class T>
Edge<T> * Graph<T>::addEdge(const T &source, const T &dest, double weight) {
	auto s = findVertex(source);
	auto d = findVertex(dest);
	if (s == nullptr || d == nullptr)
		return nullptr;
	Edge<T> *e = new Edge<T>(s, d, weight);
	s->addEdge(e);
    needUpdate = true;

	return e;
}

template <class T>
int Graph<T>::getNumVertex() const {
    return vertexSet.size();
}

template <class T>
Vertex<T>* Graph<T>::findVertex(const T & inf) const {
	for (auto v : vertexSet)
		if (v->info == inf)
			return v;
	return nullptr;
}

template <class T>
vector<Vertex<T> *> Graph<T>::getVertexSet() const {
	return vertexSet;
}

template<class T>
void Graph<T>::dijkstraShortestPath(Vertex<T> *s ) {

    for (Vertex<T>* vertex : vertexSet) {
        vertex->dist = INF;
        vertex->path = nullptr;
        vertex->visited = false;
    }
    
    s->dist = 0;
    MutablePriorityQueue<Vertex<T>> queue;
    queue.insert(s);

    while(!queue.empty()) {
        Vertex<T>* vertex = queue.extractMin();

        for (Edge<T>* edge : vertex->adj) {
            Vertex<T>* vertex_dest = edge->dest;
            if (!(vertex_dest->visited) && (vertex_dest->dist > vertex->dist + edge->weight)) {
                if (vertex_dest->dist == INF) {
                    vertex_dest->dist = vertex->dist + edge->weight;
                    vertex_dest->path = vertex;
                    queue.insert(vertex_dest);
                } else {
                    vertex_dest->dist = vertex->dist + edge->weight;
                    vertex_dest->path = vertex;
                    queue.decreaseKey(vertex_dest);
                }
            }
        }
        vertex->visited = true;
    }
}


template<class T>
void Graph<T>::floydWarshallShortestPath() {

    if (!needUpdate)
        return;

    resetTable();
    for (int k = 0; k < getNumVertex(); k++) {
        for (int i = 0; i < getNumVertex(); i++) {
            for (int j = 0; j < getNumVertex(); j++) {
                if (shortestPathTable[i][j] > shortestPathTable[i][k] + shortestPathTable[k][j]) {
                    shortestPathTable[i][j] = shortestPathTable[i][k] + shortestPathTable[k][j];
                    nextVertexTable[i][j] = nextVertexTable[i][k];
                }
            }
        }
    }
    needUpdate = false;
}

template <class T>
void Graph<T>::resetTable() {

    shortestPathTable = std::vector<std::vector<double>>(getNumVertex(), std::vector<double>(getNumVertex(), INF));
    nextVertexTable = std::vector<std::vector<Vertex<T>*>>(getNumVertex(), std::vector<Vertex<T>*>(getNumVertex(), nullptr));

    for (int i = 0; i < getNumVertex(); i++) {
        for (int j = 0; j < getNumVertex(); j++) {
            if (i == j) {
                shortestPathTable[i][j] = 0;
                nextVertexTable[i][j] = vertexSet[j];
                continue;
            }

            for (Edge<T>* edge : vertexSet[i]->adj) {
                if (edge->dest == vertexSet[j]) {
                    shortestPathTable[i][j] = edge->weight;
                    nextVertexTable[i][j] = vertexSet[j];
                    break;
                }
            }
        }
    }
}

template<class T>
std::vector<Vertex<T>*> Graph<T>::getFloydWarshallPath(Vertex<T>* vertex, Vertex<T>* end) const{
    std::vector<Vertex<T>*> res;

    while (vertex != end) {
        res.push_back(vertex);
        vertex = nextVertexTable[vertex->getVertexIndex()][end->getVertexIndex()];
    }
    res.push_back(end);

    return res;
}

#endif