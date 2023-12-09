//
// Created by evane on 12/8/2023.
//

#include "eventQueue.h"

void eventQueue::addRequest(ifstream &in) {
    int track = -1, sector = -1, time = -1;
    in >> time; in >> track; in >> sector;
    if (time == -1 || track == -1 || sector == -1) return; // End of file
    EventNode *tmp = new EventNode();
    auto *req = new Request(time, track, sector);
    auto *re = new RequestEvent(req, time);
    tmp->addRequest(re);
    queue.emplace(time * 0.1, tmp);
}

void eventQueue::addTimer(int time) {
    EventNode *tmp = new EventNode();
    auto *te = new TimerEvent(time);
    tmp->addTimer(te);
    queue.emplace(time, tmp);
}

void eventQueue::addDDone(int time, int diskID, int arrivalTime) {
    EventNode *tmp = new EventNode();
    auto *dde = new DiskDoneEvent(time, diskID, arrivalTime);
    tmp->addDiskDone(dde);
    queue.emplace(time, tmp);
}