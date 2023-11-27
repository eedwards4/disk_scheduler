//
// Created by evane on 11/27/2023.
//

#ifndef DISKSIM_X_LOOKQUEUENODE_H
#define DISKSIM_X_LOOKQUEUENODE_H

class Request;

class LookQueueNode {
public:
    LookQueueNode(Request *req);
    LookQueueNode *next();
    void next(LookQueueNode *node);
    Request *request();

private:
    LookQueueNode *_next;
    Request *_request;

};


#endif //DISKSIM_X_LOOKQUEUENODE_H
