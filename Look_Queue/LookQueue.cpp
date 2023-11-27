//
// Created by evane on 11/27/2023.
//

#include "LookQueue.h"

void LookQueue::addRequest(Request *request, int cRWHeadTrack, int cRWHeadSector) {
    LookQueueNode *newNode = new LookQueueNode(request);
    LookQueueNode *currNode = head;
    LookQueueNode *prevNode = nullptr;
    bool added = false;

    if (head == nullptr) {
        head = newNode;
        tail = newNode;
        return;
    }

    while (currNode != nullptr) {
        if (currNode->request()->track() > cRWHeadTrack) {
            if (prevNode == nullptr) {
                newNode->next(currNode);
                head = newNode;
                added = true;
                break;
            } else {
                newNode->next(currNode);
                prevNode->next(newNode);
                added = true;
                break;
            }
        }
        prevNode = currNode;
        currNode = currNode->next();
    }

    if (!added) {
        tail->next(newNode);
        tail = newNode;
    }
}
