//
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <algorithm>

#include "../CommonFiles/Request.hpp"
#include "LookQueue.h"

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


LookQueue *createLookQueue(int argc, char* argv[], int headPos, LookQueue* &in, LookQueue* &out){
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

    // Create vector of all requests
    std::vector<Request*> requests;
    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        queue->addRequest(request, headPos, sector);
    }

    std::vector<std::pair<bool, Request*>> inRequests;
    std::vector<std::pair<bool, Request*>> outRequests;
    // Split vector into constituent unordered vectors (in/out)
    for (auto &request : requests) {
        if (request->track() >= headPos){
            inRequests.emplace_back(0, request);
        } else {
            outRequests.emplace_back(0, request);
        }
    }
    // Convert to queues
    in = makeInQueue(inRequests);
    out = makeOutQueue(outRequests);
}

int main(int argc, char *argv[]) {
    const int randomTest = false;
    int headPos = 20;
    bool headDirection = true; // false = out, true = in
    LookQueue *in = nullptr;
    LookQueue *out= nullptr;

    if (randomTest){
        // placeholder for random test
    }
    else {
        createLookQueues(argc, argv, headPos, in, out);
    }

    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the ST Queue." << std::endl;
    std::cout << "Direction is IN" << std::endl;
    std::cout << "Current queue contains." << std::endl;
    in->print();
    if (out->empty()){
        std::cout << "nextQueue is empty." << std::endl;
    } else {
        std::cout << "nextQueue contains." << std::endl;
        out->print();
    }

    delete in;
    delete out;
    return 0;
}
