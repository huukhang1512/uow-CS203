#include "Simulation.h"
#include <cmath>
#include <iostream>
using std::cout;
using std::endl;
using std::fmax;

ifstream openNewFile(char* filePath){

    cout << "Loading file from path " << filePath << "..." << endl;
    ifstream file(filePath);

    if (file.fail()){
        throw std::invalid_argument("Unable to locate the file, please make sure your file path is correct");
    }
    return file;
}

Simulation::Simulation(int _numOfTellers, char *filePath){
    tellers = new Teller[_numOfTellers];
    tellersHeap = new MinHeap<Teller>(_numOfTellers);
    customers = new Customer[100];
    eventsHeap = new MinHeap<Event>(100);
    customersHeap = new MinHeap<Customer>(100);
    numOfTellers = _numOfTellers;
    float curArrival, curServiceTime;
    int curPriority;
    ifstream file = openNewFile(filePath);
    while (file >> curArrival >> curServiceTime >> curPriority){
        Event event(curArrival, EventType::a);
        customers[numOfCustomer++].setCustomerData(curArrival, curServiceTime, curPriority);
        eventsHeap->push(event);
    }
    for (int i = 0; i < numOfTellers; i++){
        tellers[i].setId(i);
    }
}

int Simulation::availableTeller(){
    if(tellersHeap->size() >= numOfTellers){
        return -1;
    }
    return tellersHeap->pop().getId();
}

void Simulation::serve(Customer *customer, Teller *teller, float finishedTime){
    teller->serve(finishedTime, customer->getServiceTime());
    totalCustomerServiceTime += customer->getServiceTime();
}

void Simulation::processArrival(Customer &customer){
    int availableServerIndex = availableTeller();
    if (availableServerIndex == -1){
        customersHeap->push(customer);
    } else {
        // process the customer right away
        float finished = curTime + customer.getServiceTime();

        Event departureEvent(finished, EventType::d, availableServerIndex);
        eventsHeap->push(departureEvent);

        serve(&customer, &tellers[availableServerIndex],finished);
    }
}

void Simulation::processDeparture(int availableTeller){
    // teller finished with the departure event, process next customer currently queue up if any, else stay idle
    if (!customersHeap->empty()){
        Customer customer = customersHeap->pop();

        float finished = curTime + customer.getServiceTime();
        float waitingTime = curTime - customer.getArrivalTime();

        Event departureEvent(finished, EventType::d, availableTeller);
        eventsHeap->push(departureEvent);

        serve(&customer, &tellers[availableTeller],finished);
        totalCustomerWaitingTime += waitingTime;
    } else {
        tellersHeap->push(tellers[availableTeller]);
    }
}

void Simulation::beginSimulation(){
    int curCustomer = 0;
    while (!eventsHeap->empty()){
        maxHeapLength = fmax(maxHeapLength, customersHeap->size());
        Event event = eventsHeap->pop();
        curTime = event.firedTime;
        int server = event.server;

        if (event.type == EventType::a){
           processArrival(customers[curCustomer++]);
        } else {
            processDeparture(server);
        }
    }
}

void Simulation::report(){
    cout << "Total simulated time              = " << curTime << endl;
    cout << "Total serving time                = " << totalCustomerServiceTime << endl;
    cout << "Average serving time per customer = " << totalCustomerServiceTime / numOfCustomer << endl;
    cout << "Average waiting time per customer = " << totalCustomerWaitingTime / numOfCustomer << endl;
    cout << "Maximum length of queue           = " << maxHeapLength << endl;
    cout << "Average length of queue           = " << totalCustomerWaitingTime / curTime << endl;
    cout << endl;
    for (int i = 0; i < numOfTellers; i++){
        cout << "Statistic of Teller #" << i << ":" << endl;
        cout << "\t Number of customers served = " << tellers[i].getTotalServed() << endl;
        cout << "\t Total idle time            = " << curTime - tellers[i].getTotalServedTime() << endl;
        cout << "\t Idle rate                  = " << (curTime - tellers[i].getTotalServedTime()) / curTime << endl;
    }
}