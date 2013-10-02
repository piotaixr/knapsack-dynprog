/* 
 * File:   SwapVectorsAlgorithm.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 15 mai 2013, 17:07
 */

template<typename P, typename W>
SwapVectorsAlgorithm<P, W>::SwapVectorsAlgorithm(int numThreadsOmp) : AbstractKnapsackAlgorithm<P, W>(), numThreadsOmp(numThreadsOmp) {
}

template<typename P, typename W>
SwapVectorsAlgorithm<P, W>::SwapVectorsAlgorithm(const SwapVectorsAlgorithm<P, W>& orig) : AbstractKnapsackAlgorithm<P, W>(orig) {
}

template<typename P, typename W>
SwapVectorsAlgorithm<P, W>::~SwapVectorsAlgorithm() {

}

template<typename P, typename W>
P SwapVectorsAlgorithm<P, W>::run(const Instance<P, W>& instance) {
    using namespace std;
    
    vector<P>* v1 = new vector<P>(instance.getKnapsackSize() + 1);
    vector<P>* v2 = new vector<P>(instance.getKnapsackSize() + 1);
    vector<P>* temp;
    int size = v2->size();

    for (size_t i = 0; i < instance.getNbObjects(); i++) {
#ifndef SWAP_NO_OMP
        if(numThreadsOmp != 0){ 
           omp_set_num_threads(numThreadsOmp);
        }
#pragma omp parallel for
#endif
        for (size_t j = 1; j < size; j++) {
            calculCase(instance, *v1, *v2, i, j);
        }

        temp = v1;
        v1 = v2;
        v2 = temp;
        cout << setw(10) << i << "/" << setw(10) << instance.getNbObjects() << " : " << setw(10) << v1->at(size - 1) << "\r" << flush;
    }
    cout << endl;
    P retour = v1->at(v1->size() - 1);
    delete v1;
    delete v2;
    return retour;
}

template<typename P, typename W>
void SwapVectorsAlgorithm<P, W>::calculCase(const Instance<P, W>& instance, std::vector<P>& v1, std::vector<P>& v2, int i, int j) {
    using namespace std;
    
    P prevValuenoAdd = v1[j];
    const Object<P, W>& o = instance.getObject(i);

    if (j < o.getWeight()) { 
        v2[j] = prevValuenoAdd;
    } else {
        size_t xCaseToAdd = j - o.getWeight();
        P newValue = v1.at(xCaseToAdd) + o.getUtility();
        v2[j] = max(prevValuenoAdd, newValue);
    }
}
