#ifndef Event_H
#define Event_H
#include "Teller.h"
enum EventType {A,D}; // Arrival | Departure

class Event {
    public:
        float firedTime;
        EventType type;
        Teller server;
        Event();
        Event(float _firedTime, EventType _type);
        Event(float _firedTime, EventType _type, Teller _server);
        friend bool operator<(Event a, Event b){
            return a.firedTime < b.firedTime;
        }
        friend bool operator==(Event a, Event b){
            return a.firedTime == b.firedTime;
        }
        friend bool operator>(Event a, Event b){
            return !(a < b || a == b);
        }
};

#endif
