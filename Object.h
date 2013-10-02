/* 
 * File:   Object.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 15 mai 2013, 14:34
 */

#ifndef OBJECT_H
#define	OBJECT_H

#include <ostream>

template<typename P, typename W>
class Object {
public:
    Object(P utility, W weight);
    Object(const Object<P,W>& orig);
    virtual ~Object();

    inline P getUtility() const {
        return utility;
    }

    inline W getWeight() const {
        return weight;
    }

    inline double getRatio() const {
        return ratio;
    }

    bool operator<(const Object& o) const;
    
    template<typename Profit, typename Weight>
    friend std::ostream& operator<<(std::ostream& os, const Object<Profit,Weight>& o);
private:
    W weight;
    double ratio;
    P utility;
};

#include "Object.tpp"
#endif	/* OBJECT_H */

