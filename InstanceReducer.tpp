/* 
 * File:   InstanceReducer.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 16 mai 2013, 11:24
 */

template<typename P, typename W>
InstanceReducer<P, W>::InstanceReducer() : EventListener<P, W>() {
}

template<typename P, typename W>
InstanceReducer<P, W>::InstanceReducer(const InstanceReducer<P, W>& orig) : EventListener<P, W>(orig) {
}

template<typename P, typename W>
InstanceReducer<P, W>::~InstanceReducer() {
    //    delete heuristic;
}

template<typename P, typename W>
void InstanceReducer<P, W>::notify(const std::string& eventName, Event<P, W>& eventData) {
    boost::shared_ptr<Instance<P, W> > newInstance;

    try {
        newInstance = reduce(*eventData.getInstance());
    } catch (OptimalSolutionFoundException<P, W>& exception) {
        eventData.setOptimalSolution(exception.getOptimalSolution());
    }

    if (newInstance != 0) {
        eventData.setInstance(newInstance);
    }
}

template<typename P, typename W>
std::vector<std::pair<P, W> > InstanceReducer<P, W>::buildPwj(const std::vector<Object<P, W> >& objects) {
    using namespace std;

    vector<pair<P, W> > pw_j;
    pw_j.push_back(pair<P, W>(0, 0));
    P sumUtility = 0;
    W sumWeight = 0;
    for (typename vector<Object<P, W> >::const_iterator objectIterator = objects.begin(); objectIterator != objects.end(); objectIterator++) {
        sumUtility += objectIterator->getUtility();
        sumWeight += objectIterator->getWeight();

        pw_j.push_back(pair<P, W>(sumUtility, sumWeight));
    }

    return pw_j;
}

template<typename P, typename W>
size_t InstanceReducer<P, W>::findCriticalItemIdx(const std::vector<std::pair<P, W> >& pw_j, W knapsackSize) {
    using namespace std;

    size_t begin = 0;
    size_t end = pw_j.size() - 1;
    size_t mid;
    while (begin < end) {
        mid = (begin + end) / 2;
        if (knapsackSize == pw_j[mid].second) {
            return mid;
        } else if (knapsackSize < pw_j[mid].second) {
            end = mid - 1;
        } else {
            begin = mid + 1;
        }
    }
    //si on arrive a begin = end, on est soit sur la valeur supérieure à knapsackSize, soit sur la valeur inférieure
    if (pw_j[begin].second < knapsackSize) {
        return min(begin + 1, pw_j.size() - 1);
    } else {//on est sur la val supérieure.
        return begin;
    }
}

template<typename P, typename W>
Object<P, W>& InstanceReducer<P, W>::getPreCriticalObject(std::vector<Object<P, W> >& sortedObjects, int criticalIdx) {
    return sortedObjects[criticalIdx - 1];
}

template<typename P, typename W>
Object<P, W>& InstanceReducer<P, W>::getPostCriticalObject(std::vector<Object<P, W> >& sortedObjects, int criticalIdx) {
    return sortedObjects[criticalIdx + 1];
}

template<typename P, typename W>
void InstanceReducer<P, W>::bourrage(P& baseValue, W& availableSpace, std::vector<Object<P, W> > objects, int beginIndex, int endIndex) {
    for (int i = beginIndex; i < endIndex; i++) {
        const Object<P, W>& o = objects[i];
        if (o.getWeight() <= availableSpace) {
            baseValue += o.getUtility();
            availableSpace -= o.getWeight();
        }
    }
}

