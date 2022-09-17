#include <iostream>
#include "Simulation.h"

using std::cin;
using std::cout;
using std::endl;
using std::exception;

int main(int argc, char *argv[]){
    try {
        if (argc != 3){
            throw std::invalid_argument("Please provide a valid arguments stated below: \n ./main <path_to_txt_file> <number_of_tellers>");
            return 1;
        }
        int numOfTeller = std::stoi(argv[2]);
        Simulation simulation(numOfTeller, argv[1]);
        simulation.beginSimulation();
        simulation.report();
    }
    catch (exception &e){
        cout << e.what() << endl;
        return 1;
    }
}