/* 
 * File:   Object.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 15 mai 2013, 14:34
 */

template<typename Profit, typename Weight>
std::ostream& operator<<(std::ostream& os, const Object<Profit, Weight>& o) {
    os << "[u" << o.getUtility() << " w" << o.getWeight() << " r" << o.getRatio() << "]";
    return os;
}

template<typename P, typename W>
Object<P, W>::Object(P utility, W weight) {
    this->utility = utility;
    this->weight = weight;
    this->ratio = this->weight == 0 ? this->utility : ((float) this->utility) / this->weight;
}

template<typename P, typename W>
Object<P, W>::Object(const Object<P, W>& orig) {
    this->utility = orig.getUtility();
    this->weight = orig.getWeight();
    this->ratio = orig.getRatio();
}

template<typename P, typename W>
Object<P, W>::~Object() {
}

template<typename P, typename W>
bool Object<P, W>::operator<(const Object<P, W>& o) const {
    return this->getRatio() < o.getRatio();
}
