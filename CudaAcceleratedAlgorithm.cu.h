/*
 * CudaAcceleratedAlgorithm.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on: 21 mai 2013     
 */

#ifndef CUDAACCELERATEDALGORITHM_H_
#define CUDAACCELERATEDALGORITHM_H_

#include <cuda.h>
#include <cuda_runtime.h>
#include <ostream>
#include <limits>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "AbstractKnapsackAlgorithm.h"
#include "Instance.h"
#include "InstanceException.h"

template<typename P, typename W>
class CudaAcceleratedAlgorithm : public AbstractKnapsackAlgorithm<P, W> {
public:
    CudaAcceleratedAlgorithm();
    CudaAcceleratedAlgorithm(const CudaAcceleratedAlgorithm<P, W>& orig);
    virtual ~CudaAcceleratedAlgorithm();

    virtual P run(const Instance<P, W>& instance);
private:

};

#include "CudaAcceleratedAlgorithm.cu"
#endif /* CUDAACCELERATEDALGORITHM_H_ */
