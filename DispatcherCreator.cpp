/* 
 * File:   DispatcherCreator.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 3 juillet 2013, 00:23
 */

#include "DispatcherCreator.h"

DispatcherCreator::DispatcherCreator(bool reduce, std::string outputFile, bool outputTimes, std::string benchmarkFile) : reduce(reduce), outputFile(outputFile), outputTimes(outputTimes), benchmarkFile(benchmarkFile) {
}

DispatcherCreator::~DispatcherCreator() {
}

