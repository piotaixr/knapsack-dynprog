/* 
 * File:   Event.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 30 mai 2013, 11:38
 */

#ifndef EVENT_H
#define	EVENT_H

#include <string>
#include <ctime>

#include <boost/shared_ptr.hpp>

#include "BaseEvent.h"
#include "Instance.h"

template<typename P, typename W>
class Event : public BaseEvent {
public:

    Event(boost::shared_ptr<Instance<P, W> > instance);
    Event(const Event<P, W>& orig);
    virtual ~Event();

    inline boost::shared_ptr<Instance<P, W> > getInstance() const {
        return instance;
    }

    inline void setInstance(boost::shared_ptr<Instance<P, W> > instance) {
        this->instance = instance;
    }

    bool hasOptimalSolution() const;

    inline P getOptimalSolution() const {
        return optimalSolution;
    }

    inline void setOptimalSolution(P optimalSolution) {
        if (optimalSolutionSet)
            return;

        optimalSolutionSet = true;
        this->optimalSolution = optimalSolution;
        getCounter().stop();
    }



private:
    boost::shared_ptr<Instance<P, W> > instance;
    P optimalSolution;
    bool optimalSolutionSet;
};

#include "Event.tpp"

#endif	/* EVENT_H */

