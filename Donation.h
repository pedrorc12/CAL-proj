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
    int getId() { return id; };
};

template <class T>
int Donation<T>::idCounter = 1;

template <class T>
Donation<T>::Donation(Vertex<T>* initialLocation, Vertex<T>* destination) {
    id = idCounter;
    initialLocation = initialLocation;
    destination = destination;

    idCounter++;
}

#endif //CAL_PROJECT_DONATION_H