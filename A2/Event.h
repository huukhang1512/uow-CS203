#ifndef Event_H
#define Event_H
#include "Teller.h"
#include "Customer.h"
enum EventType {A,D}; // Arrival | Departure

class Event {
    public:
        float firedTime;
        EventType type;
        Teller teller;
        Customer customer;
        Event();
        Event(float _firedTime, EventType _type, Customer _customer);
        Event(float _firedTime, EventType _type, Customer _customer, Teller _teller);
        friend bool operator<(Event a, Event b){
            return a.firedTime < b.firedTime;
        }
        friend bool operator==(Event a, Event b){
            return a.firedTime == b.firedTime && 
                a.type == b.type &&
                a.teller == b.teller &&
                a.customer == b.customer;
        }
        friend bool operator>(Event a, Event b){
            return !(a < b || a == b);
        }
};

#endif
