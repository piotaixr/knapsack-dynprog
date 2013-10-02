/* 
 * File:   ThrustAlgorithm.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 19 juillet 2013, 17:12
 */

#ifndef THRUSTALGORITHM_H
#define	THRUSTALGORITHM_H

#include <thrust/device_vector.h>
#include <thrust/host_vector.h>

#include "AbstractKnapsackAlgorithm.h"
#include "Instance.h"

template<typename P, typename W>
class ThrustAlgorithm : public AbstractKnapsackAlgorithm<P, W> {
public:
    ThrustAlgorithm();
    ThrustAlgorithm(const ThrustAlgorithm<P, W>& orig);
    virtual ~ThrustAlgorithm();

    virtual P run(const Instance<P, W>& instance);
private:

};

template<typename T>
struct thrust_max_fun : public thrust::binary_function<T, T, T> {
    T objectUtility;

    thrust_max_fun(T objectUtility) : objectUtility(objectUtility) {
    };

    thrust_max_fun(const thrust_max_fun<T>& orig) : objectUtility(orig.objectUtility) {
    }

    __host__ __device__ T operator()(const T& lhs, const T& rhs) const {
        using namespace std;
        
        return max(lhs, rhs + objectUtility);
    }
};

#include "ThrustAlgorithm.tpp"
#endif	/* THRUSTALGORITHM_H */

