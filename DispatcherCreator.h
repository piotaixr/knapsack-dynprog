/* 
 * File:   DispatcherCreator.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 3 juillet 2013, 00:23
 */

#ifndef DISPATCHERCREATOR_H
#define	DISPATCHERCREATOR_H

#include <string>

#include <boost/any.hpp>
#include <boost/shared_ptr.hpp>

#include "EventDispatcher.h"
#include "InstanceReducer.h"
#include "ResultPrinter.h"
#include "BenchmarkPrinter.h"

class DispatcherCreator {
public:
    DispatcherCreator(bool reduce, std::string outputFile, bool outputTimes, std::string benchmarkFile);

    virtual ~DispatcherCreator();

    template<typename P, typename W>
    boost::shared_ptr<EventDispatcher<P, W> > getDispatcher();

private:
    DispatcherCreator(const DispatcherCreator& orig);
    DispatcherCreator& operator=(const DispatcherCreator& orig);

    bool reduce, outputTimes, benchmark;

    std::string outputFile, benchmarkFile;
    std::map<std::string, boost::any> dispatchers;

};

template<typename P, typename W>
boost::shared_ptr<EventDispatcher<P, W> > DispatcherCreator::getDispatcher() {
    if (dispatchers.find(BOOST_CURRENT_FUNCTION) == dispatchers.end()) {

        boost::shared_ptr<EventDispatcher<P, W> > dispatcher(new EventDispatcher<P, W>());
        if (reduce)
            dispatcher->addListener(BaseEvent::BEFORE_COMPUTATION, new InstanceReducer<P, W>());

        if (benchmarkFile != "")
            dispatcher->addListener(BaseEvent::OPTIMAL_SOLUTION_FOUND, new BenchmarkPrinter<P, W>(benchmarkFile));

        if (outputFile != "") {
            static std::ofstream file(outputFile.c_str(), std::ofstream::app);

            dispatcher->addListener(BaseEvent::OPTIMAL_SOLUTION_FOUND, new ResultPrinter<P, W>(file, outputTimes));
        }

        dispatchers[BOOST_CURRENT_FUNCTION] = dispatcher;
    }

    return boost::any_cast<boost::shared_ptr<EventDispatcher<P, W> > >(dispatchers[BOOST_CURRENT_FUNCTION]);
}

#endif	/* DISPATCHERCREATOR_H */

