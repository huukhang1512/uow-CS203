#ifndef TELLER_H
#define TELLER_H

class Teller {
    private:
        int id;
        int served;
        float totalServedTime;
        float finishedAt;
    public:
        int getTotalServed();
        float getTotalServedTime();
        float getFinishedAt();
        void setId(int _id);
        int getId();
        void serve(float finishedTime, float servedTime);
        Teller();
        friend bool operator<(Teller a, Teller b){
            return a.finishedAt < b.finishedAt;
        }
        friend bool operator>(Teller a, Teller b){
            return a.finishedAt > b.finishedAt;
        }
};
#endif