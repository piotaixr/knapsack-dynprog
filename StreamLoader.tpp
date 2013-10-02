/* 
 * File:   StreamLoader.tpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 2 juillet 2013, 18:58
 */

template<typename P, typename W>
StreamLoader<P, W>::StreamLoader(std::istream& in) : in(in) {
    nextName = "";
}

template<typename P, typename W>
StreamLoader<P, W>::StreamLoader(const StreamLoader<P, W>& orig) : InstanceLoader<P, W>(orig), in(orig.in) {
}

template<typename P, typename W>
StreamLoader<P, W>::~StreamLoader() {
}

template<typename P, typename W>
boost::shared_ptr<Instance<P, W> > StreamLoader<P, W>::nextInstance() {
    using namespace std;

    string name(nextName);

    return this->readFromStream(name, in);
}

template<typename P, typename W>
bool StreamLoader<P, W>::hasNext() {
    using namespace std;
    using namespace boost;

    while (nextName == "" && !in.eof()) {
        getline(in, nextName, '\n');
        trim(nextName);
    }

    return nextName != "";
}