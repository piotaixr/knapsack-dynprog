/* 
 * File:   MatrixKnapsackAlgorithm.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on 15 mai 2013, 16:31
 */

template<typename P, typename W>
MatrixAlgorithm<P, W>::MatrixAlgorithm() : AbstractKnapsackAlgorithm<P, W>() {
}

template<typename P, typename W>
MatrixAlgorithm<P, W>::MatrixAlgorithm(const MatrixAlgorithm<P, W>& orig) : AbstractKnapsackAlgorithm<P, W>(orig) {
}

template<typename P, typename W>
MatrixAlgorithm<P, W>::~MatrixAlgorithm() {
}

template<typename P, typename W>
void MatrixAlgorithm<P, W>::calculCase(const Instance<P, W>& instance, boost::numeric::ublas::matrix<P>& mat, size_t i, size_t j) {
    using namespace std;

    P prevValuenoAdd = mat(i - 1, j);
    const Object<P, W>& o = instance.getObject(i - 1);

    if (j < o.getWeight()) {
        mat(i, j) = prevValuenoAdd;
    } else {
        size_t xCaseToAdd = j - o.getWeight();
        P newValue = mat(i - 1, xCaseToAdd) + o.getUtility();
        mat(i, j) = max(prevValuenoAdd, newValue);
    }
}

template<typename P, typename W>
P MatrixAlgorithm<P, W>::run(const Instance<P, W>& instance) {

    boost::numeric::ublas::matrix<P> matrix(instance.getNbObjects() + 1, instance.getKnapsackSize() + 1);
    matrix.clear();

    for (int i = 1; i <= instance.getNbObjects(); i++) {
        for (int j = 1; j <= instance.getKnapsackSize(); j++) {
            calculCase(instance, matrix, i, j);
        }
    }

    return matrix(matrix.size1() - 1, matrix.size2() - 1);
}