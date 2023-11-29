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
    LookQueue() : in_head{nullptr}, in_tail{nullptr}, out_head{nullptr}, out_tail{nullptr} {}
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~LookQueue();

private:
    LookQueueNode *in_head, *in_tail, *out_head, *out_tail;
    int headPos = -1;

};


#endif //DISKSIM_X_LOOKQUEUE_H
