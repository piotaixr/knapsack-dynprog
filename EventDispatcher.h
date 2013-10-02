/* 
 * File:   EventDispatcher.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 30 mai 2013, 11:37
 */

#ifndef EVENTDISPATCHER_H
#define	EVENTDISPATCHER_H

#include <string>
#include <map>
#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/foreach.hpp>

#include "Event.h"
#include "EventListener.h"

template<typename P, typename W>
class EventDispatcher {
public:
    EventDispatcher();
    EventDispatcher(const EventDispatcher<P, W>& orig);
    virtual ~EventDispatcher();

    EventDispatcher<P, W>& addListener(const std::string& eventName, EventListener<P, W>* listener);

    void dispatch(const std::string& eventName, boost::shared_ptr<Event<P, W> > eventData);
private:
    std::map<std::string, std::set<EventListener<P, W>*> > listeners;
};

#include "EventDispatcher.tpp"

#endif	/* EVENTDISPATCHER_H */

