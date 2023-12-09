//
// Created by Ethan Edwards on 12/6/2023.
//

#ifndef DISKSIM_X_EVENTNODE_H
#define DISKSIM_X_EVENTNODE_H

#include "CommonFiles/Request.hpp"

class TimerEvent{
public:
    TimerEvent(int time) {this->time = time;}
    int get() const { return time; }

private:
    int time = -1;
};
class RequestEvent {
public:
    RequestEvent(Request *r, int time) {request = r; this->time = time;}
    Request *getRequest() { return request; }
    int get() { return time; }

private:
    Request *request = nullptr;
    int time = -1;

};
class DiskDoneEvent{
public:
    DiskDoneEvent(int time, int diskID, int arrivalTime)
    {this->time = time; this->diskID = diskID; this->arrivalTime = arrivalTime;}
    int getArrivalTime() {return arrivalTime;}
    int getID() {return diskID;}
    int get() {return time;}

private:
    int arrivalTime = -1;
    int diskID = -1;
    int time = -1;

};
class EventNode {
public:
    EventNode(): timerEvent(nullptr), requestEvent(nullptr), ddoneEvent(nullptr),
                 isTimer(false), isRequest(false), isDDone(false) {}
    void addTimer(TimerEvent *timer) {
        timerEvent = timer;
        isTimer = true;
    }
    void addRequest(RequestEvent *request) {
        requestEvent = request;
        isRequest = true;
    }
    void addDiskDone(DiskDoneEvent *dDone) {
        ddoneEvent = dDone;
        isDDone = true;
    }
    TimerEvent *getTimer() { return timerEvent; }
    RequestEvent *getRequest() { return requestEvent; }
    DiskDoneEvent *getDiskDone() { return ddoneEvent; }
    bool isTimerEvent() { return isTimer; }
    bool isRequestEvent() { return isRequest; }
    bool isDiskDoneEvent() { return isDDone; }
    int getTime(){
        if (isTimer) return timerEvent->get();
        else if (isRequest) return requestEvent->get();
        else if (isDDone) return ddoneEvent->get();
        else return -1;
    }
    std::string type(){
        if (isTimer) return "Timer";
        else if (isRequest) return "Request";
        else if (isDDone) return "DiskDone";
        else return "Error";
    }

private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;
    bool isTimer, isRequest, isDDone;

};

#endif //DISKSIM_X_EVENTNODE_H
