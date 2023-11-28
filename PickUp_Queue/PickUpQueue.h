//
// Created by evane on 11/27/2023.
//

#ifndef DISKSIM_X_PICKUPQUEUE_H
#define DISKSIM_X_PICKUPQUEUE_H


#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "PickUpQueueNode.h"

class Request;

class PickUpQueue : public Queue {
public:
    PickUpQueue() : head{nullptr}, tail{nullptr} {}
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~PickUpQueue();

private:
    PickUpQueueNode *head, *tail;

};


#endif //DISKSIM_X_PICKUPQUEUE_H
