//
// Created by Ethan Edwards on 12/8/2023.
//

#include "Disk.h"

int Disk::processRequest(Request *req, int curTime) {
    if (idle){ // Process the request immediately
        vector<float> info = mathTime(req->time(), curTime, req->track(), req->sector());
        printRequest(req->track(), req->sector(), info);
        numProcessed++; idle = false;
        headTrack = req->track();
        headSector = req->sector();
        // Add new data to summary
        sum->newTIS(info[5]);
        sum->newWT(info[3]);
        sum->newST(info[4]);
        sum->newInQ(numInQueue);
        return static_cast<int>(info[2]);
    } else{ // Add the request to the wait queue to be addressed later
        waitQueue->addRequest(req, headTrack, headSector);
        numInQueue++;
        return -1;
    }
}

int Disk::processDiskDone(int curTime, int arrivalTime) {
    if (!waitQueue->empty()){
        Request *req = waitQueue->getRequest();
        vector<float> info = mathTimeToo(arrivalTime, curTime, req->track(), req->sector());
        printRequest(req->track(), req->sector(), info);
        numInQueue--; numProcessed++;
        headTrack = req->track();
        headSector = req->sector();
        // Add new data to summary
        sum->newTIS(info[5]);
        sum->newWT(info[3]);
        sum->newST(info[4]);
        sum->newInQ(numInQueue);
        return static_cast<int>(info[2]);
    } else{
        idle = true;
        return -1;
    }
}

// Helper functions
vector<float> Disk::mathTimeToo(int reqTime, int curTime, int reqTrack, int reqSector){
    float entr = reqTime;
    float init = curTime;
    float comp = init + dist(headTrack, reqTrack) + rotDist(headSector, reqSector) + 0.1;
    float wait = init - entr;
    float serv = comp - init;
    float TIS = serv - wait;
    vector<float> tmp = {entr, init, comp, wait, serv, TIS};
    return tmp;
}
vector<float> Disk::mathTime(int reqTime, int curTime, int reqTrack, int reqSector) {
    float entr = reqTime * 0.1;
    float init = curTime * 0.1;
    float comp = init + dist(headTrack, reqTrack) + rotDist(headSector, reqSector) + 0.1;
    float wait = init - entr;
    float serv = comp - init;
    float TIS = serv - wait;
    vector<float> tmp = {entr, init, comp, wait, serv, TIS};
    return tmp;
}

int Disk::dist(int start, int end) {
    return abs(start - end) * 3;
}

double Disk::rotDist(int start, int end) {
    if (end > start){
        return (end - start) * 0.1;
    } else{
        return ((end - start + 30) % 30) * 0.1;
    }
}

void Disk::printRequest(int track, int sector, vector<float> info) {
    ofstream out(myFile, fstream::app);
    if (out.is_open()){
        out << numProcessed << " ";
        out << track << " ";
        out << sector << " ";
        for (float i : info){
            out << i << " ";
        }
        out << endl;
        out.close();
    } else{
        cout << "ERROR OPENING THE OUTPUT FILE " << myFile << "! TERMINATING..." << endl;
        exit(4);
    }
}