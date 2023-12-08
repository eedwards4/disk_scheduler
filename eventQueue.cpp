//
// Created by evane on 12/8/2023.
//

#include "eventQueue.h"

void eventQueue::addRequest(ifstream &in) {
    int track, sector, time;
    in >> time; in >> track; in >> sector;
    EventNode *tmp = new EventNode();
    auto *req = new Request(track, sector, time);
    auto *re = new RequestEvent(req, time);
    tmp->addRequest(re);
    queue.emplace(time, tmp);
}

void eventQueue::addTimer(int time) {
    EventNode *tmp = new EventNode();
    auto *te = new TimerEvent(time);
    tmp->addTimer(te);
    queue.emplace(time, tmp);
}

void eventQueue::addDDone(int time) {
    EventNode *tmp = new EventNode();
    auto *dde = new DiskDoneEvent(time);
    tmp->addDiskDone(dde);
    queue.emplace(time, tmp);
}