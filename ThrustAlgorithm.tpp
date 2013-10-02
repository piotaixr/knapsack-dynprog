/* 
 * File:   ThrustAlgorithm.tpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 19 juillet 2013, 17:13
 */

template<typename P, typename W>
ThrustAlgorithm<P, W>::ThrustAlgorithm() {
}

template<typename P, typename W>
ThrustAlgorithm<P, W>::ThrustAlgorithm(const ThrustAlgorithm<P, W>& orig) : AbstractKnapsackAlgorithm<P, W>(orig) {
}

template<typename P, typename W>
ThrustAlgorithm<P, W>::~ThrustAlgorithm() {
}

template<typename P, typename W>
P ThrustAlgorithm<P, W>::run(const Instance<P, W>& instance) {
    using namespace std;

    thrust::device_vector<P> data(instance.getKnapsackSize() + 1, 0);
    thrust::device_vector<P> retour(instance.getKnapsackSize() + 1, 0);

    bool swap = false;
    unsigned i = 1;

    typename vector<Object<P, W> >::const_iterator it;
    for (it = instance.getObjects().begin(); it != instance.getObjects().end(); it++) {
        const Object<P, W>& o = *it;

        if (swap) {
            thrust::copy(retour.begin(), retour.begin() + o.getWeight(), data.begin());
            thrust::transform(retour.begin() + o.getWeight(), retour.end(), retour.begin(), data.begin() + o.getWeight(), thrust_max_fun<P>(o.getUtility()));
        } else {
            thrust::copy(data.begin(), data.begin() + o.getWeight(), retour.begin());
            thrust::transform(data.begin() + o.getWeight(), data.end(), data.begin(), retour.begin() + o.getWeight(), thrust_max_fun<P>(o.getUtility()));
        }

        swap = !swap;

        cout << setw(10) << i << " /" << setw(10) << instance.getNbObjects() << setw(10) << instance.getKnapsackSize() << '\r' << flush;
        i++;
    }

    cout << endl;

    return swap ? *(retour.end() - 1) : *(data.end() - 1);
}