/* 
 * File:   ResultPrinter.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 6 juin 2013, 13:42
 */

#ifndef RESULTPRINTER_H
#define	RESULTPRINTER_H

#include <fstream>
#include <iostream>

#include <boost/foreach.hpp>

#include "EventListener.h"

template<typename P, typename W>
class ResultPrinter : public EventListener<P, W> {
public:
    ResultPrinter(std::ostream& out, bool otputTimes);
    
    virtual ~ResultPrinter();

    virtual void notify(const std::string& eventName, Event<P, W>& eventData);
    
    inline virtual std::string getName(){
        return "ResultPrinter";
    }
private:
    ResultPrinter(const ResultPrinter<P, W>& orig);
    ResultPrinter& operator=(const ResultPrinter& orig);
    
    std::ostream& file;
    bool outputTimes;
};

#include "ResultPrinter.tpp"

#endif	/* RESULTPRINTER_H */

