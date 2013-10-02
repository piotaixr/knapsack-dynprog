/* 
 * File:   ResizableProblemInfeasibleException.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 31 mai 2013, 14:13
 */

template<typename P, typename W>
ResizableProblemInfeasibleException<P, W>::ResizableProblemInfeasibleException(const Instance<P, W>& instance) : InstanceException<P, W>(instance, generateMessage(instance)) {
}

template<typename P, typename W>
ResizableProblemInfeasibleException<P, W>::ResizableProblemInfeasibleException(const ResizableProblemInfeasibleException<P, W>& orig) : InstanceException<P, W>(orig) {
}

template<typename P, typename W>
ResizableProblemInfeasibleException<P, W>::~ResizableProblemInfeasibleException() throw () {
}

template<typename P, typename W>
std::string ResizableProblemInfeasibleException<P, W>::generateMessage(const Instance<P, W>& instance) {
    return "Resizing the instance " + instance.getName() + " gives an unsolvable one";
}