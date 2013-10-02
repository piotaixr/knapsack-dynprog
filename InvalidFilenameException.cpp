/* 
 * File:   InvalidFilenameException.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 31 mai 2013, 14:43
 */

#include "InvalidFilenameException.h"

using namespace std;

InvalidFilenameException::InvalidFilenameException(const string& filename) : filename(filename) {
}

InvalidFilenameException::InvalidFilenameException(const InvalidFilenameException& orig) : filename(orig.getFilename()) {
}

InvalidFilenameException::~InvalidFilenameException() throw () {
}

const char* InvalidFilenameException::what() const throw () {
    return getMessage().c_str();
}
