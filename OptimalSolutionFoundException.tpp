/* 
 * File:   OptimalSolutionFoundException.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 31 mai 2013, 12:02
 */

template<typename P, typename W>
OptimalSolutionFoundException<P, W>::OptimalSolutionFoundException(const Instance<P, W>& instance, P optimalSolution) : InstanceException<P, W>(instance, generateMessage(instance, optimalSolution)), optimalSolution(optimalSolution) {
}

template<typename P, typename W>
OptimalSolutionFoundException<P, W>::OptimalSolutionFoundException(const OptimalSolutionFoundException<P, W>& orig) : InstanceException<P, W>(orig) {
    optimalSolution = orig.getOptimalSolution();
}

template<typename P, typename W>
OptimalSolutionFoundException<P, W>::~OptimalSolutionFoundException() throw () {
}

template<typename P, typename W>
std::string OptimalSolutionFoundException<P, W>::generateMessage(const Instance<P, W>& instance, P optimalSolution) {
    std::stringstream ss;
    ss << "Une solution optimale a été trouvée pour l'instance " << instance.getName() << ": " << optimalSolution;

    return ss.str();
}