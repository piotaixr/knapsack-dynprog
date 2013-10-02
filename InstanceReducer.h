/* 
 * File:   InstanceReducer.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 16 mai 2013, 11:24
 */

#ifndef INSTANCEREDUCER_H
#define	INSTANCEREDUCER_H

#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <math.h>

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#include "Event.h"
#include "Object.h"
#include "Instance.h"
#include "EventListener.h"
#include "ResizedInstance.h"
#include "OptimalSolutionFoundException.h"
#include "ResizableProblemInfeasibleException.h"

template<typename P, typename W>
class InstanceReducer : public EventListener<P, W> {
public:
    InstanceReducer();
    InstanceReducer(const InstanceReducer<P, W>& orig);
    virtual ~InstanceReducer();

    boost::shared_ptr<Instance<P, W> > reduce(const Instance<P, W>& orig);
    virtual void notify(const std::string& eventName, Event<P, W>& eventData);

    inline virtual std::string getName() {
        return "Reducer";
    }
private:
    void bourrage(P& baseValue, W& availableSpace, std::vector<Object<P, W> > objects, int beginIndex, int endIndex);

    P calculateDantzig(const std::list<Object<P, W> >& objects, W knapsackSize, int& charniere);

    P calculateHeuristicValue(const std::list<Object<P, W> >& objects, W knapsackSize);

    boost::shared_ptr<Instance<P, W> > createNewInstance(const Instance<P, W>& instance, std::vector<Object<P, W> >& sortedObjects, const std::vector<int>& objForceIn, const std::vector<int>& objForceOut);

    size_t findCriticalItemIdx(const std::vector<std::pair<P, W> >& pw_j, W knapsackSize);

    std::vector<std::pair<P, W> > buildPwj(const std::vector<Object<P, W> >& objects);

    Object<P, W>& getPreCriticalObject(std::vector<Object<P, W> >& sortedObjects, int criticalIdx);

    Object<P, W>& getPostCriticalObject(std::vector<Object<P, W> >& sortedObjects, int criticalIdx);

};

#include "InstanceReducer.tpp"

#endif	/* INSTANCEREDUCER_H */

