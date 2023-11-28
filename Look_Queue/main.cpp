//
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "../CommonFiles/Request.hpp"
#include "LookQueue.h"

LookQueue *createLookQueue(int argc, char *argv[], int headPos, bool headDirection) {
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
    std::vector<std::pair<int, Request*>> requests;

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        requests.emplace_back(std::make_pair(0, request));
    }



    return queue;
}



int main(int argc, char *argv[]) {
    std::cout << "Look wait queue -- Main function.\n";
    const int randomTest = false;
    int headPos = 0;
    bool headDirection = true; // false = out, true = in
    LookQueue *queue = nullptr;

    if (randomTest){
        // placeholder for random test
    }
    else {
        queue = createLookQueue(argc, argv, headPos, headDirection);
    }

    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the ST Queue." << std::endl;
    if (headDirection) {std::cout << "Direction is IN" << std::endl;}
    else {std::cout << "Direction is OUT" << std::endl;}
    std::cout << "Current queue contains." << std::endl;
    queue->print();
    std::cout << "nextQueue is empty." << std::endl;
    delete queue;

    return 0;
}
