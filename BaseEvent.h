/* 
 * File:   BaseEvent.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 26 juin 2013, 14:22
 */

#ifndef BASEEVENT_H
#define	BASEEVENT_H

#include <string>
#include <map>
#include <stdint.h>

#include "Counter.h"

class BaseEvent {
public:
    static const std::string BEFORE_COMPUTATION;
    static const std::string OPTIMAL_SOLUTION_FOUND;
    
    BaseEvent();
    BaseEvent(const BaseEvent& orig);
    virtual ~BaseEvent();

    inline Counter& getCounter() {
        return this->counter;
    }

    inline const std::map<std::string, uint64_t>& getTimes() const {
        return times;
    }

    inline void addTime(std::string name, uint64_t time) {
        times[name] = time;
    }

private:
    Counter counter;
    std::map<std::string, uint64_t> times;

};

#endif	/* BASEEVENT_H */

