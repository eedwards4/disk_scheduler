//
// Created by evane on 11/27/2023.
//

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../CommonFiles/Request.hpp"
#include "PickUpQueue.h"

PickUpQueue *createPickUpQueue(int argc, char *argv[], int headPos) {
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

    auto *queue = new PickUpQueue();

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, headPos, 0);
    }

    return queue;
}

int main(int argc, char *argv[]) {
    int headPos = 40;
    auto *queue = createPickUpQueue(argc, argv, headPos);
    queue->print();
    delete queue;
    return 0;
}
