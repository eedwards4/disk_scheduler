//
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>

#include "CommonFiles/Request.hpp"
#include "FCFS_Queue/FCFSQueue.hpp"
#include "ST_Queue/STQueue.hpp"
#include "PickUp_Queue/PickUpQueue.h"
#include "Look_Queue/LookQueue.h"
#include "CLook_Queue/CLookQueue.h"

#include "eventNode.h"

class Disk {
public:
    // a disk is identified by its wait-queue and the name of
    // the disk -- FCFS, ST, etc.
    Disk(Queue *waitQueue, std::string nameOfThisDisk);
    retType processRequest(EventQueue *event, Request *req, ...)
    retType processDiskDoneEvent(EventQueue *event, ...)
};

class EventQueue {
public:
    bool empty() { return queue.empty(); }
    EventNode *getEvent() {
        EventNode *eNode = queue.top().second;
        queue.pop();
        return eNode;
    }

    void addRequest(int time, int track, int sector, int curTrack, int curSector){
        const int transferTime = 0.1;
        EventNode *eNode = new EventNode();
        Request *request = new Request(time, track, sector);
        RequestEvent *rEvent = new RequestEvent(request);
        rEvent->setSeekTime(dist(curTrack, track));
        rEvent->setRotationTime(rotDist(curSector, sector));
        rEvent->setTransferTime(transferTime);
        eNode->addRequest(rEvent);
        queue.emplace(time, eNode);
    }
    void addTimerEvent(int timerEvent){
        int tStamp = tStamp;
        EventNode *eNode = new EventNode();
        TimerEvent *tEvent = new TimerEvent(timerEvent);
        eNode->addTimer(tEvent);
        queue.emplace(tStamp, eNode);
    }

private:
    std::priority_queue<std::pair<int, EventNode *>> queue;
    int dist(int a, int b){
        return abs(a - b) * 3;
    }
    int rotDist(int a, int b){
        if (b > a){
            return b - a * 0.1;
        } else{
            return ((b - a + 30) % 30) * 0.1;
        }
    }
};

int main(int argc, char *argv[]) {
    if (argc != 2) {
        std::cout << "usage: " << argv[0] << " nameOfAnInputFile\n";
        exit(1);
    }
    // Define basic variables
    int initHeadPos = 0;
    int curTime = 0;
    int curTrack = 0;
    int curSector = 0;
    int time, track, sector;
    std::string filename = argv[1];

    // Create all disks
    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();
    Queue *pickup = new PickUpQueue();
    Queue *look = new LookQueue();
    Queue *clook = new CLookQueue();

    Disk *fcfsDisk = new Disk(fcfs, "FCFS");
    Disk *stDisk = new Disk(st, "ST");
    Disk *pickupDisk = new Disk(pickup, "PickUp");
    Disk *lookDisk = new Disk(look, "Look");
    Disk *clookDisk = new Disk(clook, "CLook");

    std::vector<Disk *> disks;
    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);
    disks.push_back(pickupDisk);
    disks.push_back(lookDisk);
    disks.push_back(clookDisk);

    // Create event queue
    EventQueue *eQueue = new EventQueue();

    // Add first request to the event queue
    std::ifstream inputStream;
    inputStream.open(filename, std::ios::in);
    if( ! inputStream.is_open()) {
        std::cout << "Unable to open " << filename << ". Terminating...";
        exit(1);
    }
    inputStream >> time;
    inputStream >> track;
    inputStream >> sector;
    eQueue->addRequest(time, track, sector, curTrack);

    // Set up first timer event
    eQueue->addTimerEvent(50);

    // Process all events
    while( !eQueue->empty() ) {
        EventNode *event = eQueue->getEvent();
        if (event->isRequestEvent()){
            for (Disk *d : disks){
                d->processRequest(eQueue, event->getRequest()->getRequest());
            }
            inputStream >> time;
            inputStream >> track;
            inputStream >> sector;
            eQueue->addRequest(time, track, sector);
        } else if (event->isTimerEvent()){

        } else{

        }
        /*
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
                  */
    }
}
