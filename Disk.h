//
// Created by evane on 12/8/2023.
//

#ifndef DISKSIM_X_DISK_H
#define DISKSIM_X_DISK_H

#include <string>

#include "FCFS_Queue/FCFSQueue.hpp"
#include "ST_Queue/STQueue.hpp"
#include "PickUp_Queue/PickUpQueue.h"
#include "Look_Queue/LookQueue.h"
#include "CLook_Queue/CLookQueue.h"

using namespace std;

class Disk {
public:
    Disk(Queue *queue, string name);
    int processRequest(Request *req, int headTrack, int headSector, int curTime);
    int processTimer() {return 0; /*Return the number of objects that still need to be processed*/}
    void processDiskDone();

private:
    string name;
    Queue *queue;

};


#endif //DISKSIM_X_DISK_H
