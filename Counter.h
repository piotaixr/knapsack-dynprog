/* 
 * File:   Counter.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 11 juillet 2013, 16:04
 */

#ifndef COUNTER_H
#define	COUNTER_H

#include <ctime>
#include <string>

class Counter {
public:

    typedef enum {
        CREATED, STARTED, STOPPED
    } CounterState;

    Counter(std::string name);
    Counter(const Counter& orig);
    virtual ~Counter();

    inline void start() {
        if (state == CREATED) {
            state = STARTED;
            clock_gettime(CLOCK_REALTIME, &begin);
        }
    }

    inline void stop() {
        if (state == STARTED) {
            state = STOPPED;
            clock_gettime(CLOCK_REALTIME, &end);
        }
    }

    inline std::string getName() const {
        return name;
    }

    inline unsigned long long getTime() const {
        if (state == CREATED)
            return 0;

        timespec now;
        if (state != STOPPED)
            clock_gettime(CLOCK_REALTIME, &now);
        else
            now = end;

        timespec elapsed = diff(begin, now);

        return elapsed.tv_sec * 1000000000 + elapsed.tv_nsec;
    }
private:
    timespec diff(timespec start, timespec end) const;
    CounterState state;
    std::string name;
    timespec begin;
    timespec end;
};

#endif	/* COUNTER_H */

