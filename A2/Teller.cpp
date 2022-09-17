#include "Teller.h"
Teller::Teller(){
    served = 0;
    totalServedTime = 0.0;
    finishedAt = 0.0;
}

int Teller::getTotalServed(){
    return served;
}

float Teller::getTotalServedTime(){
    return totalServedTime;
}

float Teller::getFinishedAt(){
    return finishedAt;
}

void Teller::setId(int _id){
    id = _id;
}

int Teller::getId(){
    return id;
}

void Teller::serve(float finishedTime, float servedTime){
    served++;
    finishedAt = finishedTime;
    totalServedTime += servedTime;
}
