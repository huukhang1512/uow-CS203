#include "Teller.h"
#include "Event.h"
Event::Event(){
    firedTime = 0.0;
}
Event::Event(float _firedTime, EventType _type, Customer _customer){
    firedTime = _firedTime;
    type = _type;
    customer = _customer;
}
Event::Event(float _firedTime, EventType _type, Customer _customer, Teller _teller){
    firedTime = _firedTime;
    type = _type;
    teller = _teller;
    customer = _customer;

}