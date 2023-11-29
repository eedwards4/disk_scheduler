//
// Created by Ethan Edwards on 11/27/2023.
//

#include "LookQueue.h"
#include "../CommonFiles/Request.hpp"

void LookQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    LookQueueNode *lookNode = new LookQueueNode(request);
    // std::cout << "Working on request " << cRWHeadSector << std::endl; // DEBUG
    if (request->track() >= cRWHeadTrack){
        if (in_head == nullptr){
            in_head = lookNode;
            in_tail = lookNode;
            return;
        }
        // Handle duplicates
        LookQueueNode *tmp = in_head;
        while (tmp != in_tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() != request->track()){
                lookNode->next(tmp->next());
                lookNode->prev(tmp);
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle non-duplicates
        tmp = in_head;
        while (tmp != in_tail){
            if (request->track() < tmp->request()->track()){
                lookNode->next(tmp);
                lookNode->prev(tmp->prev());
                tmp->prev(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle endpoints
        in_tail->next(lookNode);
        lookNode->prev(in_tail);
        in_tail = lookNode;
    } else {
        if (out_head == nullptr){
            out_head = lookNode;
            out_tail = lookNode;
            return;
        }
        // Handle duplicates
        LookQueueNode *tmp = out_head;
        while (tmp != out_tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() != request->track()){
                lookNode->next(tmp->next());
                lookNode->prev(tmp);
                tmp->next(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle non-duplicates
        tmp = out_head;
        while (tmp != out_tail){
            if (request->track() < tmp->request()->track()){
                lookNode->next(tmp);
                lookNode->prev(tmp->prev());
                tmp->prev(lookNode);
                return;
            }
            tmp = tmp->next();
        }
        // Handle endpoints
        out_tail->next(lookNode);
        lookNode->prev(out_tail);
        out_tail = lookNode;
    }
}

Request *LookQueue::getRequest() {
    if (empty()){
        std::cout << "Calling LookQueueNode::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    if (in_head != nullptr){
        LookQueueNode *lookNode = in_head;
        Request *request = lookNode->request();
        in_head = in_head->next();
        if (in_head == nullptr){
            in_tail = nullptr;
        }
        delete lookNode;
        return request;
    }
    LookQueueNode *lookNode = out_head;
    Request *request = lookNode->request();
    out_head = out_head->next();
    if (out_head == nullptr){
        out_tail = nullptr;
    }
    delete lookNode;
    return request;
}

bool LookQueue::empty() {
    return in_head == nullptr && out_head == nullptr;
}

void LookQueue::print() {
    std::cout << "Direction is IN" << std::endl;
    std::cout << "Current queue contains." << std::endl;
    for (auto cur = in_head; cur; cur = cur->next()){
        cur->request()->print();
    }
    if (out_head != nullptr){
        std::cout << "nextQueue contains." << std::endl;
        for (auto cur = out_head; cur; cur = cur->next()){
            cur->request()->print();
        }
    } else{std::cout << "nextQueue is empty." << std::endl;}
}

LookQueue::~LookQueue() {
    while (in_head != nullptr){
        LookQueueNode *node = in_head;
        in_head = node->next();
        delete node;
    }
    while (out_head != nullptr){
        LookQueueNode *node = out_head;
        out_head = node->next();
        delete node;
    }
}
