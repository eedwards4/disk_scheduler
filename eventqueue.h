//
// Created by Ethan Edwards on 12/6/2023.
//

#include <vector>

#include "eventNode.h"

#ifndef DISKSIM_X_EVENTQUEUE_H
#define DISKSIM_X_EVENTQUEUE_H


class eventqueue {
public:
    eventqueue() = default;
    void addAllFromFile(std::string fileName); // DEGUG ONLY
    void run(std::string , int headPos);
    void printEventQueue(); // DEBUG ONLY

private:
    std::vector<EventNode *> queue;
};


#endif //DISKSIM_X_EVENTQUEUE_H
