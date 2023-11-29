//
//

#ifndef DISKSIM_X_STQUEUE_HPP
#define DISKSIM_X_STQUEUE_HPP

#include <iostream>
#include "../CommonFiles/Queue.hpp"
#include "STQueueNode.h"

class Request;

class STQueue : public Queue {
public:
    STQueue() : head{nullptr}, tail{nullptr} {}
    virtual void addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector);
    virtual Request *getRequest();
    virtual bool empty();
    virtual void print();
    virtual ~STQueue();

private:
    STQueueNode *head, *tail;
    int headPos = -1;

};


#endif //DISKSIM_X_STQUEUE_HPP
