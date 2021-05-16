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
    double getStartTime() { return startTime; }
    double getEndTime() { return endTime; }
    double getActualTime() { return actualTime; }
    Vertex<T>* getActualLocation() { return actualLocation; }

    void setActualTime(double time) { this->actualTime = time; }
    void setActualLocation(Vertex<T>* location) { this->actualLocation = location; }
};

template <class T>
int Volunteer<T>::idCounter = 1;

template <class T>
Volunteer<T>::Volunteer(double startTime, double endTime, Vertex<T> *initialLocation) {
    this->id = idCounter;
    this->startTime = startTime;
    this->endTime = endTime;
    this->actualTime = startTime;
    this->actualLocation = initialLocation;

    idCounter++;
}

#endif //CAL_PROJECT_VOLUNTEER_H
