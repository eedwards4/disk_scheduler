//
//

#include "STQueue.hpp"
#include "../CommonFiles/Request.hpp"

void STQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    STQueueNode *stNode = new STQueueNode(request, cRWHeadTrack, cRWHeadSector);
    if (empty()){
        head = stNode;
        tail = stNode;
    } else {
        tail->next(stNode);
        tail = stNode;
    }
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
    for (auto cur = head; cur; cur = cur->next()){
        cur->request()->print();
    }
}

STQueue::~STQueue() {
    while (head != nullptr){
        STQueueNode *node = head;
        head = node->next();
        delete node;
    }
}