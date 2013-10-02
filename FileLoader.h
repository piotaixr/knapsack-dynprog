/* 
 * File:   FileLoader.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 28 juin 2013, 17:32
 */

#ifndef FILELOADER_H
#define	FILELOADER_H

#include <string>
#include <vector>

#include "InstanceLoader.h"

template<typename P, typename W>
class FileLoader : public InstanceLoader<P, W> {
public:
    FileLoader(const std::vector<std::string>& names);
    FileLoader(const FileLoader<P, W>& orig);
    virtual ~FileLoader();

    virtual boost::shared_ptr<Instance<P, W> > nextInstance();
    virtual bool hasNext();
private:
    std::vector<std::string> filenames;
    std::vector<std::string>::iterator it;
};

#include "FileLoader.tpp"
#endif	/* FILELOADER_H */

