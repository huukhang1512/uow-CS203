#include <iostream>
#include <fstream>
#include <queue>
#include <ctime>
#include <vector>

using std::exception;
using std::cout;
using std::endl;
using std::ifstream;
using std::priority_queue;
using std::queue;
using std::vector;

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

int getAvailableIndex(Teller tellers[], int numOfTeller){
    for(int i = 0; i < numOfTeller; i++){
                if(!tellers[i].isBusy)
                       return i;
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

        int numOfTeller = 3;
        float curArrival, curServiceTime;
        int curPriority;
        
        queue<Customer> customers;
        priority_queue<Event,vector<Event>, Comparison> events;

        int size=0;
        while (file >> curArrival >> curServiceTime >> curPriority){
            Customer customer(curArrival,curServiceTime,curPriority);
            Event event(curArrival,EventType::a);
            customers.push(customer);
            events.push(event);
        }

        Teller tellers[numOfTeller];
        float curTime = 0.0;

        priority_queue<Customer,vector<Customer>, Compare> heap;

        int j = 0;
        while(!events.empty()){
            j++;
            Event event = events.top();
            events.pop();
            curTime = event.firedTime;
            int server = event.server;
            
            if(event.type == EventType::a){
                int availableServerIndex = getAvailableIndex(tellers,numOfTeller);
                Customer customer = customers.front();
                customers.pop();
                if(availableServerIndex == -1){
                    heap.push(customer);
                } else {
                    float finished = curTime + customer.serviceTime;
                    Event departureEvent(finished,EventType::d,availableServerIndex);
                    tellers[availableServerIndex].isBusy = true;
                    events.push(departureEvent);
                    tellers[availableServerIndex].served++;
                }
            } else {
                tellers[server].isBusy = false;
                if(!heap.empty()){
                    Customer customer = heap.top();
                    heap.pop();
                    float finished = curTime + customer.serviceTime;
                    tellers[server].isBusy = true;

                    Event departureEvent(finished,EventType::d, server);
                    events.push(departureEvent);
                    tellers[server].served++;
                }

            }
        }
       
        for(int i = 0; i < numOfTeller; i++){
            cout << "Number of customers served by teller #" << i << ": " << tellers[i].served << endl;
        }
    } catch (exception &e) {
        cout << e.what() << endl;
        return 1;
    }
}