template<typename P, typename W>
boost::shared_ptr<Instance<P, W> > InstanceReducer<P, W>::reduce(const Instance<P, W>& orig) {
    using namespace std;

    int nbObjects = orig.getNbObjects();

    vector<Object<P, W> > sortedObjects(orig.getObjects());
    sort(sortedObjects.begin(), sortedObjects.end());
    reverse(sortedObjects.begin(), sortedObjects.end());

    vector<pair<P, W> > pw_j = buildPwj(sortedObjects);

    int s = findCriticalItemIdx(pw_j, orig.getKnapsackSize());

    P maxRealizableSolution = pw_j[s - 1].first;
    W availableSpace = orig.getKnapsackSize() - pw_j[s - 1].second;

    bourrage(maxRealizableSolution, availableSpace, sortedObjects, s + 1, nbObjects);
    
    vector<P> dantzigsForce0;
    vector<P> dantzigsForce1;

    for (int j = 0; j <= s; j++) {
        const Object<P, W>& o_j = sortedObjects[j];
        int _s = findCriticalItemIdx(pw_j, orig.getKnapsackSize() + o_j.getWeight());
        availableSpace = orig.getKnapsackSize() + o_j.getWeight() - pw_j[_s - 1].second;
        const Object<P, W>& criticalObject = sortedObjects[_s];
        const Object<P, W>& preCriticalObject = getPreCriticalObject(sortedObjects, _s);
        const Object<P, W>& postCriticalObject = getPostCriticalObject(sortedObjects, _s);

        P base = pw_j[_s - 1].first - o_j.getUtility();
        P bonusU1 = availableSpace * postCriticalObject.getRatio();
        P bonusU2 = criticalObject.getUtility() - (criticalObject.getWeight() - availableSpace) * preCriticalObject.getRatio();

        P u0_j = base + (P) max(bonusU1, bonusU2);

        dantzigsForce0.push_back(u0_j);

        maxRealizableSolution = max(maxRealizableSolution, pw_j[_s - 1].first - o_j.getUtility());

        maxRealizableSolution = maxRealizableSolution;
    }
    for (int j = s; j < nbObjects; j++) {
        const Object<P, W>& o_j = sortedObjects[j];
        int _s = findCriticalItemIdx(pw_j, orig.getKnapsackSize() - o_j.getWeight());
        availableSpace = orig.getKnapsackSize() - o_j.getWeight() - pw_j[_s - 1].second;
        const Object<P, W>& criticalObject = sortedObjects[_s];
        const Object<P, W>& preCriticalObject = getPreCriticalObject(sortedObjects, _s);
        const Object<P, W>& postCriticalObject = getPostCriticalObject(sortedObjects, _s);

        P base = pw_j[_s - 1].first + o_j.getUtility();
        P bonusU1 = availableSpace * postCriticalObject.getRatio();
        P bonusU2 = criticalObject.getUtility()-(criticalObject.getWeight() - availableSpace) * preCriticalObject.getRatio();

        P u1_j = base + (P) max(bonusU1, bonusU2);

        dantzigsForce1.push_back(u1_j);

        maxRealizableSolution = max(maxRealizableSolution, pw_j[_s - 1].first + o_j.getUtility());

        maxRealizableSolution = maxRealizableSolution;
    }

    vector<int> objForceIn;
    vector<int> objForceOut;

    for (int j = 0; j < dantzigsForce0.size(); j++) {
        if (dantzigsForce0[j] <= maxRealizableSolution) {

            objForceIn.push_back(j);
        }
    }
    for (int j = 0; j < dantzigsForce1.size(); j++) {
        int idObj = j + s;

        if (dantzigsForce1[j] <= maxRealizableSolution) {
            objForceOut.push_back(idObj);
        }
    }

    try {
        return createNewInstance(orig, sortedObjects, objForceIn, objForceOut);
    } catch (ResizableProblemInfeasibleException<P, W>& ex) {
        throw OptimalSolutionFoundException<P, W>(ex.getInstance(), maxRealizableSolution);
    }
}

/**
 * 
 * @param instance
 * @param objForceIn indices des objets a mettre dans le sac, ordre croissant
 * @param objForceOut indices des objets à ne pas mettre dans le sac, ordre croissant
 * @return 
 */
template<typename P, typename W>
boost::shared_ptr<Instance<P, W> > InstanceReducer<P, W>::createNewInstance(const Instance<P, W>& instance, std::vector<Object<P, W> >& sortedObjects, const std::vector<int>& objForceIn, const std::vector<int>& objForceOut) {
    using namespace std;

    int newKnapsackSize = instance.getKnapsackSize();
    int utilityBonus = 0;
    int weightLoss = 0;
    vector<Object<P, W> > newObjects;
    vector<int>::const_iterator forceInIterator = objForceIn.begin();
    vector<int>::const_iterator forceOutIterator = objForceOut.begin();
    int unfeasible = false;

    typename vector<Object<P, W> >::const_iterator objectIterator = sortedObjects.begin();
    int i = 0;
    while (objectIterator != sortedObjects.end()) {

        if (forceInIterator != objForceIn.end() && *forceInIterator == i && forceOutIterator != objForceOut.end() && *forceOutIterator == i) {
            unfeasible = true;
        }
        if (forceInIterator != objForceIn.end() && *forceInIterator == i) {
            // forcer l'objet à l'intérieur revient a calculer une instance sans l'objet et une taille plus petite
            newKnapsackSize -= objectIterator->getWeight();
            weightLoss += objectIterator->getWeight();
            utilityBonus += objectIterator->getUtility();
            forceInIterator++;
        } else if (forceOutIterator != objForceOut.end() && *forceOutIterator == i) {
            // forcer l'objet à l'extérieur revient a calculer une instance sans l'objet        
            forceOutIterator++;
        } else {
            newObjects.push_back(*objectIterator);
        }
        objectIterator++;
        i++;
    }
    if (newKnapsackSize < 0 || unfeasible)
        throw ResizableProblemInfeasibleException<P, W>(instance);

    return boost::shared_ptr<Instance<P, W> >(new ResizedInstance<P, W>(instance, newKnapsackSize, newObjects, utilityBonus));
}