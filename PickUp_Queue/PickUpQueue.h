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
    PickUpQueue() : pickup_head{nullptr}, pickup_tail{nullptr}, detritus_head{nullptr}, detritus_tail{nullptr} {}
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~PickUpQueue();

private:
    PickUpQueueNode *pickup_head, *pickup_tail, *detritus_head, *detritus_tail;
    int headPos = -1;

};


#endif //DISKSIM_X_PICKUPQUEUE_H
