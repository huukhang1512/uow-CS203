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
        // read from CLI
        int numOfTeller = std::stoi(argv[2]);
        char *filePath =  argv[1];

        Simulation simulation(numOfTeller,filePath);
        simulation.beginSimulation();
        simulation.report();
    }
    catch (exception &e){
        cout << e.what() << endl;
        return 1;
    }
}