#ifndef Event_H
#define Event_H

enum EventType {a,d};

class Event {
    public:
        float firedTime;
        EventType type;
        int server=-1;
        Event();
        Event(float _firedTime, EventType _type);
        Event(float _firedTime, EventType _type, int _server);
        friend bool operator<(Event a, Event b){
            return a.firedTime < b.firedTime;
        }
        friend bool operator>(Event a, Event b){
            return a.firedTime > b.firedTime;
        }
};

#endif
