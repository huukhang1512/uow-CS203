#include "Teller.h"
#include "Event.h"
Event::Event(){
    firedTime = 0.0;
}
Event::Event(float _firedTime, EventType _type){
    firedTime = _firedTime;
    type = _type;
}
Event::Event(float _firedTime, EventType _type, Teller _server){
    firedTime = _firedTime;
    type = _type;
    server = _server;
}