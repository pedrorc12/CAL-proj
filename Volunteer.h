#ifndef CAL_PROJECT_VOLUNTEER_H
#define CAL_PROJECT_VOLUNTEER_H

#include "Graph.h"

template <class T>
class Volunteer {
    int id;
    double startTime;
    double endTime;
    double actualTime;
    Vertex<T>* actualLocation;
    static int idCounter;

public:
    Volunteer(double startTime, double endTime, Vertex<T>* initialLocation);
    int getId() { return id; }
};

template <class T>
int Volunteer<T>::idCounter = 1;

template <class T>
Volunteer<T>::Volunteer(double startTime, double endTime, Vertex<T> *initialLocation) {
    id = idCounter;
    startTime = startTime;
    endTime = endTime;
    actualTime = startTime;
    actualLocation = initialLocation;

    idCounter++;
}

#endif //CAL_PROJECT_VOLUNTEER_H
