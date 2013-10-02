/* 
 * File:   ResizableProblemInfeasibleException.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 31 mai 2013, 14:13
 */

#ifndef RESIZABLEPROBLEMINFEASIBLEEXCEPTION_H
#define	RESIZABLEPROBLEMINFEASIBLEEXCEPTION_H

#include "InstanceException.h"

template<typename P, typename W>
class ResizableProblemInfeasibleException : public InstanceException<P, W> {
public:
    ResizableProblemInfeasibleException(const Instance<P, W>& instance);
    ResizableProblemInfeasibleException(const ResizableProblemInfeasibleException<P, W>& orig);
    virtual ~ResizableProblemInfeasibleException() throw ();
protected:
    virtual std::string generateMessage(const Instance<P, W>& instance);
private:

};

#include "ResizableProblemInfeasibleException.tpp"

#endif	/* RESIZABLEPROBLEMINFEASIBLEEXCEPTION_H */

