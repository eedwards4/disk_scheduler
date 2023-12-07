//
// Created by Ethan Edwards on 12/6/2023.
//

#ifndef DISKSIM_X_EVENTNODE_H
#define DISKSIM_X_EVENTNODE_H

#include "CommonFiles/Request.hpp"

class TimerEvent{
public:
    TimerEvent(int timer) {timerEvent = timer;}
    int get() const { return timerEvent; }

private:
    int timerEvent;
};
class RequestEvent {
public:
    RequestEvent(Request *r) {request = r;}
    Request *getRequest() { return request; }
    void setSeekTime(int n) {seekTime = n;}
    void setRotationTime(int n) {rotationTime = n;}
    void setTransferTime(int n) {transferTime = n;}
    int getST() {return seekTime;}
    int getRT() {return rotationTime;}
    int getTT() {return transferTime;}
    int getAT() {
        return seekTime + rotationTime + transferTime;
    }

private:
    Request *request = nullptr;
    int seekTime = 0,
    rotationTime = 0,
    transferTime = 0;
};
class DiskDoneEvent;
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

private:
    TimerEvent *timerEvent;
    RequestEvent *requestEvent;
    DiskDoneEvent *ddoneEvent;
    bool isTimer, isRequest, isDDone;

};

#endif //DISKSIM_X_EVENTNODE_H
