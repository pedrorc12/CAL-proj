#ifndef CAL_PROJECT_DONATIONSOLUTION_H
#define CAL_PROJECT_DONATIONSOLUTION_H

#include "Donation.h"
#include "Volunteer.h"

template <class T>
class DonationSolution {
    Donation<T>* donation;
    Volunteer<T>* volunteer;
    double pickUpTime;
    double deliveredTime;
    vector<Vertex<T>*> path;

public:
    DonationSolution(Donation<T>* donation, Volunteer<T>* volunteer, double pickUpTime, double deliveredTime);
    void addVertex(Vertex<T>* vertex);
    void printSolution();
    void printPath();
};

template <class T>
DonationSolution<T>::DonationSolution(Donation<T>* donation, Volunteer<T>* volunteer, double pickUpTime, double deliveredTime) {
    donation = donation;
    volunteer = volunteer;
    pickUpTime = pickUpTime;
    deliveredTime = deliveredTime;
}

template <class T>
void DonationSolution<T>::addVertex(Vertex<T>* vertex) {
    path.push_back(vertex);
}

template <class T>
void DonationSolution<T>::printSolution() {
    cout << "Donation ID: " << donation->getId() << endl;
    cout << "Volunteer ID: " << volunteer->getId() << endl;
    cout << "Pick up Time: " << pickUpTime << endl;
    cout << "Delivered Time: " << deliveredTime << endl;
    cout << "Path: ";
    printPath();
}

template <class T>
void DonationSolution<T>::printPath() {
    for (int i = 0; i < path.size(); i++) {
        cout << path[i]->getInfo();

        if (i != path.size() - 1)
            cout << " -> ";
    }
}

#endif //CAL_PROJECT_DONATIONSOLUTION_H
