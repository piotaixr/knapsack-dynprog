/* 
 * File:   BaseEvent.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 26 juin 2013, 14:22
 */
#include "BaseEvent.h"

using namespace std;

const string BaseEvent::BEFORE_COMPUTATION = "beforeComputation";
const string BaseEvent::OPTIMAL_SOLUTION_FOUND = "optimalSolutionFound";

BaseEvent::BaseEvent() : counter("Total") {
}

BaseEvent::BaseEvent(const BaseEvent& orig) : counter(orig.counter) {
}

BaseEvent::~BaseEvent() {
}

