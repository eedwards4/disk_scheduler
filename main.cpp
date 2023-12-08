//
// Created by Ethan Edwards on 12/8/2023.
//
#include <vector>
#include <fstream>
#include <iostream>

#include "Disk.h"
#include "eventNode.h"
#include "eventQueue.h"
#include "CommonFiles/Request.hpp"

using namespace std;

void setUpDisks(vector<Disk*> &disks){
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

    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);
    disks.push_back(pickupDisk);
    disks.push_back(lookDisk);
    disks.push_back(clookDisk);
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        exit(1);
    }

    // Define base vars
    int curTrack = 0, curSector = 0, curTime = 0;
    vector<Disk*> disks;
    setUpDisks(disks);

    // Set up file stuff
    ifstream inf;
    inf.open(argv[1]);
    if( !inf.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(2);
    }

    // Create event queue
    eventQueue *queue = new eventQueue();
    queue->addRequest(inf);
    queue->addTimer(50);

    while (!queue->empty()){
        EventNode *node = queue->get();
        curTime = node->getTime();
        if (node->isRequestEvent()){
            // Send the request to each queue

            // If there are still objects in the input file, create a new request event

        } else if (node->isTimerEvent()){

        } else if (node->isDiskDoneEvent()){

        } else{
            cout << "BAD NODE IN EVENT QUEUE! TERMINATING..." << endl;
            exit(3);
        }
    }
    return 0;
}