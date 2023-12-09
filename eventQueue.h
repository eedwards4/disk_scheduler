//
// Created by evane on 12/8/2023.
//

#ifndef DISKSIM_X_EVENTQUEUE_H
#define DISKSIM_X_EVENTQUEUE_H

#include <queue>
#include <vector>
#include <fstream>

#include "eventNode.h"
#include "CommonFiles/Request.hpp"

using namespace std;

class eventQueue {
public:
    // Getters
    bool empty() {return queue.empty();}
    EventNode *get() {
        EventNode *tmp = queue.top().second;
        queue.pop();
        return tmp;
    }
    int size() {return queue.size();}
    EventNode *peek() {return queue.top().second;}

    // Setters
    void addRequest(ifstream &in);
    void addTimer(int time);
    void addDDone(int time, int diskID, int arrivalTime);

private:
    priority_queue<pair<int, EventNode*>, vector<pair<int, EventNode*>>, greater<>> queue; // NOTE: The int in the pair exists ONLY for sorting

};


#endif //DISKSIM_X_EVENTQUEUE_H
