//
// Created by evane on 11/27/2023.
//

#ifndef DISKSIM_X_PICKUPQUEUENODE_H
#define DISKSIM_X_PICKUPQUEUENODE_H


class Request;

class PickUpQueueNode {
public:
    PickUpQueueNode(Request *req);
    PickUpQueueNode *next();
    void next(PickUpQueueNode *node);
    Request *request();

private:
    PickUpQueueNode *_next;
    Request *_request;

};


#endif //DISKSIM_X_PICKUPQUEUENODE_H
