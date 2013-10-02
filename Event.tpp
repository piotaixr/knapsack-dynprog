/* 
 * File:   Event.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 30 mai 2013, 11:38
 */

template<typename P, typename W>
Event<P, W>::Event(boost::shared_ptr<Instance<P, W> > _instance) {
    instance = _instance;
    optimalSolution = 0;
    optimalSolutionSet = false;
    getCounter().start();
}

template<typename P, typename W>
Event<P, W>::Event(const Event<P, W>& orig) : BaseEvent(orig) {
}

template<typename P, typename W>
Event<P, W>::~Event() {
}

template<typename P, typename W>
bool Event<P, W>::hasOptimalSolution() const {
    return optimalSolutionSet;
}

