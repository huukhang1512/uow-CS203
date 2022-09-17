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
void Customer::setCustomerData(float _arrivalTime, float _serviceTime, int _priority){
    arrivalTime = _arrivalTime;
    serviceTime = _serviceTime;
    priority = _priority;
}