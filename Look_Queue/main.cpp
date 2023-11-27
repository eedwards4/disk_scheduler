//
//
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../CommonFiles/Request.hpp"
#include "LookQueue.h"

LookQueue *createLookQueue(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }

    std::ifstream inputStream;
    inputStream.open(argv[1], std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        perror("Error when attempting to open the input file.");
        exit(1);
    }

    auto *queue = new LookQueue();

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, 0, 0);
    }

    return queue;
}



int main(int argc, char *argv[]) {
    std::cout << "Look wait queue -- Main function.\n";
    const int randomTest = false;
    LookQueue *queue = nullptr;

    if (randomTest){
        // placeholder for random test
    }
    else {
        queue = createLookQueue(argc, argv);
    }

    queue->print();
    delete queue;

    return 0;
}
