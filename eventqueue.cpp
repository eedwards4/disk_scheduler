//
// Created by evane on 12/6/2023.
//

#include <fstream>

#include "eventqueue.h"
#include "CommonFiles/Request.hpp"
#include "FCFS_Queue/FCFSQueue.hpp"
#include "ST_Queue/STQueue.hpp"
#include "PickUp_Queue/PickUpQueue.h"
#include "Look_Queue/LookQueue.h"
#include "CLook_Queue/CLookQueue.h"

using namespace std;

void eventqueue::addAllFromFile(string fileName) { // DEBUG ONLY!!!!

}

void eventqueue::run(string fileName, int headPos) {
    // File stuff
    system("mkdir output");
    ofstream fcfsout = ofstream("output/FCFS");
    ofstream stout = ofstream("output/ST");
    ofstream pickupout = ofstream("output/PickUp");
    ofstream lookout = ofstream("output/Look");
    ofstream clookout = ofstream("output/CLook");
    ifstream in = ifstream(fileName);

    // Queue stuff
    auto *fcfs = new FCFSQueue();
    auto *st = new STQueue();
    auto *pickup = new PickUpQueue();
    auto *look = new LookQueue();
    auto *clook = new CLookQueue();

    int time, track, sector, headTrack = headPos, headSector = 0;
    while (! queue.empty()) {
        EventNode *eNode = queue.front();
        queue.erase(queue.begin());
        if (eNode->isRequestEvent()){
            Request *req = eNode->getRequest()->getRequest();
            fcfs->addRequest(req, headTrack, headSector);
            st->addRequest(req ,headTrack, headSector);
            pickup->addRequest(req, headTrack ,headSector);
            look->addRequest(req, headTrack, headSector);
            clook->addRequest(req, headTrack, headSector);
        } else if (eNode->isTimerEvent()){

        } else if (eNode->isDiskDoneEvent()){

        } else {
            cout << "Error: EventNode is not a valid event type. WHAT DID YOU DO?!" << endl;
            exit(1);
        }
    }
}

void eventqueue::printEventQueue() { // DEBUG ONLY!!!!
    for (auto &i : queue) {
        cout << i->getRequest()->getTime() << " " << i->getRequest()->getTrack() << " " << i->getRequest()->getSector() << endl;
    }
}
