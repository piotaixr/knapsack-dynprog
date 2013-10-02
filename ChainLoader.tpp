/* 
 * File:   ChainLoader.tpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 2 juillet 2013, 19:10
 */

template<typename P, typename W>
ChainLoader<P, W>::ChainLoader() {
}

template<typename P, typename W>
ChainLoader<P, W>::ChainLoader(const ChainLoader<P, W>& orig) : InstanceLoader<P, W>(orig) {
}

template<typename P, typename W>
ChainLoader<P, W>::~ChainLoader() {
}

template<typename P, typename W>
boost::shared_ptr<Instance<P, W> > ChainLoader<P, W>::nextInstance() {
    return (*loaders.begin())->nextInstance();
}

template<typename P, typename W>
bool ChainLoader<P, W>::hasNext() {
    while (loaders.begin() != loaders.end() && !(*loaders.begin())->hasNext()){
        loaders.erase(loaders.begin());
    }

    return loaders.begin() != loaders.end();
}

