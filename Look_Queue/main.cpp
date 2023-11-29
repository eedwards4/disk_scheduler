//
//
#include <iostream>
#include <fstream>
#include <cstdlib>

#include "../CommonFiles/Request.hpp"
#include "LookQueue.h"

/* this does nothing without vector and algorithm
bool compareRequestAsc(std::pair<bool, Request*> a, std::pair<bool, Request*> b) {
    return a.second->track() < b.second->track();
}

bool compareRequestDesc(std::pair<bool, Request*> a, std::pair<bool, Request*> b) {
    return a.second->track() > b.second->track();
}

LookQueue *makeInQueue(std::vector<std::pair<bool, Request*>> requests) {
    LookQueue *queue = new LookQueue();
    std::stable_sort(requests.begin(), requests.end(), compareRequestAsc);
    for (auto &request : requests) {
        queue->addRequest(request.second, 0, 0);
    }
    return queue;
}

LookQueue *makeOutQueue(std::vector<std::pair<bool, Request*>> requests) {
    LookQueue *queue = new LookQueue();
    std::stable_sort(requests.begin(), requests.end(), compareRequestDesc);
    for (auto &request : requests) {
        queue->addRequest(request.second, 0, 0);
    }
    return queue;
}
*/

LookQueue *createLookQueue(int argc, char* argv[], int headPos){
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

    LookQueue *queue = new LookQueue();

    int time, track, sector, i = 0;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, headPos, i);
        i++;
    }

    return queue;
}

int main(int argc, char *argv[]) {
    const int randomTest = false;
    int headPos = 20;
    bool headDirection = true; // false = out, true = in
    LookQueue *queue = nullptr;

    if (randomTest){
        // placeholder for random test
    }
    else {
        queue = createLookQueue(argc, argv, headPos);
    }

    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the Look Queue." << std::endl;
    queue->print();

    delete queue;
    return 0;
}
