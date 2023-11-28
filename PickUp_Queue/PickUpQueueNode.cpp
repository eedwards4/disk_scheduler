//
// Created by evane on 11/27/2023.
//

#include "PickUpQueueNode.h"

class Request;

PickUpQueueNode::PickUpQueueNode(Request *req) : _request(req), _next(nullptr) {}

PickUpQueueNode *PickUpQueueNode::next() {
    return _next;
}

void PickUpQueueNode::next(PickUpQueueNode *node) {
    _next = node;
}

Request *PickUpQueueNode::request() {
    return _request;
}
