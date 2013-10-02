/* 
 * File:   Instance.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 15 mai 2013, 14:32
 */

#ifndef INSTANCE_H
#define	INSTANCE_H
#include <vector>
#include <string>
#include <istream>
#include <iosfwd>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <bitset>

#include <boost/filesystem.hpp>

#include "Object.h"
#include "InvalidFilenameException.h"

template<typename P, typename W> class AbstractKnapsackAlgorithm;

template<typename P, typename W>
class Instance {
public:
    Instance(const std::string& filename);
    Instance(const std::string& name, W knapsackSize, const std::vector<Object<P,W> >& objects);
    Instance(const Instance<P,W>& orig);
    virtual ~Instance();

    void addObject(Object<P,W>& object);

    inline W getKnapsackSize() const {
        return knapsackSize;
    }

    inline const std::vector<Object<P,W> >& getObjects() const {
        return objects;
    }

    inline int getNbObjects() const {
        return objects.size();
    }

    inline const Object<P,W>& getObject(int idx) const {
        return objects.at(idx);
    }

    W getWmax() const;

    P getUmax() const;

    virtual P getObjective(AbstractKnapsackAlgorithm<P,W>& algo);

    inline const std::string& getName() const {
        return name;
    }
protected:
    void readFromStream(std::istream& in);
private:
    W knapsackSize;
    std::string name;
    std::vector<Object<P,W> > objects;
};

#include "Instance.tpp"
#endif	/* INSTANCE_H */
