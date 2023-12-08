//
// Created by Ethan Edwards on 12/7/23.
//
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <queue>
#include <cfenv>
#include <cmath>

#include "CommonFiles/Request.hpp"
#include "FCFS_Queue/FCFSQueue.hpp"
#include "ST_Queue/STQueue.hpp"
#include "PickUp_Queue/PickUpQueue.h"
#include "Look_Queue/LookQueue.h"
#include "CLook_Queue/CLookQueue.h"

#include "eventNode.h"

using namespace std;

class EventQueue{
public:
    // Getters
    bool empty() {return queue.empty();}
    EventNode *get(int &time){
        EventNode *tmp = queue.top().second;
        time = queue.top().first;
        queue.pop();
        return tmp;
    }

    // Setters
    void addRequest(ifstream &file){
        int time, track, sector; file >> time; file >> track; file >> sector;
        EventNode *tmp = new EventNode;
        Request *r = new Request(time, track, sector);
        RequestEvent *req = new RequestEvent(r);
        tmp->addRequest(req);
        queue.emplace(time, tmp);
    }
    void addTimer(int time){
        EventNode *tmp = new EventNode;
        TimerEvent *t = new TimerEvent(time);
        tmp->addTimer(t);
        queue.emplace(time, tmp);
    }
    void addDiskDone(DiskDoneEvent *ddone){
        EventNode *tmp = new EventNode;
        tmp->addDiskDone(ddone);
        queue.emplace(ddone->getTime(), tmp);
    }

private:
    priority_queue<pair<int, EventNode *>, vector<pair<int, EventNode*>>, greater<pair<int, EventNode*>>> queue;

};

class Disk {
public:
    Disk(Queue *waitQueue, string nameOfThisDisk){
        name = nameOfThisDisk;
        this->waitQueue = waitQueue;
    }
    DiskDoneEvent *processRequest(Request *req, int &headTrack, int &headSector, int curTime){
        if (free){ // If free, send straight to the queue
            free = false;
            // Math time
            float num = entries.size();
            float entr = req->time() * 0.1;
            float init = curTime * 0.1;
            float comp = init + dist(headTrack, req->track()) + rotDist(headSector, req->sector());
            float wait = init - entr;
            float serv = comp - init;
            float TIS = comp - wait;
            // Put all the output into storage
            vector<float> tmp {num, static_cast<float>(req->track()), static_cast<float>(req->sector()), entr, init, comp, wait, serv, TIS};
            entries.push_back(tmp);
            waitQueue->addRequest(req, headTrack, headSector);
            // Set head position to the new request
            headTrack = req->track();
            headSector = req->sector();
            return new DiskDoneEvent(comp, num);
        } else{ // Place in limbo
            limbo.push_back(req);
            return nullptr;
        }
    }
    int processTimer(){
        return limbo.size();
    }
    void processDiskDone(int requestNum, int &headTrack, int &headSector, int curTime){
        free = true;
        if (!limbo.empty()){ // Start processing the first request in limbo
            Request *tmp = limbo.front();
            limbo.erase(limbo.begin());
            // Feed to processRequest
            processRequest(tmp, headTrack, headSector, curTime);
            headTrack = tmp->track();
            headSector = tmp->sector();
        }
    }
    void print(ofstream &out){
        for (int i = 0; i < entries.size(); i++){
            out << "    " << entries[i][0] << "      " << entries[i][1] << "      " << entries[i][2] << "      " << entries[i][3] << "      " << entries[i][4] << "      " << entries[i][5] << "      " << entries[i][6] << "   " << entries[i][7] << "   " << entries[i][8] << endl;
        }
    }
private:
    string name;
    bool free = true;
    const float transferTime = 0.1;
    Queue *waitQueue;
    vector<Request *> limbo;
    vector<vector<float>> entries; // <num>[track][sector][entr][init][comp][wait][serv][tis]

    int dist(float start, float end){
        return abs(start - end) * 3;
    }
    int rotDist(float start, float end){
        if (end > start){return (end - start) * 0.1;}{
            return fmod((end - start + 30), 30) * 0.1;
        }
    }

};

class TimerSnapshot{
public:
    TimerSnapshot(int t, int fcfs, int st, int pickup, int look, int clook){
        time = t;
        this->fcfs = fcfs;
        this->st = st;
        this->pickup = pickup;
        this->look = look;
        this->clook = clook;
    }
    void print(ofstream &out){
        out << time << " " << fcfs << " " << st << " " << pickup << " " << look << " " << clook << endl;
    }

private:
    int time = 0;
    int fcfs = 0;
    int st = 0;
    int pickup = 0;
    int look = 0;
    int clook = 0;

};

class summaryObject{
public:
    summaryObject(string n){
        name = n;
    }
    void newTIS(int tis){
        if (tis < minTIS || minTIS == -1){minTIS = tis;}
        if (tis > maxTIS || maxTIS == -1){maxTIS = tis;}
        avgTIS = (avgTIS + tis) / 2;
    }
    void newWT(int wt){
        if (wt < minWT || minWT == -1){minWT = wt;}
        if (wt > maxWT || maxWT == -1){maxWT = wt;}
        avgWT = (avgWT + wt) / 2;
    }
    void newST(int st){
        if (st < minST || minST == -1){minST = st;}
        if (st > maxST || maxST == -1){maxST = st;}
        avgST = (avgST + st) / 2;
    }
    void newInQ(int inq){
        if (inq > maxInQ || maxInQ == -1){maxInQ = inq;}
        avgInQ = (avgInQ + inq) / 2;
    }
    void print(ofstream &out){
        out << name << " " << minTIS << " " << maxTIS << " " << avgTIS << " " << minWT << " " << maxWT << " " << avgWT << " " << minST << " " << maxST << " " << avgST << " " << maxInQ << " " << avgInQ << endl;
    }

private:
    string name; // Name of algorithm
    int minTIS = -1; // Time in System
    int maxTIS = -1;
    int avgTIS = -1;
    int minWT = -1; // Wait time
    int maxWT = -1;
    int avgWT = -1;
    int minST = -1; // Service time
    int maxST = -1;
    int avgST = -1;
    int maxInQ = -1; // NumInQueue
    int avgInQ = -1;

};

