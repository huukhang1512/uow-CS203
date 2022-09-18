#ifndef TELLER_H
#define TELLER_H

class Teller {
    private:
        int served;
        float totalServedTime;
        float finishedAt;
    public:
        int getTotalServed();
        float getTotalServedTime();
        float getFinishedAt();
        void serve(float finishedTime, float servedTime);
        Teller();
        // A teller is less than other when they finished their work first
        friend bool operator<(Teller a, Teller b){
            return a.finishedAt < b.finishedAt;
        }
        // A teller is less than other when they finished their work later
        friend bool operator>(Teller a, Teller b){
            return a.finishedAt > b.finishedAt;
        }
        friend bool operator==(Teller a, Teller b){
            return a.finishedAt == b.finishedAt &&
                a.served == b.served &&
                a.totalServedTime == b.totalServedTime;
        }
};
#endif