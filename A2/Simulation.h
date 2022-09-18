#ifndef SIMULATION_H
#define SIMULATION_H
#include <fstream>
#include "Customer.h"
#include "Event.h"
#include "Teller.h"
#include "MinHeap.h"

using std::ifstream;

class Simulation {
    public:
        void beginSimulation();
        void report();
        Simulation(int numOfTellers, char *filePath);

    private:
        float totalCustomerServiceTime = 0.0;
        float totalCustomerWaitingTime = 0.0;
        float totalTellersIdleTime = 0.0;
        float curTime = 0.0;

        int maxCustomerQueueSize = 0;
        int numOfCustomers = 0;
        int numOfTellers = 0;

        Customer *customers;
        MinHeap<Teller> *tellersHeap;
        MinHeap<Event> *eventsHeap;
        MinHeap<Customer> *customersHeap;

        void processArrival(Customer &customer);
        void processDeparture(Teller teller);
        void serve(Customer *customer, Teller *teller, float finishedTime);
        Teller availableTeller();
};
#endif