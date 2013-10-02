/* 
 * File:   ResizedInstance.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 17 mai 2013, 13:44
 */

template<typename P, typename W>
ResizedInstance<P, W>::ResizedInstance(const std::string& name, W knapsackSize, const std::vector<Object<P, W> >& objects, P bonusObjective) : Instance<P, W>(name, knapsackSize, objects) {
    this->bonusObjective = bonusObjective;
}

template<typename P, typename W>
ResizedInstance<P, W>::ResizedInstance(const Instance<P, W> & orig, W knapsackSize, const std::vector<Object<P, W> >& objects, P bonusObjective) : Instance<P, W>(orig.getName(), knapsackSize, objects) {
    this->bonusObjective = bonusObjective;
}

template<typename P, typename W>
ResizedInstance<P, W>::ResizedInstance(const ResizedInstance<P, W>& orig) : Instance<P, W>(orig) {
    this->bonusObjective = orig.getBonusObjective();
}

template<typename P, typename W>
ResizedInstance<P, W>::~ResizedInstance() {
}

template<typename P, typename W>
P ResizedInstance<P, W>::getObjective(AbstractKnapsackAlgorithm<P, W>& algo) {
    return getBonusObjective() + Instance<P, W>::getObjective(algo);
}