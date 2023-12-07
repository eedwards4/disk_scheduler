//
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>

#include "/CommonFiles/Request.hpp"
#include "/FCFS_Queue/FCFSQueue.hpp"
#include "/ST_Queue/STQueue.hpp"
#include "PickUp_Queue/PickUpQueue.h"
#include "Look_Queue/LookQueue.h"
#include "CLook_Queue/CLookQueue.h"


class Disk {
public:
    Disk(Queue *waitQueue, std::string diskName);
    retType processRequest(EventQueue *eventQueue, Request *req)
           // if the disk is busy, adds the req to the wait queue
           // otherwise, starts serving this request and adds
           // a diskdone event to eventQueue

    retType processDiskDone(EventQueue *eventQueue)
           // collects stats regarding the request that was just finished
           // if wait-queue is not empty, get a request from it
           //     and start serving it. This will create a diskdone event.
           // if the wait queue is emtpy, set the status of the disk to
           // idle

    int processTimer()
           // keeps track of the number of elements in its wait queue
           // and returns that number.

};

class EventQueue {
public:
    // a sorted linked list of event nodes.

};

int main() {

    FCFSQueue *fcfsQueue = new FCFSQueue();
    STQueue *stQueue = new STQueue();

    Disk *fcfsDisk = new Disk(fcfsQueue, "FCFS");
    Disk *stDisk = new Disk(stQueue, "ST");

    std::vector<Disk *> disks;
    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);

    EventQueue *eQueue = new EventQueue();

    eQueue->addEvent(/* add a timer event node */);
    eQueue->addEvent(/* add a request event node */);

    while( ! eQueue->empty() ) {
        EventNode *event = eQueue->getEvent();
        /*
        1. Event is a request
              if there is another request in input, read it and
                   add it to the event queue
              give this request to all disks

        2. Event is a diskdone event
              diskdoneDisk->processDiskDone(eQueue)

        3. Event is a timer event
              ask each disk for the number of entries (requests) in its
              wait queue

              if eQueue is not empty, add a new timer event to it
                 for simulation-time + 50 ms.
              */

    }

    // print out stats

}