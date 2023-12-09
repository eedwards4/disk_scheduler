//
//

#ifndef FCFS_QUEUE_REQUEST_HPP
#define FCFS_QUEUE_REQUEST_HPP

class Request {
public:
    Request(double rTime, int rTrack, int rSector, int rOrder = -1);

    int track();
    int sector();
    double time();
    int order();
    void print();
    void setOrder(int order) { _order = order; }

private:
    double _time;
    int _track, _sector, _order;

};

#endif //FCFS_QUEUE_REQUEST_HPP
