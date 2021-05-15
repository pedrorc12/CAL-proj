#ifndef CAL_PROJECT_VOLUNTEER_H
#define CAL_PROJECT_VOLUNTEER_H

#include "Graph.h"

int actualId = 1;

template <class T>
class Volunteer {
    int id;
    double startTime;
    double endTime;
    double actualTime;
    Vertex<T>* actualLocation;

public:
    Volunteer(double startTime, double endTime, Vertex<T>* initialLocation);
};

template <class T>
Volunteer<T>::Volunteer(double startTime, double endTime, Vertex<T> *initialLocation) {
    id = actualId;
    startTime = startTime;
    endTime = endTime;
    actualTime = startTime;
    actualLocation = initialLocation;

    actualId++;
}

#endif //CAL_PROJECT_VOLUNTEER_H
