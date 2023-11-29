//
// Created by Ethan Edwards on 11/27/2023.
//

#include "CLookQueue.h"
#include "../CommonFiles/Request.hpp"

void CLookQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    CLookQueueNode *lookNode = new CLookQueueNode(request);
    // Set head position for print
    if (headPos == -1){headPos = cRWHeadTrack;}
    if (request->track() >= cRWHeadTrack) { // Add stuff to IN queue
        if (in_head == nullptr){ // First object
            in_head = lookNode;
            in_tail = lookNode;
            return;
        }
        // Handle duplicate objects
        CLookQueueNode *tmp = in_head;
        while (tmp != in_tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle new objects
        tmp = in_head;
        if (tmp->request()->track() > request->track()){ // Handle head change
            lookNode->next(tmp);
            in_head = lookNode;
            return;
        }
        while (tmp != in_tail){
            if (tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Add to the end if no slot
        in_tail->next(lookNode);
        in_tail = lookNode;
    }
    else{ // Add stuff to OUT queue
        if (out_head == nullptr){ // First object
            out_head = lookNode;
            out_tail = lookNode;
            return;
        }
        // Handle duplicate objects
        CLookQueueNode *tmp = out_head;
        while (tmp != out_tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle new objects
        tmp = out_head;
        if (tmp->request()->track() > request->track()){ // Handle head change
            lookNode->next(tmp);
            out_head = lookNode;
            return;
        }
        while (tmp != out_tail){
            if (tmp->next()->request()->track() > request->track()){
                lookNode->next(tmp->next());
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Add to the end if no slot
        out_tail->next(lookNode);
        out_tail = lookNode;
    }
}

Request *CLookQueue::getRequest() {
    if (empty()){
        std::cout << "Calling CLookQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    if (in_head != nullptr){
        CLookQueueNode *lookNode = in_head;
        Request *request = lookNode->request();
        in_head = in_head->next();
        if (in_head == nullptr){
            in_tail = nullptr;
        }
        delete lookNode;
        return request;
    }
    CLookQueueNode *lookNode = out_head;
    Request *request = lookNode->request();
    out_head = out_head->next();
    if (out_head == nullptr){
        out_tail = nullptr;
    }
    delete lookNode;
    return request;
}

bool CLookQueue::empty() {
    return in_head == nullptr && out_head == nullptr;
}

void CLookQueue::print() {
    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the Look Queue." << std::endl;
    std::cout << "Current queue contains." << std::endl;
    for (auto cur = in_head; cur; cur = cur->next()){
        cur->request()->print();
    }
    if (out_head != nullptr){
        std::cout << "Next queue contains." << std::endl;
        for (auto cur = out_head; cur; cur = cur->next()){
            cur->request()->print();
        }
    } else{std::cout << "nextQueue is empty." << std::endl;}
}

CLookQueue::~CLookQueue() {
    while (in_head != nullptr){
        CLookQueueNode *node = in_head;
        in_head = node->next();
        delete node;
    }
    while (out_head != nullptr){
        CLookQueueNode *node = out_head;
        out_head = node->next();
        delete node;
    }
}
