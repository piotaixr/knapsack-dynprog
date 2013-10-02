/* 
 * File:   BenchmarkPrinter.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 26 juillet 2013, 14:47
 */

#ifndef BENCHMARKPRINTER_H
#define	BENCHMARKPRINTER_H
#include <set>

#include <boost/regex.hpp>

#include <boost/bind.hpp>
#include <boost/algorithm/string/join.hpp>
#include <boost/foreach.hpp>

#include "BaseEvent.h"

template<typename P, typename W>
class BenchmarkPrinter : public EventListener<P, W> {
public:
    BenchmarkPrinter(std::string filenamePattern);
    virtual ~BenchmarkPrinter();

    virtual void notify(const std::string& eventName, Event<P, W>& eventData);

    virtual std::string getName() {
        return "BenchmarkPrinter";
    }
private:
    BenchmarkPrinter(const BenchmarkPrinter<P, W>& orig);
    BenchmarkPrinter& operator=(const BenchmarkPrinter& orig);
    
    typedef std::map<std::string, uint64_t> counter_map_type;
    typedef std::vector<counter_map_type > vector_counter_map_type;
    typedef std::map<uint64_t, vector_counter_map_type> times_type;

    times_type times;
    std::string filenamePattern;

    std::set<std::string> getCounterNames();
};

template <typename T>
struct RetrieveKey {
    typedef typename T::first_type result_type;

    result_type operator()(T keyValuePair) const {
        return keyValuePair.first;
    }
};

template <typename T >
struct StringConverter {
    typedef std::string result_type;

    result_type operator()(T value) const {
        std::stringstream sstream;
        sstream << value;

        return std::string(sstream.str());
    }
};

#include "BenchmarkPrinter.tpp"
#endif	/* BENCHMARKPRINTER_H */

