/* 
 * File:   FileLoader.tpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 28 juin 2013, 17:32
 */

template<typename P, typename W>
FileLoader<P, W>::FileLoader(const std::vector<std::string>& names) : filenames(names), it(filenames.begin()) {

}

template<typename P, typename W>
FileLoader<P, W>::FileLoader(const FileLoader<P, W>& orig) : InstanceLoader<P, W>(orig), filenames(orig.filenames), it(filenames.begin()) {
}

template<typename P, typename W>
FileLoader<P, W>::~FileLoader() {

}

template<typename P, typename W>
bool FileLoader<P, W>::hasNext() {
    return it != filenames.end();
}

template<typename P, typename W>
boost::shared_ptr<Instance<P, W> > FileLoader<P, W>::nextInstance() {
    namespace fs = boost::filesystem;
    using namespace std;

    boost::shared_ptr<Instance<P, W> > ptr;

    if (it != filenames.end()) {
        string filename = *it;
        it++;
        
        fs::path p(filename);
        if (!fs::exists(p) || !fs::is_regular_file(p)) {
            throw InvalidFilenameException(filename);
        }

        ifstream file(filename.c_str(), ifstream::in);

        ptr = this->readFromStream(p.stem().generic_string(), file);
    }

    return ptr;
}
