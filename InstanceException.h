/* 
 * File:   InstanceException.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 31 mai 2013, 11:57
 */

#ifndef INSTANCEEXCEPTION_H
#define	INSTANCEEXCEPTION_H

#include <string>
#include <exception>

#include "Instance.h"

template<typename P, typename W>
class InstanceException: public std::exception {
public:
    InstanceException(const Instance<P,W>& instance);
    InstanceException(const Instance<P,W>& instance, const std::string& message);
    InstanceException(const InstanceException& orig);
    virtual ~InstanceException() throw() ;

    inline const Instance<P,W>& getInstance() const {
        return instance;
    }

    virtual const char* what() const throw ();

protected:
    std::string generateMessage(const Instance<P,W>& instance);

    void setMessage(std::string message) {
        this->message = message;
    }
private:
    const Instance<P,W>& instance;
    std::string message;
};

#include "InstanceException.tpp"
#endif	/* INSTANCEEXCEPTION_H */

