/* 
 * File:   AbstractKnapsackAlgorithm.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 15 mai 2013, 16:17
 */

#ifndef ABSTRACTKNAPSACKALGORITHM_H
#define	ABSTRACTKNAPSACKALGORITHM_H

#include "Instance.h"

template<typename P, typename W>
class AbstractKnapsackAlgorithm  {
public:
    AbstractKnapsackAlgorithm();
    AbstractKnapsackAlgorithm(const AbstractKnapsackAlgorithm<P,W>& orig);
    virtual ~AbstractKnapsackAlgorithm();

    virtual P run(const Instance<P,W>& instance)= 0;
private:

};

#include "AbstractKnapsackAlgorithm.tpp"

#endif	/* ABSTRACTKNAPSACKALGORITHM_H */