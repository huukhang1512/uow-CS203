#include "Customer.h"

float Customer::getArrivalTime(){
    return arrivalTime;
}
float Customer::getServiceTime(){
    return serviceTime;
}
int Customer::getPriority(){
    return priority;
}

Customer::Customer(float _arrivalTime, float _serviceTime, int _priority){
    arrivalTime = _arrivalTime;
    serviceTime = _serviceTime;
    priority = _priority;
}

Customer::Customer(){
    arrivalTime = 0.0;
    serviceTime = 0.0;
    priority = -1;
}