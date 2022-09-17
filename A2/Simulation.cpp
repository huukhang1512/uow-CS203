#include "Simulation.h"
#include <iostream>
using std::cout;
using std::ofstream;
using std::endl;

ifstream openNewFile(char* filePath){

    cout << "Loading file from path " << filePath << "..." << endl;
    ifstream file(filePath);

    if (file.fail()){
        throw std::invalid_argument("Unable to locate the file, please make sure your file path is correct");
    }
    return file;
}

Simulation::Simulation(int _numOfTellers, char *filePath){
    tellersHeap = new MinHeap<Teller>(_numOfTellers);
    customers = new Customer[100];
    eventsHeap = new MinHeap<Event>(200);
    customersHeap = new MinHeap<Customer>(100);

    numOfTellers = _numOfTellers;
    float curArrival, curServiceTime;
    int curPriority;
    ifstream file = openNewFile(filePath);
    while (file >> curArrival >> curServiceTime >> curPriority){
        Event event(curArrival, EventType::A);
        customers[numOfCustomer++].setCustomerData(curArrival, curServiceTime, curPriority);
        eventsHeap->push(event);
    }
    for (int i = 0; i < numOfTellers; i++){
        Teller teller;
        tellersHeap->push(teller);
    }
}

void Simulation::serve(Customer *customer, Teller *teller, float finishedTime){
    teller->serve(finishedTime, customer->getServiceTime());
    totalCustomerServiceTime += customer->getServiceTime();
    Event departureEvent(finishedTime, EventType::D, *teller);
    eventsHeap->push(departureEvent);
}

void Simulation::processArrival(Customer &customer){
    if (tellersHeap->empty()){
        customersHeap->push(customer);
    } else {
        // process the customer right away
        float finished = curTime + customer.getServiceTime();
        Teller teller = tellersHeap->pop();
        serve(&customer, &teller, finished);
    }
}

void Simulation::processDeparture(Teller teller){
    // teller finished with the departure event, process next customer currently queue up if any, else stay idle
    if (!customersHeap->empty()){
        Customer customer = customersHeap->pop();

        float finished = curTime + customer.getServiceTime();
        float waitingTime = curTime - customer.getArrivalTime();
        serve(&customer, &teller, finished);
        totalCustomerWaitingTime += waitingTime;
    } else {
        tellersHeap->push(teller);
    }
}

void Simulation::beginSimulation(){
    int curCustomer = 0;
    while (!eventsHeap->empty()){
        maxHeapLength = maxHeapLength < customersHeap->size() ? customersHeap->size() : maxHeapLength;
        Event event = eventsHeap->pop();
        Teller server = event.server;
        curTime = event.firedTime;

        if (event.type == EventType::A){
            processArrival(customers[curCustomer++]);
        } else if (event.type == EventType::D){
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
    int i = 0;
    while(!tellersHeap->empty()){
        Teller teller = tellersHeap->pop();
        cout << "Statistic of Teller #" << i++ << ":" << endl;
        cout << "\t Number of customers served = " << teller.getTotalServed() << endl;
        cout << "\t Total idle time            = " << curTime - teller.getTotalServedTime() << endl;
        cout << "\t Idle rate                  = " << (curTime - teller.getTotalServedTime()) / curTime << endl;
    }
}