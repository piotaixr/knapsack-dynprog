/* 
 * File:   ChainLoader.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 2 juillet 2013, 19:10
 */

#ifndef CHAINLOADER_H
#define	CHAINLOADER_H

#include <list>

#include "InstanceLoader.h"

template<typename P, typename W>
class ChainLoader : public InstanceLoader<P, W> {
public:
    ChainLoader();
    ChainLoader(const ChainLoader<P, W>& orig);
    virtual ~ChainLoader();

    virtual boost::shared_ptr<Instance<P, W> > nextInstance();
    virtual bool hasNext();

    inline void addLoader(boost::shared_ptr<InstanceLoader<P, W> > loader) {
        loaders.push_back(loader);
    }

private:
    std::list<boost::shared_ptr<InstanceLoader<P, W> > > loaders;
};

#include "ChainLoader.tpp"
#endif	/* CHAINLOADER_H */

