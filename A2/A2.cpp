#include <iostream>
#include "Simulation.h"

using std::cin;
using std::cout;
using std::endl;
using std::exception;

int main(int argc, char *argv[]){
    try {
        // Read from standard input
        char filePath[50];
        int numOfTellers;

        cout << "Please enter the path to the text file (max 50 characters): ";
        cin.getline(filePath,50);
        cout << "Please enter the number of tellers: ";
        cin >> numOfTellers;
        
        Simulation simulation(numOfTellers,filePath);
        simulation.beginSimulation();
        simulation.report();
    }
    catch (exception &e){
        cout << e.what() << endl;
        return 1;
    }
}