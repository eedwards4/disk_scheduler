//
// Created by evane on 11/27/2023.
//

#include "LookQueue.h"
#include "../CommonFiles/Request.hpp"

void LookQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {

}

Request *LookQueue::getRequest() {
    if (empty()){
        std::cout << "Calling LookQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    LookQueueNode *lookNode = head;
    Request *request = lookNode->request();
    head = head->next();
    if (head == nullptr){
        tail = nullptr;
    }
    delete lookNode;
    return request;
}

bool LookQueue::empty() {
    return head == nullptr;
}

void LookQueue::print() {
    for (auto cur = head; cur; cur = cur->next()){
        cur->request()->print();
    }
}

LookQueue::~LookQueue() {
    while (head != nullptr){
        LookQueueNode *node = head;
        head = node->next();
        delete node;
    }
}
