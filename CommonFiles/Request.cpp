//
//

#include <iostream>
#include "Request.hpp"

Request::Request(double rTime, int rTrack, int rSector, int rOrder) : _time(rTime), _track(rTrack), _sector(rSector), _order(rOrder) {}

int Request::track() { return _track; }

int Request::sector() { return _sector; }

double Request::time() { return _time; }

int Request::order() { return _order; }

void Request::print() {
    std::cout << time() << " " << track() << " " << sector() << std::endl;
}
