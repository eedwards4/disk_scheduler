//
// Created by Ethan Edwards on 12/7/23.
//
#include <iostream>
#include <fstream>
#include <cstdlib>

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

private:

};

class Disk {
public:
    Disk(Queue *waitQueue, string nameOfThisDisk){
        name = nameOfThisDisk;
        this->waitQueue = waitQueue;
    }
    DiskDoneEvent *processRequest(Request *req, int headTrack, int headSector){
        if (free){
            free = false;
            waitQueue->addRequest(req, headTrack, headSector);
            // Start filling out entry and set up disk done event
        }

    }
    void processTimer(int time){
        // Return status of disk
    }
    void processDiskDone(Request *req, int headTrack, int headSector){
        free = true;
        // Finish filling out entry
    }
    void print(ofstream &out){
        for (int i = 0; i < entries.size(); i++){
            out << "    " << i << " " << entries[i][0] << " " << entries[i][1] << " " << entries[i][2] << " " << entries[i][3] << " " << entries[i][4] << " " << entries[i][5] << " " << entries[i][6] << " " << entries[i][7] << endl;
        }
    }
private:
    string name;
    bool free = true;
    Queue *waitQueue;
    vector<vector<int>> entries; // <num>[track][sector][entr][init][comp][wait][serv][tis]

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
    int time = 0.00;
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

ofstream setupFCFS(){
    ofstream fcfs_out("output/FCFS_output");
    fcfs_out << "                                FCFS REPORT" << endl;
    fcfs_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    return fcfs_out;
}

ofstream setupST(){
    ofstream st_out("output/STRACK_output");
    st_out << "                                STRACK REPORT" << endl;
    st_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    return st_out;
}

ofstream setupPickUp(){
    ofstream pickup_out("output/PICKUP_output");
    pickup_out << "                            PICKUP REPORT" << endl;
    pickup_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    return pickup_out;
}

ofstream setupLook(){
    ofstream look_out("output/LOOK_output");
    look_out << "                                LOOK REPORT" << endl;
    look_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    return look_out;
}

ofstream setupCLook(){
    ofstream clook_out("output/CLOOK_output");
    clook_out << "                              CLOOK REPORT" << endl;
    clook_out << "    # Trac  Sec      Entr      Init      Comp      Wait      Serv   TmInSys" << endl;
    return clook_out;
}

ofstream setupSummary(){
    ofstream summary_out("output/SUMMARY_output");
    summary_out << "                          SUMMARY REPORT" << endl;
    summary_out << "      Name             TimeInSystem                      WaitTime                   ServiceTime            NumInQue" << endl;
    summary_out << "                 Min       Max       Avg       Min       Max       Avg       Min       Max       Avg       Max       Avg" << endl;
    return summary_out;
}

ofstream setupTimer(){
    ofstream timer_out ("output/TIMER_output");
    timer_out << "                              TIMER REPORT" << endl;
    timer_out << "      Time      FCFS    STRACK    PICKUP     CLOOK      LOOK" << endl;
    return timer_out;
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        exit(1);
    }

    // Define base vars
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

    // Actually do the thing
    //
    //
    //
    // yeah

    // Create files from data
    system("mkdir -p output");
    ofstream fcfs_out = setupFCFS();
    ofstream st_out = setupST();
    ofstream pickup_out = setupPickUp();
    ofstream look_out = setupLook();
    ofstream clook_out = setupCLook();
    ofstream summary_out = setupSummary();
    ofstream timer_out = setupTimer();
}