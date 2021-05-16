#ifndef CAL_PROJECT_DONATION_H
#define CAL_PROJECT_DONATION_H

#include "Graph.h"

template <class T>
class Donation {
    int id;
    Vertex<T>* initialLocation;
    Vertex<T>* destination;
    static int idCounter;

public:
    Donation(Vertex<T>* initialLocation, Vertex<T>* destination);
    int getId() { return id; }
    Vertex<T>* getInitialLocation() { return initialLocation; }
    Vertex<T>* getDestination() { return destination; }
};

template <class T>
int Donation<T>::idCounter = 1;

template <class T>
Donation<T>::Donation(Vertex<T>* initialLocation, Vertex<T>* destination) {
    this->id = idCounter;
    this->initialLocation = initialLocation;
    this->destination = destination;

    idCounter++;
}

#endif //CAL_PROJECT_DONATION_H