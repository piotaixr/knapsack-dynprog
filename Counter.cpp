/* 
 * File:   Counter.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 11 juillet 2013, 16:04
 */

#include "Counter.h"

using namespace std;

Counter::Counter(string name) : name(name), state(CREATED) {
}

Counter::Counter(const Counter& orig) : name(orig.name), state(orig.state), begin(orig.begin), end(orig.end) {
}

Counter::~Counter() {
}

timespec Counter::diff(timespec start, timespec end) const {
    timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0) {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    } else {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}
