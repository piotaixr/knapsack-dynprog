/* 
 * File:   InstanceLoader.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 28 juin 2013, 17:29
 */

template<typename P, typename W>
InstanceLoader<P, W>::InstanceLoader() {
}

template<typename P, typename W>
InstanceLoader<P, W>::InstanceLoader(const InstanceLoader<P, W>& orig) {
}

template<typename P, typename W>
InstanceLoader<P, W>::~InstanceLoader() {
}

template<typename P, typename W>
boost::shared_ptr<Instance<P, W> > InstanceLoader<P, W>::readFromStream(const std::string& name, std::istream& in) {
    using namespace std;
    W knapsackSize;
    size_t nbObjects;
    in >> nbObjects;

    vector<Object<P, W> > objects;

    P utilities[nbObjects];

    for (size_t i = 0; i < nbObjects; i++) {
        in >> utilities[i];
    }

    W weight;
    for (size_t i = 0; i < nbObjects; i++) {
        in >> weight;
        objects.push_back(Object<P, W>(utilities[i], weight));
    }

    in >> knapsackSize;

    boost::shared_ptr<Instance<P, W> > instance(new Instance<P, W>(name, knapsackSize, objects));

    return instance;
}