//
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>

#include "../CommonFiles/Request.hpp"
#include "LookQueue.h"


LookQueue *createLookQueue(std::priority_queue<std::pair<int, Request*>> requests) {
    LookQueue *queue = new LookQueue();
    while (!requests.empty()) {
        queue->addRequest(requests.top().second, 0, 0);
        requests.pop();
    }
    return queue;
}


void constituize(int argc, char* argv[], int headPos, std::priority_queue<std::pair<int, Request*>> &in, std::priority_queue<std::pair<int, Request*>> &out){
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

    // Create vector of all requests
    std::vector<Request*> requests;
    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        requests.emplace_back( request);
    }

    // Split vector into constituent unordered queues (in/out)
    // TODO: Fix incorrect insert order, probably by using a vector instead of a priority queue =(
    for (auto &request : requests) {
        if (request->track() >= headPos){
            in.emplace(request->track() * -1, request);
        } else {
            out.emplace(request->track(), request);
        }
    }
}

int main(int argc, char *argv[]) {
    const int randomTest = false;
    int headPos = 20;
    bool headDirection = true; // false = out, true = in
    LookQueue *in_queue = nullptr;
    LookQueue *out_queue = nullptr;

    std::priority_queue<std::pair<int, Request*>> in;
    std::priority_queue<std::pair<int, Request*>> out;

    if (randomTest){
        // placeholder for random test
    }
    else {
        constituize(argc, argv, headPos, in, out);
        in_queue = createLookQueue(in);
        out_queue = createLookQueue(out);
    }

    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the ST Queue." << std::endl;
    std::cout << "Direction is IN" << std::endl;
    std::cout << "Current queue contains." << std::endl;
    in_queue->print();
    if (out_queue->empty()){
        std::cout << "nextQueue is empty." << std::endl;
    } else {
        std::cout << "nextQueue contains." << std::endl;
        out_queue->print();
    }

    delete in_queue;
    delete out_queue;
    return 0;
}
