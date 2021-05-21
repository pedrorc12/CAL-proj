#ifndef CAL_PROJECT_SOLVER_H
#define CAL_PROJECT_SOLVER_H

#include <chrono>

#include "Graph.h"
#include "Volunteer.h"
#include "Donation.h"
#include "DonationSolution.h"

template <class T>
class Solver {
public:
    vector<DonationSolution<T>*> solveProblemFloydWarshall(Graph<T> &graph, vector<Volunteer<T>*> &volunteers, vector<Donation<T>*> &donations, Vertex<T>* baseStore);
    vector<DonationSolution<T>*> solveProblemDijkstra(Graph<T> &graph, vector<Volunteer<T>*> &volunteers, vector<Donation<T>*> &donations, Vertex<T>* baseStore);
};

template <class T>
vector<DonationSolution<T>*> Solver<T>::solveProblemFloydWarshall(Graph<T> &graph, vector<Volunteer<T>*> &volunteers, vector<Donation<T>*> &donations, Vertex<T>* baseStore) {

    cout << "\n Starting Floyd Warshall" << endl;
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    graph.floydWarshallShortestPath();

    std::chrono::steady_clock::time_point endTime = std::chrono::steady_clock::now();

    cout << "Finished Floyd Warshall time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime).count() << "[µs]\n" << std::endl;

    vector<DonationSolution<T>*> res;

    cout << "Processing to find the paths " << endl;

    std::chrono::steady_clock::time_point startTime2 = std::chrono::steady_clock::now();


    for (Donation<T>* donation : donations) {

        if (donation->getDestination() == nullptr)
            donation->setDestination(baseStore);

        int donationIndex = donation->getInitialLocation()->getVertexIndex();
        int destinationIndex = donation->getDestination()->getVertexIndex();
        double donationDeliveryTime = graph.getShortestPathTable()[donationIndex][destinationIndex] / 60000;

        Volunteer<T>* nearestVolunteer = nullptr;
        double nearestVolunteerTravelTime = INF;

        for (Volunteer<T>* volunteer : volunteers) {

            int volunteerIndex = volunteer->getActualLocation()->getVertexIndex();
            double travelTime = graph.getShortestPathTable()[volunteerIndex][donationIndex] / 60000;

            //Checks if volunteer is able to deliver the donation in his work time
            if (volunteer->getActualTime() + travelTime + donationDeliveryTime <= volunteer->getEndTime()) {
                //Checks if this volunteer is quicker than the previous quicker one
                if ((nearestVolunteer == nullptr) || (nearestVolunteerTravelTime > travelTime)) {
                    nearestVolunteer = volunteer;
                    nearestVolunteerTravelTime = travelTime;
                }
            }
        }

        if (nearestVolunteer != nullptr) {
            double pickUpTime = nearestVolunteer->getActualTime() + nearestVolunteerTravelTime;
            double deliveredTime = pickUpTime + donationDeliveryTime;

            DonationSolution<T>* ds = new DonationSolution<T>(donation, nearestVolunteer, pickUpTime, deliveredTime);

            //Finding the path traveled by the volunteer to the donation and then to the destination
            ds->findPath(graph.getNextVertexTable());

            //Update volunteer attributes
            nearestVolunteer->setActualTime(deliveredTime);
            nearestVolunteer->setActualLocation(donation->getDestination());

            res.push_back(ds);
        }
    }

    std::chrono::steady_clock::time_point endTime2 = std::chrono::steady_clock::now();
    cout << "Finished processing the paths time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - startTime2).count() << "[µs]\n" << std::endl;

    cout << "Total time elapsed = " << std::chrono::duration_cast<std::chrono::microseconds>(endTime2 - startTime).count() << "[µs]\n" << std::endl;

    return res;
}

template<class T>
vector<DonationSolution<T> *> Solver<T>::solveProblemDijkstra(Graph<T> &graph, vector<Volunteer<T> *> &volunteers, vector<Donation<T> *> &donations, Vertex<T>* baseStore) {
    //Use Dijkstra for each point to calculate the distance and then calculate the path

    //Start the timer
    cout << "\n Starting Dijkstra..." << endl;
    std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();

    vector<DonationSolution<T>*> res;

    for(Donation<T>* donation : donations){

        if (donation->getDestination() == nullptr)
            donation->setDestination(baseStore);

        Volunteer<T>* nearestVolunteer = nullptr;
        double nearestVolunteerTravelTime = INF;

        vector<Vertex<T> *>donationPath;
        vector<Vertex<T> *>nearestVolunteerPath;

        //Find the path for the initial to the destination of the donation
        graph.dijkstraShortestPath(donation->getInitialLocation(), donation->getDestination());
        if(!graph.dijkstraFindPath(donation->getInitialLocation(), donation->getDestination(), &donationPath))
            continue;

        double donationDeliveryTime = donation->getDestination()->getDist() / 60000;
        double travelTime;

        for(Volunteer<T>* volunteer: volunteers){
            vector<Vertex<T> *>volunteerPath;
            double dist = INF;
            graph.dijkstraShortestPath(volunteer->getActualLocation(), donation->getInitialLocation());
            bool foundPath = graph.dijkstraFindPath(volunteer->getActualLocation(), donation->getInitialLocation(), &volunteerPath);

            //Dist to the donation initial location
            travelTime = donation->getInitialLocation()->getDist() / 60000;
            //if found path and the travel time is better
            if(foundPath && (travelTime < nearestVolunteerTravelTime)){
                //if the volunteer can make the travel in time
                if (volunteer->getActualTime() + travelTime + donationDeliveryTime <= volunteer->getEndTime()){
                    nearestVolunteerPath = volunteerPath;
                    nearestVolunteer = volunteer;
                    nearestVolunteerTravelTime = travelTime;
                }
            }
        }

        if (nearestVolunteer != nullptr) {
            double pickUpTime = nearestVolunteer->getActualTime() + nearestVolunteerTravelTime;
            double deliveredTime = pickUpTime + donationDeliveryTime;

            DonationSolution<T>* ds = new DonationSolution<T>(donation, nearestVolunteer, pickUpTime, deliveredTime);

            //Build the path
            ds->connectPath(nearestVolunteerPath, donationPath);

            //Update volunteer attributes
            nearestVolunteer->setActualTime(deliveredTime);
            nearestVolunteer->setActualLocation(donation->getDestination());

            res.push_back(ds);
        }
    }

    return res;
}


#endif //CAL_PROJECT_SOLVER_H
