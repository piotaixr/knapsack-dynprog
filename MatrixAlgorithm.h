/* 
 * File:   MatrixKnapsackAlgorithm.h
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 *
 * Created on 15 mai 2013, 16:31
 */

#ifndef MATRIXALGORITHM_H
#define	MATRIXALGORITHM_H

#include <boost/numeric/ublas/matrix.hpp>

#include "AbstractKnapsackAlgorithm.h"

template<typename P, typename W>
class MatrixAlgorithm : public AbstractKnapsackAlgorithm<P, W> {
public:
    MatrixAlgorithm();
    MatrixAlgorithm(const MatrixAlgorithm<P, W>& orig);
    virtual ~MatrixAlgorithm();

    virtual P run(const Instance<P, W>& instance);
private:
    void calculCase(const Instance<P, W>& instance, boost::numeric::ublas::matrix<P>& matrix, size_t i, size_t j);
};



#include "MatrixAlgorithm.tpp"
#endif	/* MATRIXALGORITHM_H */

