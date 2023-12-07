//
// Created by evane on 11/28/2023.
//

#ifndef DISKSIM_X_CLOOKQUEUE_H
#define DISKSIM_X_CLOOKQUEUE_H

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "CLookQueueNode.h"

class Request;

class CLookQueue : public Queue {
public:
    CLookQueue() : in_head{nullptr}, in_tail{nullptr}, out_head{nullptr}, out_tail{nullptr} {}
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~CLookQueue();

private:
    CLookQueueNode *in_head, *in_tail, *out_head, *out_tail;
    int headPos = -1;

};


#endif //DISKSIM_X_CLOOKQUEUE_H
