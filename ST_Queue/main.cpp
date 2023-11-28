//
//

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

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
    std::vector<std::pair<int, Request*>> requests;

    int time, track, sector;
    while(inputStream >> time && inputStream >> track && inputStream >> sector) {
        auto *request = new Request(time, track, sector);
        requests.emplace_back(std::make_pair(0, request));
    }

    // This would be done differently for a real program, since the queue would need to keep up with active requests
    // (e.g some kind of auto-clear function to clear the queue after a certain size)
    for (auto &request : requests) {
        if (request.first == 0) { // Add untouched requests to the queue
            queue->addRequest(request.second, 0, 0);
            request.first = 1; // Mark the request as added
            for (auto &request2 : requests) {
                if (request2.first == 0 && request.second->track() == request2.second->track()) { // Add requests that are the same as the current request to the queue
                    queue->addRequest(request2.second, 0, 0);
                    request2.first = 1; // Mark the request as added
                }
            }
        }
    }

    return queue;
}

int main(int argc, char *argv[]) {
    const int randomTest = false;
    int headPos = 0;
    STQueue *queue = nullptr;

    if (randomTest){
        // placeholder for random test
    }
    else {
        queue = createSTQueue(argc, argv, headPos);
    }

    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the ST Queue." << std::endl;
    std::cout << "Printing the nodes in ST Queue starts..." << std::endl;
    queue->print();
    std::cout << "Printing the nodes in ST Queue ends..." << std::endl;
    delete queue;

    return 0;
}
