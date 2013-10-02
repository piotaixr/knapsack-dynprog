/* 
 * File:   ResizedInstance.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 17 mai 2013, 13:44
 */

#ifndef RESIZEDINSTANCE_H
#define	RESIZEDINSTANCE_H

#include "Instance.h"

template<typename P, typename W>
class ResizedInstance : public Instance<P, W> {
public:
    ResizedInstance(const std::string& name, W knapsackSize, const std::vector<Object<P, W> >& objects, P bonusObjective);
    ResizedInstance(const Instance<P, W>& instance, W knapsackSize, const std::vector<Object<P, W> >& objects, P bonusObjective);
    ResizedInstance(const ResizedInstance<P, W>& orig);
    virtual ~ResizedInstance();

    inline P getBonusObjective() const {
        return bonusObjective;
    }

    virtual P getObjective(AbstractKnapsackAlgorithm<P, W>& algo);
private:
    P bonusObjective;
};

#include "ResizedInstance.tpp"

#endif	/* RESIZEDINSTANCE_H */

