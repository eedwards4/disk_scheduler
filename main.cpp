//
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "eventNode.h"
#include "eventqueue.h"

int main(int argc, char* argv[]){
    if (!(argc == 2)){
        std::cout << "Usage: ./disksim <input file>" << std::endl;
        return 1;
    }
    std::string inputFileName = argv[1];
    auto *eQueue = new eventqueue();
    eQueue->run(inputFileName, 0);
    return 0;
}

/*
class Disk {
public:
    // a disk is identified by its wait-queue and the name of
    // the disk -- FCFS, ST, etc.
    Disk(Queue *waitQueue, std::string nameOfThisDisk);
    retType processRequest(EventQueue *event, Requset *req, ...)
    retType processDiskDoneEvent(EventQueue *event, ...)
};

class EventQueue {

};

int main() {
    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();

    Disk *fcfsDisk = new Disk(fcfs, "FCFS");
    Disk *stDisk = new Disk(st, "ST");

    std::vector<Disk *> disks;
    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);

    EventQueue *eQueue = new EventQueue();

    eQueue->addRequest("add a request to the event queue");
    eQueue->addTimerEvent("add a timer event for time 50");

    while( ! eQueue->empty() ) {
        EventNode *event = eQueue->getEvent();
        process event:
            1. event is a request event:
                  give this request to every disk using processRequest

            2. event is a timer event:
                  ask each disk to provide the number of entries in its
                       wait queue
                  if eQueue is not empty, add a new timer event to it.

            3. event is a disk-done event:
                  event node has access to the disk whose disk-done
                      event was just removed from the event queue

                  disk->processDiskDoneEvent(eQueue, ...)
    }
}
*/