//
// Created by evane on 11/27/2023.
//

#include "PickUpQueue.h"
#include "../CommonFiles/Request.hpp"

void PickUpQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    PickUpQueueNode *lookNode = new PickUpQueueNode(request);
    // Set head position for print
    if (headPos == -1){headPos = cRWHeadTrack;}
    if (request->track() >= cRWHeadTrack) { // Add stuff to IN queue
        if (pickup_head == nullptr){ // First object
            pickup_head = lookNode;
            pickup_tail = lookNode;
            return;
        }
        // Handle duplicate objects
        PickUpQueueNode *tmp = pickup_head;
        while (tmp != pickup_tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle new objects
        tmp = pickup_head;
        if (tmp->request()->track() > request->track()){ // Handle head change
            lookNode->next(tmp);
            pickup_head = lookNode;
            return;
        }
        while (tmp != pickup_tail){
            if (tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Add to the end if no slot
        pickup_tail->next(lookNode);
        pickup_tail = lookNode;
    }
    else{ // Add stuff to OUT queue
        if (detritus_head == nullptr){ // First object
            detritus_head = lookNode;
            detritus_tail = lookNode;
            return;
        }
        // Handle duplicate objects
        PickUpQueueNode *tmp = detritus_head;
        while (tmp != detritus_tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle new objects
        tmp = detritus_head;
        if (tmp->request()->track() < request->track()){ // Handle head change
            lookNode->next(tmp);
            detritus_head = lookNode;
            return;
        }
        while (tmp != detritus_tail){
            if (tmp->next()->request()->track() < request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Add to the end if no slot
        detritus_tail->next(lookNode);
        detritus_tail = lookNode;
    }
}

Request *PickUpQueue::getRequest() {
    if (empty()){
        std::cout << "Calling PickUpQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    if (pickup_head != nullptr){
        PickUpQueueNode *pickUpNode = pickup_head;
        Request *request = pickUpNode->request();
        pickup_head = pickup_head->next();
        if (pickup_head == nullptr){
            pickup_tail = nullptr;
        }
        delete pickUpNode;
        return request;
    }
    PickUpQueueNode *detritusNode = detritus_head;
    Request *request = detritusNode->request();
    detritus_head = detritus_head->next();
    if (detritus_head == nullptr){
        detritus_tail = nullptr;
    }
    delete detritusNode;
    return request;
}

bool PickUpQueue::empty() {
    return pickup_head == nullptr && detritus_head == nullptr;
}

void PickUpQueue::print() {
    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the ST Queue." << std::endl;
    std::cout << "Printing the nodes in Pick Up Queue starts..." << std::endl;
    for (auto cur = pickup_head; cur; cur = cur->next()){
        cur->request()->print();
    }
    if (detritus_head != nullptr){
        for (auto curr = detritus_head; curr; curr = curr->next()){
            curr->request()->print();
        }
    }
    std::cout << "Printing the nodes in Pick up Queue ends..." << std::endl;
}

PickUpQueue::~PickUpQueue() {
    while (pickup_head != nullptr){
        PickUpQueueNode *node = pickup_head;
        pickup_head = node->next();
        delete node;
    }
}