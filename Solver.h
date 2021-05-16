#ifndef CAL_PROJECT_SOLVER_H
#define CAL_PROJECT_SOLVER_H

#include "Graph.h"
#include "Volunteer.h"
#include "Donation.h"
#include "DonationSolution.h"

template <class T>
class Solver {
public:
    vector<DonationSolution<T>*> solveProblem(Graph<T> graph, vector<Volunteer<T>*> volunteers, vector<Donation<T>*> donations);
};

template <class T>
vector<DonationSolution<T>*> Solver<T>::solveProblem(Graph<T> graph, vector<Volunteer<T>*> volunteers, vector<Donation<T>*> donations) {

    graph.floydWarshallShortestPath();
    vector<DonationSolution<T>*> res;

    for (Donation<T>* donation : donations) {

        int donationIndex = donation->getInitialLocation()->getVertexIndex();
        int destinationIndex = donation->getDestination()->getVertexIndex();

        Volunteer<T>* nearestVolunteer = nullptr;
        double nearestVolunteerTravelTime = 0;

        for (Volunteer<T>* volunteer : volunteers) {

            int volunteerIndex = volunteer->getActualLocation()->getVertexIndex();
            double travelTime = graph.getShortestPathTable()[volunteerIndex][donationIndex];

            //Checks if volunteer is able to deliver the donation in his work time
            if (volunteer->getActualTime() + travelTime <= volunteer->getEndTime()) {
                //Checks if this volunteer is quicker than the previous quicker one
                if ((nearestVolunteer == nullptr) || (nearestVolunteerTravelTime > travelTime)) {
                    nearestVolunteer = volunteer;
                    nearestVolunteerTravelTime = travelTime;
                }
            }
        }

        if (nearestVolunteer != nullptr) {
            double pickUpTime = nearestVolunteer->getActualTime() + nearestVolunteerTravelTime;
            double deliveredTime = pickUpTime + graph.getShortestPathTable()[donationIndex][destinationIndex];

            res.push_back(new DonationSolution<T>(donation, nearestVolunteer, pickUpTime, deliveredTime));
        }
    }
    return res;
}
#endif //CAL_PROJECT_SOLVER_H
