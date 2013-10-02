/* 
 * File:   StreamLoader.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 2 juillet 2013, 18:58
 */

#ifndef STREAMLOADER_H
#define	STREAMLOADER_H

#include <istream>
#include <string>

#include <boost/algorithm/string.hpp>

#include "InstanceLoader.h"

template<typename P, typename W>
class StreamLoader : public InstanceLoader<P, W> {
public:
    StreamLoader(std::istream& in);
    StreamLoader(const StreamLoader<P, W>& orig);
    virtual ~StreamLoader();

    virtual boost::shared_ptr<Instance<P, W> > nextInstance();
    virtual bool hasNext();
private:

    std::istream& in;
    std::string nextName;
};

#include "StreamLoader.tpp"

#endif	/* STREAMLOADER_H */

