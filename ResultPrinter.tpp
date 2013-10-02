/* 
 * File:   ResultPrinter.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 6 juin 2013, 13:42
 */

#include "BaseEvent.h"

template<typename P, typename W>
ResultPrinter<P, W>::ResultPrinter(std::ostream& out, bool outputTimes) : file(out), outputTimes(outputTimes) {
}

template<typename P, typename W>
ResultPrinter<P, W>::~ResultPrinter() {
    file << std::flush;
}

template<typename P, typename W>
void ResultPrinter<P, W>::notify(const std::string& eventName, Event<P, W>& eventData) {
    using namespace std;

    if (eventName == BaseEvent::OPTIMAL_SOLUTION_FOUND) {
        uint64_t nanos = eventData.getCounter().getTime();

        file << eventData.getInstance()->getName() << "\t\t"
                << eventData.getOptimalSolution();

        if (outputTimes) {
            file << "\t\t" << nanos << "\t\t";

            for (map<string, uint64_t>::const_iterator it = eventData.getTimes().begin(); it != eventData.getTimes().end(); it++) {
                file << it->first << "\t\t"
                        << it-> second << "\t\t";
            }
        }

        file << endl;
    }
}