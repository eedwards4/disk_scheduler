//
// Created by evane on 11/27/2023.
//

#ifndef DISKSIM_X_LOOKQUEUE_H
#define DISKSIM_X_LOOKQUEUE_H

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "LookQueueNode.h"

class Request;

class LookQueue : public Queue {
public:
    LookQueue() : head{nullptr}, tail{nullptr} {}
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~LookQueue();

private:
    LookQueueNode *head, *tail;

};


#endif //DISKSIM_X_LOOKQUEUE_H