// Print functions
void setupFCFS(Disk *fcfs){
    ofstream fcfs_out("output/FCFS_output");
    fcfs_out << "                                FCFS REPORT" << endl;
    fcfs_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    fcfs->print(fcfs_out);
}
void setupST(Disk *st){
    ofstream st_out("output/STRACK_output");
    st_out << "                                STRACK REPORT" << endl;
    st_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    st->print(st_out);
}
void setupPickUp(Disk *pickup){
    ofstream pickup_out("output/PICKUP_output");
    pickup_out << "                            PICKUP REPORT" << endl;
    pickup_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    pickup->print(pickup_out);
}
void setupLook(Disk *look){
    ofstream look_out("output/LOOK_output");
    look_out << "                                LOOK REPORT" << endl;
    look_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    look->print(look_out);
}
void setupCLook(Disk *clook){
    ofstream clook_out("output/CLOOK_output");
    clook_out << "                              CLOOK REPORT" << endl;
    clook_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    clook->print(clook_out);
}
void setupSummary(vector<summaryObject> &summary){
    ofstream summary_out("output/SUMMARY_output");
    summary_out << "                          SUMMARY REPORT" << endl;
    summary_out << "      Name             TimeInSystem                      WaitTime                   ServiceTime            NumInQue" << endl;
    summary_out << "                 Min       Max       Avg       Min       Max       Avg       Min       Max       Avg       Max       Avg" << endl;
    for (summaryObject i : summary){
        i.print(summary_out);
    }
}
void setupTimer(vector<TimerSnapshot> &timer){
    ofstream timer_out ("output/TIMER_output");
    timer_out << "                              TIMER REPORT" << endl;
    timer_out << "      Time      FCFS    STRACK    PICKUP     CLOOK      LOOK" << endl;
    for (TimerSnapshot i : timer){
        i.print(timer_out);
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        exit(1);
    }

    // Define base vars
    int curTrack = 0, curSector = 0, curTime = 0;
    vector<TimerSnapshot> timer;
    vector<summaryObject> summary {
            summaryObject("FCFS"),
            summaryObject("ST"),
            summaryObject("PickUp"),
            summaryObject("Look"),
            summaryObject("CLook")
    };

    // Set up file stuff
    ifstream inf;
    inf.open(argv[1]);
    if( !inf.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(1);
    }

    // Create disks
    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();
    Queue *pickup = new PickUpQueue();
    Queue *look = new LookQueue();
    Queue *clook = new CLookQueue();

    Disk *fcfsDisk = new Disk(fcfs, "FCFS");
    Disk *stDisk = new Disk(st, "ST");
    Disk *pickupDisk = new Disk(pickup, "PickUp");
    Disk *lookDisk = new Disk(look, "Look");
    Disk *clookDisk = new Disk(clook, "CLook");

    vector<Disk *> disks;
    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);
    disks.push_back(pickupDisk);
    disks.push_back(lookDisk);
    disks.push_back(clookDisk);
    // Wheeeeee

    // Create event queue
    EventQueue *eQueue = new EventQueue();
    eQueue->addRequest(inf);
    eQueue->addTimer(50);

    while (!eQueue->empty()){
        EventNode *node = eQueue->get(curTime); // Get the next node and update the time
        if (node->isRequestEvent()){
            for (Disk *i : disks){ // Process the request through each queue and create DDones
                DiskDoneEvent *tmp = i->processRequest(node->getRequest()->getRequest(), curTrack, curSector, curTime);
                if (tmp != nullptr){
                    eQueue->addDiskDone(tmp);
                }
            }
            if (!inf.eof()){ // Queue the next request
                eQueue->addRequest(inf);
            }
        } else if (node->isTimerEvent()){
            vector<int> data;
            for (Disk *i : disks){ // Get number of in-limbo objects from each queue
                data.push_back(i->processTimer());
            }
            // Write to timer vector (we could just write the data to a file, but I prefer writing everything at the end)
            timer.emplace_back(curTime, data[0], data[1], data[2], data[3], data[4]);
            if (!eQueue->empty()){ // Add a new timer if this was not the last object in the queue
                eQueue->addTimer(curTime + 50);
            }
        } else if (node->isDiskDoneEvent()){
            for (Disk *i : disks){ // Process the DDone through each queue
                i->processDiskDone(node->getDiskDone()->getRNum(), curTrack, curSector, curTime);
            }
        } else{
            cout << "BAD NODE IN EVENT QUEUE. TERMINATING..." << endl;
            exit(1);
        }
    }

    // Create files from data
    system("mkdir -p output");
    setupFCFS(fcfsDisk);
    setupST(stDisk);
    setupPickUp(pickupDisk);
    setupLook(lookDisk);
    setupCLook(clookDisk);
    setupSummary(summary);
    setupTimer(timer);
}