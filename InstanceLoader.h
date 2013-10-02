/* 
 * File:   InstanceLoader.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 28 juin 2013, 17:29
 */

#ifndef INSTANCELOADER_H
#define	INSTANCELOADER_H

#include <string>
#include <istream>

#include <boost/shared_ptr.hpp>

#include "Instance.h"
#include "Object.h"

template<typename P, typename W>
class InstanceLoader {
public:
    InstanceLoader();
    InstanceLoader(const InstanceLoader<P, W>& orig);
    virtual ~InstanceLoader();

    virtual boost::shared_ptr<Instance<P, W> > nextInstance() = 0;
    virtual bool hasNext() = 0;

    virtual boost::shared_ptr<Instance<P, W> > readFromStream(const std::string& name, std::istream& in);
private:

};

#include "InstanceLoader.tpp"
#endif	/* INSTANCELOADER_H */

