//
// Created by evane on 11/28/2023.
//

#ifndef DISKSIM_X_CLOOKQUEUENODE_H
#define DISKSIM_X_CCLOOKQUEUENODE_H


class Request;

class CLookQueueNode {
public:
    CLookQueueNode(Request *req);
    CLookQueueNode *next();
    CLookQueueNode *prev();
    void next(CLookQueueNode *node);
    void prev(CLookQueueNode *node);
    Request *request();

private:
    CLookQueueNode *_next;
    Request *_request;

};


#endif //DISKSIM_X_CCLOOKQUEUENODE_H
