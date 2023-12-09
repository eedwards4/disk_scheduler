//
// Created by Ethan Edwards on 12/8/2023.
//
#include <vector>
#include <fstream>
#include <iostream>

#include "Disk.h"
#include "eventNode.h"
#include "eventQueue.h"

using namespace std;

void setUpDisks(vector<Disk*> &disks){
    Queue *fcfs = new FCFSQueue();
    Queue *st = new STQueue();
    Queue *pickup = new PickUpQueue();
    Queue *look = new LookQueue();
    Queue *clook = new CLookQueue();

    Disk *fcfsDisk = new Disk(fcfs, "FCFS", 0);
    Disk *stDisk = new Disk(st, "STRACK", 1);
    Disk *pickupDisk = new Disk(pickup, "PICKUP", 2);
    Disk *lookDisk = new Disk(look, "LOOK", 3);
    Disk *clookDisk = new Disk(clook, "CLOOK", 4);

    disks.push_back(fcfsDisk);
    disks.push_back(stDisk);
    disks.push_back(pickupDisk);
    disks.push_back(lookDisk);
    disks.push_back(clookDisk);
}

void setUpFiles(){
    fstream fcfs("output/FCFS_output", ofstream::out | ofstream::trunc);
    fstream st("output/STRACK_output", ofstream::out | ofstream::trunc);
    fstream pickup("output/PICKUP_output", ofstream::out | ofstream::trunc);
    fstream look("output/LOOK_output", ofstream::out | ofstream::trunc);
    fstream clook("output/CLOOK_output", ofstream::out | ofstream::trunc);
    fstream timer("output/TIMER_output", ofstream::out | ofstream::trunc);
    fstream summary("output/SUMMARY_output", ofstream::out | ofstream::trunc);
    if (!fcfs.is_open() || !st.is_open() || !pickup.is_open() || !look.is_open() || !clook.is_open()){
        cout << "ERROR OPENING ONE OR MORE OUTPUT FILES! TERMINATING..." << endl;
        exit(4);
    }

    fcfs << "FCFS REPORT" << endl;
    fcfs << "#Trac Sec  Entr      Init   Comp   Wait    Serv    TmInSys" << endl;
    st << "STRACK REPORT" << endl;
    st << "#Trac Sec  Entr      Init   Comp   Wait    Serv   TmInSys" << endl;
    pickup << "PICK_UP REPORT" << endl;
    pickup << "#Trac Sec  Entr      Init   Comp   Wait    Serv   TmInSys" << endl;
    look << "LOOK REPORT" << endl;
    look << "#Trac Sec  Entr      Init   Comp   Wait    Serv   TmInSys" << endl;
    clook << "C_LOOK REPORT" << endl;
    clook << "#Trac Sec  Entr      Init   Comp   Wait    Serv   TmInSys" << endl;
    timer << "TIMER REPORT" << endl;
    timer << "Time           FCFS       SAME TRACK     PICKUP   C-LOOK        LOOK" << endl;
    summary << "SUMMARY REPORT" << endl;
    summary << " Name    TimeInSystem            WaitTime          ServiceTime           NumInQue" << endl;
    summary << "        Min     Max     Avg     Min    Max    Avg     Min  Max      Avg  Max Avg" << endl;

    fcfs.close();
    st.close();
    pickup.close();
    look.close();
    clook.close();
    timer.close();
    summary.close();
}

void printTimerDump(int curTime, vector<int> dumpData){
    ofstream dump("output/TIMER_output", fstream::app);
    if (dump.is_open()){
        dump << curTime << " ";
        for (int i : dumpData){
            dump << i << " ";
        }
        dump << endl;
        dump.close();
    } else{
        cout << "FAILED TO OPEN TIMER DUMP FILE! TERMINATING..." << endl;
        exit(4);
    }
}

int main(int argc, char* argv[]){
    if (argc != 2){
        cerr << "Usage: " << argv[0] << " <input file>" << endl;
        exit(1);
    }

    // Define base vars
    int timerInterval = 50;
    int curTime = 0;
    vector<Disk*> disks;
    setUpDisks(disks);

    // Set up file stuff
    ifstream inf;
    inf.open(argv[1]);
    if( !inf.is_open()) {
        std::cout << "Unable to open " << argv[1] << ". Terminating...";
        exit(2);
    }
    setUpFiles();

    // Create event queue
    eventQueue *queue = new eventQueue();
    queue->addRequest(inf);
    queue->addTimer(50);

    while (!queue->empty()){
        EventNode *node = queue->get();
        curTime = node->getTime();
        if (node->isRequestEvent()){
            cout << "Request event at time " << curTime << endl;
            cout << "Event contains: " << node->getRequest()->getRequest()->track() << " " << node->getRequest()->getRequest()->sector() << endl;
            // Send the request to each queue
            for (Disk *i : disks){
                int ddone = i->processRequest(node->getRequest()->getRequest(), curTime);
                // Create a new disk done event if this disk has become active
                if (ddone != -1){
                    int diskID = i->getID();
                    queue->addDDone(ddone, diskID, curTime);
                }
            }
            // If there are still objects in the input file, create a new request event
            if (!inf.eof()){
                queue->addRequest(inf);
            }
        } else if (node->isTimerEvent()){
            vector<int> dumpData;
            cout << "Timer event at time " << curTime << endl;
            cout << "Number of events remaining: " << queue->size() << endl;
            cout << "First event is: " << queue->peek()->type() << " at " << queue->peek()->getTime() << endl;
            for (Disk *i : disks){
                dumpData.push_back(i->processTimer());
            }
            printTimerDump(curTime, dumpData);
            if (!queue->empty()){
                queue->addTimer(curTime + timerInterval);
            }
        } else if (node->isDiskDoneEvent()){
            cout << "Disk done event at time " << curTime << endl;
            cout << "Event contains: " << node->getDiskDone()->getID() << endl;
            Disk *d = disks[node->getDiskDone()->getID()];
            int ddone = d->processDiskDone(curTime, node->getDiskDone()->getArrivalTime());
            if (ddone != -1){
                queue->addDDone(ddone, d->getID(), curTime);
            }
        } else{
            cout << "BAD NODE IN EVENT QUEUE! TERMINATING..." << endl;
            exit(3);
        }
        cout << "------------------------------------------------------------" << endl;
    }
    ofstream summary("output/SUMMARY_output", fstream::app);
    for (Disk *i : disks){
        summary << i->getName() << " ";
        i->printSummary(summary);
    }
    return 0;
}