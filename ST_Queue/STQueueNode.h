//
// Created by evane on 11/27/2023.
//

#ifndef DISKSIM_X_STQUEUENODE_H
#define DISKSIM_X_STQUEUENODE_H

class Request;

class STQueueNode {
public:
    STQueueNode(Request *req);
    STQueueNode *next();
    void next(STQueueNode *node);
    Request *request();

private:
    STQueueNode *_next;
    Request *_request;

};


#endif //DISKSIM_X_STQUEUENODE_H
