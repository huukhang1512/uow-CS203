#include <iostream>
#include <fstream>

using std::exception;
using std::cout;
using std::endl;
using std::ifstream;

ifstream openNewFile(char* filePath){

    cout << "Loading file from path " << filePath << "..." << endl;
    ifstream file(filePath);

    if(file.fail()){
        throw std::invalid_argument("Unable to locate the file, please make sure your file path is correct");
    }
    return file;
}

class CustomerMetaData {
    private:
        float arrivalTime;
        float serviceTime;
        int priority; // 1 | 2 | 3
    public:
        CustomerMetaData(){};
        CustomerMetaData(float _arrivalTime, float _serviceTime, int _priority){
            arrivalTime = _arrivalTime;
            serviceTime = _serviceTime;
            priority = _priority;
        }
        void setData(float _arrivalTime, float _serviceTime, int _priority){
            arrivalTime = _arrivalTime;
            serviceTime = _serviceTime;
            priority = _priority;
        }
        
};

int main(int argc, char *argv[]) {
    try {
        if (argc != 2){
            throw std::invalid_argument("Please provide a valid arguments stated below: \n ./main <path_to_txt_file>");
            return 1;
        }
        ifstream file = openNewFile(argv[1]);
        float curArrival, curServiceTime;
        int curPriority;
        
        CustomerMetaData data[100];
        int size=0;
        while (file >> curArrival >> curServiceTime >> curPriority){
            data[size++].setData(curArrival,curServiceTime,curPriority);
        }

    } catch (exception &e) {
        cout << e.what() << endl;
        return 1;
    }
}