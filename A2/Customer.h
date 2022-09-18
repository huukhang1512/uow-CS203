#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
    private: 
        float arrivalTime;
        float serviceTime;
        int priority; // 1 | 2 | 3
    public:
        Customer();
        Customer(float _arrivalTime, float _serviceTime, int _priority);
        friend bool operator<(Customer a, Customer b){
            if(a.priority > b.priority) {
                // customer A has a higher priority, therefore A will be placed higher than B in the min heap
                return true; 
            }
            if(a.priority == b.priority) {
                // sort by arrival time, customer A will be placed higher than customer B in the min heap if arrive earlier
                return a.arrivalTime < b.arrivalTime;
            }
            // customer A will be place lower than customer B in the min heap because A has a lower priority then B
            return false; 
        }
        friend bool operator==(Customer a, Customer b){
            return a.priority == b.priority && a.arrivalTime == b.arrivalTime && a.serviceTime == b.serviceTime;
        }
        friend bool operator>(Customer a, Customer b){
            return !(a < b || a == b);
        }
        float getArrivalTime();
        float getServiceTime();
        int getPriority();
};

#endif
