/* 
 * File:   Instance.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 15 mai 2013, 14:32
 */

template<typename P, typename W>
Instance<P, W>::Instance(const std::string& name, W knapsackSize, const std::vector<Object<P, W> >& objects) : name(name) {
    this->knapsackSize = knapsackSize;
    this->objects = std::vector<Object<P, W> >(objects);
}

template<typename P, typename W>
void Instance<P, W>::addObject(Object<P, W>& object) {
    this->objects.push_back(object);
}

template<typename P, typename W>
Instance<P, W>::Instance(const Instance<P, W>& orig) {
    this->knapsackSize = orig.getKnapsackSize();
    this->objects = std::vector<Object<P, W> >(orig.getObjects());
}

template<typename P, typename W>
Instance<P, W>::~Instance() {
}

template<typename P, typename W>
P Instance<P, W>::getObjective(AbstractKnapsackAlgorithm<P, W>& algo) {
    return algo.run(*this);
}

template<typename P, typename W>
W Instance<P, W>::getWmax() const {
    W wmax = 0;
    for (typename std::vector<Object<P, W> >::const_iterator it = this->getObjects().begin(); it != this->getObjects().end(); it++) {
        wmax = std::max(wmax, it->getWeight());
    }

    return wmax;
}

template<typename P, typename W>
P Instance<P, W>::getUmax() const {
    P umax = 0;
    for (typename std::vector<Object<P, W> >::const_iterator it = this->getObjects().begin(); it != this->getObjects().end(); it++) {
        umax = std::max(umax, it->getUtility());
    }

    return umax;
}
