/* 
 * File:   OptimalSolutionFoundException.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 31 mai 2013, 12:02
 */

#ifndef OPTIMALSOLUTIONFOUNDEXCEPTION_H
#define	OPTIMALSOLUTIONFOUNDEXCEPTION_H

#include <sstream>

#include "InstanceException.h"

template<typename P, typename W>
class OptimalSolutionFoundException : public InstanceException<P, W> {
public:
    OptimalSolutionFoundException(const Instance<P, W>& instance, P optimalSolution);
    OptimalSolutionFoundException(const OptimalSolutionFoundException<P, W>& orig);
    virtual ~OptimalSolutionFoundException() throw();

    P getOptimalSolution() const {
        return optimalSolution;
    }

private:
    std::string generateMessage(const Instance<P, W>& instance, P optimalSolution);
    P optimalSolution;
};

#include "OptimalSolutionFoundException.tpp"

#endif	/* OPTIMALSOLUTIONFOUNDEXCEPTION_H */

