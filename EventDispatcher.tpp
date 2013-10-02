/* 
 * File:   EventDispatcher.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 30 mai 2013, 11:37
 */

template<typename P, typename W>
EventDispatcher<P, W>::EventDispatcher() {
}

template<typename P, typename W>
EventDispatcher<P, W>::EventDispatcher(const EventDispatcher<P, W>& orig) {
}

template<typename P, typename W>
EventDispatcher<P, W>::~EventDispatcher() {
    using namespace std;

    typedef pair<const std::string, set<EventListener<P, W>*> > map_type;

    BOOST_FOREACH(const map_type& p, listeners) {

        typedef EventListener<P, W>* listener_ptr;

        BOOST_FOREACH(listener_ptr listener, p.second) {
            delete listener;
        }
    }
}

template<typename P, typename W>
EventDispatcher<P, W>& EventDispatcher<P, W>::addListener(const std::string& eventName, EventListener<P, W>* listener) {
    using namespace std;

    typename map<string, set<EventListener<P, W>*> >::iterator it = listeners.find(eventName);

    if (it == listeners.end()) {
        listeners[eventName] = std::set<EventListener<P, W>*>();
    }

    if (listeners[eventName].find(listener) == listeners[eventName].end())
        listeners[eventName].insert(listener);

    return *this;
}

template<typename P, typename W>
void EventDispatcher<P, W>::dispatch(const std::string& eventName, boost::shared_ptr<Event<P, W> > eventData) {
    using namespace std;

    typename map<string, set<EventListener<P, W>*> >::iterator it = listeners.find(eventName);
    if (it != listeners.end()) {

        typedef EventListener<P, W>* listener_ptr;

        BOOST_FOREACH(listener_ptr listener, it->second) {
            Counter c = Counter(listener->getName());
            c.start();
            listener->notify(eventName, *eventData);
            c.stop();

            eventData->addTime(listener->getName(), c.getTime());
            if (eventData->hasOptimalSolution())
                break;
        }
    }
}