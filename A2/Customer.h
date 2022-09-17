#ifndef CUSTOMER_H
#define CUSTOMER_H

class Customer {
    private: 
        float arrivalTime;
        float serviceTime;
        int priority; // 1 | 2 | 3
    public:
        Customer(){
            arrivalTime = 0.0;
            serviceTime = 0.0;
            priority = -1;
        };
        friend bool operator<(Customer a, Customer b){
            if(a.priority < b.priority) {
                return false;
            }
            if(a.priority == b.priority) {
                return a.arrivalTime < b.arrivalTime;
            }
            return true;
        }
        friend bool operator==(Customer a, Customer b){
            return a.priority == b.priority && a.arrivalTime == b.arrivalTime;
        }
        friend bool operator>(Customer a, Customer b){
            return !(a < b || a == b);
        }
        float getArrivalTime();
        float getServiceTime();
        int getPriority();
        void setCustomerData(float _arrivalTime, float _serviceTime, int _priority);
};

#endif
