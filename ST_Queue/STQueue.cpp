//
//

#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"

void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode *stNode = new STQueueNode(request);
    // Set head position for print
    if (headPos == -1){headPos = cRWHeadTrack;}
    if (empty()){
        head = stNode;
        tail = stNode;
        return;
    } else if (request->track() == cRWHeadTrack){
        stNode->next(head);
        head = stNode;
        return;
    } else {
        STQueueNode *tmp = head;
        while (tmp != tail){
            if (tmp->request()->track() == request->track() && tmp->next()->request()->track() != request->track()){
                stNode->next(tmp->next());
                tmp->next(stNode);
                return;
            }
            tmp = tmp->next();
        }
    }
    tail->next(stNode);
    tail = stNode;
}

Request *STQueue::getRequest() {
    if (empty()){
        std::cout << "Calling STQueue::getRequest() on an empty queue. Terminating...\n";
        exit(1);
    }
    STQueueNode *stNode = head;
    Request *request = stNode->request();
    head = head->next();
    if (head == nullptr){
        tail = nullptr;
    }
    delete stNode;
    return request;
}

bool STQueue::empty() {
    return head == nullptr;
}

void STQueue::print() {
    std::cout << "Read/write head was set to " << headPos << " when inserting requests to the ST Queue." << std::endl;
    std::cout << "Printing the nodes in ST Queue starts..." << std::endl;
    for (auto cur = head; cur; cur = cur->next()){
        cur->request()->print();
    }
    std::cout << "Printing the nodes in ST Queue ends..." << std::endl;
}

STQueue::~STQueue() {
    while (head != nullptr){
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}