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
	vector<Edge<T> *> outgoing;
	vector<Edge<T> *> incoming;

	bool visited;  // for path finding
	Edge<T> *path; // for path finding
	double dist;   // for path finding
    int queueIndex = 0; 		// required by MutablePriorityQueue
    int vertexIndex = 0;

	Vertex(T in);
	Vertex(T in, double latitude, double longitude);
	void addEdge(Edge<T> *e);

public:
    double getDistance(Vertex<T>* vertex2);
	T getInfo() const;
	vector<Edge<T> *> getIncoming() const;
	vector<Edge<T> *> getOutgoing() const;
    int getVertexIndex() const;
    void setVertexIndex(const int &index);

    bool operator<(Vertex<T> & vertex) const; // required by MutablePriorityQueue
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};


template <class T>
Vertex<T>::Vertex(T in): info(in) {}

template <class T>
Vertex<T>::Vertex(T in, double latitude, double longitude) : info(in), latitude(latitude), longitude(longitude) {}

template <class T>
double Vertex<T>::getDistance(Vertex<T>* vertex2) {
    return sqrt(pow((latitude - vertex2->latitude), 2) + pow((longitude - vertex2->longitude), 2));
}

template <class T>
void Vertex<T>::addEdge(Edge<T> *e) {
	outgoing.push_back(e);
	e->dest->incoming.push_back(e);
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
vector<Edge<T> *>  Vertex<T>::getIncoming() const {
	return this->incoming;
}

template <class T>
vector<Edge<T> *>  Vertex<T>::getOutgoing() const {
	return this->outgoing;
}

template <class T>
int Vertex<T>::getVertexIndex() const {
    return vertexIndex;
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
    std::vector<std::vector<double>> dp;
    std::vector<std::vector<Vertex<T>*>> next;
    void resetTable();

public:
	Vertex<T>* findVertex(const T &inf) const;
	vector<Vertex<T> *> getVertexSet() const;
	Vertex<T> *addVertex(const T &in);
    Vertex<T> *addVertex(const T &in, const double &lati, const double &longi);
    Edge<T> *addEdge(const T &source, const T &dest, double weight);
    int getNumVertex() const;

    void dijkstraShortestPath(Vertex<T> *s);
    void floydWarshallShortestPath();
    std::vector<T> getfloydWarshallPath(const T &origin, const T &dest) const;
};

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in) {
	Vertex<T> *v = findVertex(in);
	if (v != nullptr)
		return v;
	v = new Vertex<T>(in);
	vertexSet.push_back(v);
	return v;
}

template <class T>
Vertex<T> * Graph<T>::addVertex(const T &in, const double &lati, const double &longi) {
    Vertex<T> *v = findVertex(in);
    if (v != nullptr)
        return v;
    v = new Vertex<T>(in, lati, longi);
    vertexSet.push_back(v);
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

        for (Edge<T> edge : vertex->adj) {
            Vertex<T>* vertex_dest = edge.dest;
            if (!(vertex_dest->visited) && (vertex_dest->dist > vertex->dist + edge.weight)) {
                if (vertex_dest->dist == INF) {
                    vertex_dest->dist = vertex->dist + edge.weight;
                    vertex_dest->path = vertex;
                    queue.insert(vertex_dest);
                } else {
                    vertex_dest->dist = vertex->dist + edge.weight;
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

    resetTable();

    for (int k = 0; k < getNumVertex(); k++) {
        for (int i = 0; i < getNumVertex(); i++) {
            for (int j = 0; j < getNumVertex(); j++) {
                if (dp[i][j] > dp[i][k] + dp[k][j]) {
                    dp[i][j] = dp[i][k] + dp[k][j];
                    next[i][j] = next[i][k];
                }
            }
        }
    }
}

template <class T>
void Graph<T>::resetTable() {

    dp = std::vector<std::vector<double>>(getNumVertex(), std::vector<double>(getNumVertex(), INF));
    next = std::vector<std::vector<Vertex<T>*>>(getNumVertex(), std::vector<Vertex<T>*>(getNumVertex(), nullptr));

    for (int i = 0; i < getNumVertex(); i++) {
        for (int j = 0; j < getNumVertex(); j++) {
            if (i == j) {
                dp[i][j] = 0;
                next[i][j] = vertexSet[j];
                continue;
            }

            for (Edge<T> edge : vertexSet[i]->adj) {
                if (edge.dest == vertexSet[j]) {
                    dp[i][j] = edge.weight;
                    next[i][j] = vertexSet[j];
                    break;
                }
            }
        }
    }
}

template<class T>
std::vector<T> Graph<T>::getfloydWarshallPath(const T &orig, const T &dest) const{
    std::vector<T> res;

    Vertex<T>* vertex = findVertex(orig);
    Vertex<T>* end = findVertex(dest);

    while (vertex != end) {
        res.push_back(vertex->info);
        vertex = next[vertex->getVertexIndex()][end->getVertexIndex()];
    }
    res.push_back(end->info);

    return res;
}

#endif