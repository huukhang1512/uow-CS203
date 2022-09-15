#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <vector>
#include <cmath>

using std::exception;
using std::cout;
using std::endl;
using std::ifstream;
using std::priority_queue;
using std::queue;
using std::vector;
using std::max;

ifstream openNewFile(char* filePath){

    cout << "Loading file from path " << filePath << "..." << endl;
    ifstream file(filePath);

    if(file.fail()){
        throw std::invalid_argument("Unable to locate the file, please make sure your file path is correct");
    }
    return file;
}

class Customer {
    public:
        float arrivalTime;
        float serviceTime;
        int priority; // 1 | 2 | 3
        Customer(){};
        Customer(float _arrivalTime, float _serviceTime, int _priority){
            arrivalTime = _arrivalTime;
            serviceTime = _serviceTime;
            priority = _priority;
        }
        
};

enum EventType {a,d};

class Event {
    public:
        float firedTime;
        EventType type;
        int server=-1;
        Event(float _firedTime, EventType _type){
            firedTime = _firedTime;
            type = _type;
        }
        Event(float _firedTime, EventType _type, int _server){
            firedTime = _firedTime;
            type = _type;
            server = _server;
        }
};

class Teller {
    public:
        bool isBusy=false;
        int served=0;
        float finishedAt=0.0;
        float idleTime=0.0;
        Teller(){}
};

class Compare {
    public:
    bool operator() (Customer a, Customer b){
        if(a.priority < b.priority) {
            return true;
        }
        if(a.priority == b.priority) {
            return a.arrivalTime > b.arrivalTime;
        }
        return false;
    }
};

class Comparison {
    public:
    bool operator() (Event a, Event b){
        return a.firedTime > b.firedTime;
    }
};

int availableTeller(Teller tellers[], int numOfTeller){
    for(int i = 0; i < numOfTeller; i++){
        if(!tellers[i].isBusy) return i;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    try {
        if (argc != 2){
            throw std::invalid_argument("Please provide a valid arguments stated below: \n ./main <path_to_txt_file>");
            return 1;
        }
        ifstream file = openNewFile(argv[1]);

        int numOfTeller = 4;
        int numOfCustomer = 0;
        float curArrival, curServiceTime;
        int curPriority;
        
        queue<Customer> customers;
        priority_queue<Event,vector<Event>, Comparison> eventsHeap;
        priority_queue<Customer,vector<Customer>, Compare> customersHeap;

        while (file >> curArrival >> curServiceTime >> curPriority){
            Customer customer(curArrival,curServiceTime,curPriority);
            Event event(curArrival,EventType::a);

            customers.push(customer);
            eventsHeap.push(event);
            numOfCustomer++;
        }

        Teller tellers[numOfTeller];
        float curTime = 0.0;

        int maxHeapLength = 0;
        float totalCustomerWaitingTime = 0.0;
        float totalCustomerServiceTime = 0.0;
        float totalTellersIdleTime = 0.0;
        while(!eventsHeap.empty()){
            maxHeapLength = fmax(maxHeapLength , customersHeap.size());
            Event event = eventsHeap.top();
            eventsHeap.pop();
            curTime = event.firedTime;
            int server = event.server;
            if(event.type == EventType::a){
                int availableServerIndex = availableTeller(tellers,numOfTeller);
                Customer customer = customers.front();
                customers.pop();
                if(availableServerIndex == -1){
                    customersHeap.push(customer);
                } else {
                    // process the customer right away
                    float finished = curTime + customer.serviceTime;

                    Event departureEvent(finished,EventType::d,availableServerIndex);
                    eventsHeap.push(departureEvent);

                    tellers[availableServerIndex].isBusy = true;
                    tellers[availableServerIndex].served++;
                    tellers[availableServerIndex].idleTime += curTime - tellers[availableServerIndex].finishedAt;
                    tellers[availableServerIndex].finishedAt = finished;

                    totalCustomerServiceTime += customer.serviceTime;
                }
            } else {
                // teller finished with the departure event, process next customer currently queue up if any
                if(!customersHeap.empty()){

                    Customer customer = customersHeap.top();
                    customersHeap.pop();

                    float finished = curTime + customer.serviceTime;
                    float waitingTime = curTime - customer.arrivalTime;

                    Event departureEvent(finished,EventType::d, server);
                    eventsHeap.push(departureEvent);

                    tellers[server].isBusy = true;
                    tellers[server].served++;
                    tellers[server].finishedAt = finished;

                    totalCustomerServiceTime += customer.serviceTime;
                    totalCustomerWaitingTime += waitingTime;
                } else {
                    tellers[server].isBusy = false;
                }

            }
        }
        cout << totalCustomerWaitingTime << endl;
        cout << "Total simulated time              = " << curTime << endl;
        cout << "Total serving time                = " << totalCustomerServiceTime << endl;
        cout << "Total idle time                   = " << totalTellersIdleTime << endl;
        cout << "Average serving time per customer = " << totalCustomerServiceTime/numOfCustomer << endl;
        cout << "Average waiting time per customer = " << totalCustomerWaitingTime/numOfCustomer << endl;
        cout << "Maximum length of queue           = " << maxHeapLength << endl;
        cout << "Average length of queue           = " << totalCustomerWaitingTime/curTime << endl;
        cout << endl;
        for(int i = 0; i < numOfTeller; i++){
            cout << "Statistic of Teller #" << i << ":" << endl;
            cout << "\t Number of customers served = " << tellers[i].served << endl;
            cout << "\t Total idle time            = " << tellers[i].idleTime<< endl;
            cout << "\t Idle rate                  = " << endl;

        }

    } catch (exception &e) {
        cout << e.what() << endl;
        return 1;
    }
}