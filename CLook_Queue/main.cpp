//
// Created by evane on 11/28/2023.
//
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../CommonFiles/Request.hpp"
#include "CLookQueue.h"


CLookQueue *createCLookQueue(int argc, char* argv[], int headPos){
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

    CLookQueue *queue = new CLookQueue();

    int time, track, sector, i = 0;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, headPos, i);
        i++;
    }

    return queue;
}

int main(int argc, char *argv[]) {
    int headPos = 0;
    CLookQueue *queue = nullptr;
    queue = createCLookQueue(argc, argv, headPos);
    queue->print();
    delete queue;
    return 0;
}
