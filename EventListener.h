/* 
 * File:   EventListener.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 30 mai 2013, 11:40
 */

#ifndef EVENTLISTENER_H
#define	EVENTLISTENER_H

#include <string>

#include "Event.h"
template<typename P, typename W>
class EventListener {
public:
    EventListener();
    EventListener(const EventListener<P, W>& orig);
    virtual ~EventListener();

    virtual void notify(const std::string& eventName, Event<P, W>& eventData) = 0;
    virtual std::string getName() = 0;
private:

};

#include "EventListener.tpp"

#endif	/* EVENTLISTENER_H */

