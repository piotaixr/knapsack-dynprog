/* 
 * File:   SwapVectorsKnapsackAlgorithm.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 15 mai 2013, 17:07
 */

#ifndef SWAPVECTORSALGORITHM_H
#define	SWAPVECTORSALGORITHM_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <omp.h>

#include "AbstractKnapsackAlgorithm.h"

template<typename P, typename W>
class SwapVectorsAlgorithm : public AbstractKnapsackAlgorithm<P, W> {
public:
    SwapVectorsAlgorithm(int numThreadsOmp);
    SwapVectorsAlgorithm(const SwapVectorsAlgorithm<P, W>& orig);
    virtual ~SwapVectorsAlgorithm();

    virtual P run(const Instance<P, W>& instance);
private:
    void calculCase(const Instance<P, W>& instance, std::vector<P>& v1, std::vector<P>& v2, int i, int j);
    int numThreadsOmp;
};

#include "SwapVectorsAlgorithm.tpp"
#endif	/* SWAPVECTORSALGORITHM_H */

