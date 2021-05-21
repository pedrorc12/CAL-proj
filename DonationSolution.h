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
    vector<Vertex<T>*> getPath() { return path; }
    DonationSolution(Donation<T>* donation, Volunteer<T>* volunteer, double pickUpTime, double deliveredTime);
    void findPath(vector<vector<Vertex<T>*>> nextVertexTable);
    void connectPath(vector<Vertex<T> *> toDonation, vector<Vertex<T> *> toDelivery);
    void printSolution();
    void printPath();
};

template <class T>
void DonationSolution<T>::findPath(vector<vector<Vertex<T>*>> nextVertexTable) {

    Vertex<T>* vertex = volunteer->getActualLocation();
    Vertex<T>* donationVertex = donation->getInitialLocation();
    Vertex<T>* destinationVertex = donation->getDestination();

    while (vertex != donationVertex) {
        path.push_back(vertex);
        vertex = nextVertexTable[vertex->getVertexIndex()][donationVertex->getVertexIndex()];
    }
    while (vertex != destinationVertex) {
        path.push_back(vertex);
        vertex = nextVertexTable[vertex->getVertexIndex()][destinationVertex->getVertexIndex()];
    }
    path.push_back(destinationVertex);
}

template <class T>
DonationSolution<T>::DonationSolution(Donation<T>* donation, Volunteer<T>* volunteer, double pickUpTime, double deliveredTime) {
    this->donation = donation;
    this->volunteer = volunteer;
    this->pickUpTime = pickUpTime;
    this->deliveredTime = deliveredTime;
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

template<class T>
void DonationSolution<T>::connectPath(vector<Vertex<T> *> toDonation, vector<Vertex<T> *> toDelivery) {
    for(int i = 0; i < toDonation.size() - 1; i++){
        path.push_back(toDonation[i]);
    }
    for(Vertex<T> *vert: toDelivery){
        path.push_back(vert);
    }
}

#endif //CAL_PROJECT_DONATIONSOLUTION_H
