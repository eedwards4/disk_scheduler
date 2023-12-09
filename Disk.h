//
// Created by evane on 12/8/2023.
//

#ifndef DISKSIM_X_DISK_H
#define DISKSIM_X_DISK_H

#include <string>
#include <vector>
#include <fstream>

#include "FCFS_Queue/FCFSQueue.hpp"
#include "ST_Queue/STQueue.hpp"
#include "PickUp_Queue/PickUpQueue.h"
#include "Look_Queue/LookQueue.h"
#include "CLook_Queue/CLookQueue.h"
#include "CommonFiles/Request.hpp"
#include "summary.h"

using namespace std;

class Disk {
public:
    Disk(Queue *queue, string name, int diskID) {
        waitQueue = queue;
        this->name = name;
        myFile = "output/" + name + "_output";
        this->diskID = diskID;

    }
    int processRequest(Request *req, int curTime);
    int processTimer() {
        if (idle) {return numInQueue;}
        else {return numInQueue + 1;}  // Add 1 if we're currently processing a request
    }
    int processDiskDone(int curTime, int arrivalTime);
    int getID() {return diskID;}
    string getName() {return name;}
    void printSummary(ofstream &out) {sum->print(out);}

private:
    string name, myFile;
    int numInQueue = 0, numProcessed = 0, diskID = -1;
    int headTrack = 0, headSector = 0;
    bool idle = true;
    Queue *waitQueue;
    summary *sum = new summary(name);

    void printRequest(int track, int sector, vector<float> info);
    vector<float> mathTime(int reqTime, int curTime, int reqTrack, int reqSector);
    vector<float> mathTimeToo(int reqTime, int curTime, int reqTrack, int reqSector);
    int dist(int start, int end);
    double rotDist(int start, int end);

};


#endif //DISKSIM_X_DISK_H
