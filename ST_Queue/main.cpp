//
//

#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../CommonFiles/Request.hpp"
#include "STQueue.hpp"

STQueue *createSTQueue(int argc, char *argv[], int headPos) {
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

    auto *queue = new STQueue();

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, headPos, sector);
    }

    return queue;
}

int main(int argc, char *argv[]) {
    int headPos = 0;
    STQueue *queue = nullptr;
    queue = createSTQueue(argc, argv, headPos);
    queue->print();
    delete queue;
    return 0;
}
