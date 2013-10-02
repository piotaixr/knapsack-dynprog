/* 
 * File:   InvalidFilenameException.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 31 mai 2013, 14:43
 */

#ifndef INVALIDFILENAMEEXCEPTION_H
#define	INVALIDFILENAMEEXCEPTION_H

#include <exception>
#include <string>

class InvalidFilenameException : public std::exception {
public:
    InvalidFilenameException(const std::string& filename);
    InvalidFilenameException(const InvalidFilenameException& orig);
    virtual ~InvalidFilenameException() throw ();

    inline const std::string& getFilename() const {
        return filename;
    }

    inline std::string getMessage() const {
        return "The file " + filename + " is not valid or doesn't exist";
    }
    virtual const char* what() const throw ();
private:
    const std::string& filename;
};

#endif	/* INVALIDFILENAMEEXCEPTION_H */

