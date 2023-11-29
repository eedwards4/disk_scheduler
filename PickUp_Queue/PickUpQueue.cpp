//
// Created by evane on 11/27/2023.
//

#include "PickUpQueue.h"
#include "../CommonFiles/Request.hpp"

void PickUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    PickUpQueueNode *PickUpNode = new PickUpQueueNode(request);
    if (empty()){
        head = PickUpNode;
        tail = PickUpNode;
        return;
    } else if (request->track() == cRWHeadTrack){
        PickUpNode->next(head);
        head = PickUpNode;
        return;
    } else {
        PickUpQueueNode *tmp = head;
        while (tmp != tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() != request->track()){
                PickUpNode->next(tmp->next());
                tmp->next(PickUpNode);
                return;
            }
            tmp = tmp->next();
        }
    }
    tail->next(PickUpNode);
    tail = PickUpNode;
}

Request *PickUpQueue::getRequest() {
    if (empty()){
        std::cout << "Calling PickUpQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    PickUpQueueNode *pickUpNode = head;
    Request *request = pickUpNode->request();
    head = head->next();
    if (head == nullptr){
        tail = nullptr;
    }
    delete pickUpNode;
    return request;
}

bool PickUpQueue::empty() {
    return head == nullptr;
}

void PickUpQueue::print() {
    for (auto cur = head; cur; cur = cur->next()){
        cur->request()->print();
    }
}

PickUpQueue::~PickUpQueue() {
    while (head != nullptr){
        PickUpQueueNode *node = head;
        head = node->next();
        delete node;
    }
}