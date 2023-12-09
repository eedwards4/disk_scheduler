//
// Created by Ethan Edwards on 12/8/2023.
//

#ifndef DISKSIM_X_SUMMARY_H
#define DISKSIM_X_SUMMARY_H

#include <string>
#include <fstream>

using namespace std;

class summary {
public:
    summary(string n){name = n;}
    void newTIS(float tis){
        if (tis < minTIS || minTIS == -1){minTIS = tis;}
        if (tis > maxTIS || maxTIS == -1){maxTIS = tis;}
        avgTIS = (avgTIS + tis) / 2;
    }
    void newWT(float wt){
        if (wt < minWT || minWT == -1){minWT = wt;}
        if (wt > maxWT || maxWT == -1){maxWT = wt;}
        avgWT = (avgWT + wt) / 2;
    }
    void newST(float st){
        if (st < minST || minST == -1){minST = st;}
        if (st > maxST || maxST == -1){maxST = st;}
        avgST = (avgST + st) / 2;
    }
    void newInQ(float inq){
        if (inq > maxInQ || maxInQ == -1){maxInQ = inq;}
        avgInQ = (avgInQ + inq) / 2;
    }
    void print(ofstream &out){
        out << name << " " << minTIS << " " << maxTIS << " " << avgTIS << " " << minWT << " " << maxWT << " " << avgWT << " " << minST << " " << maxST << " " << avgST << " " << maxInQ << " " << avgInQ << endl;
    }

private:
    string name; // Name of algorithm
    float minTIS = -1; // Time in System
    float maxTIS = -1;
    float avgTIS = -1;
    float minWT = -1; // Wait time
    float maxWT = -1;
    float avgWT = -1;
    float minST = -1; // Service time
    float maxST = -1;
    float avgST = -1;
    float maxInQ = -1; // NumInQueue
    float avgInQ = -1;

};


#endif //DISKSIM_X_SUMMARY_H
