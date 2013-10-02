/*
 * CudaAcceleratedAlgorithm.cpp
 * Author: Rémi PIOTAIX <remi.piotaix@gmail.com>
 * 
 * Created on: 21 mai 2013     
 */

#include "Object.h"


#include "Instance.h"

template<typename P, typename W>
CudaAcceleratedAlgorithm<P, W>::CudaAcceleratedAlgorithm() :
AbstractKnapsackAlgorithm<P, W>() {

}

template<typename P, typename W>
CudaAcceleratedAlgorithm<P, W>::CudaAcceleratedAlgorithm(const CudaAcceleratedAlgorithm<P, W>& orig) :
AbstractKnapsackAlgorithm<P, W>(orig) {

}

template<typename P, typename W>
CudaAcceleratedAlgorithm<P, W>::~CudaAcceleratedAlgorithm() {

}

template<typename P, typename W, unsigned repeat>
__global__ void kernel(P* data, P* retour, W objSize, P objUtility, unsigned size, unsigned decalBlock = 0) throw () {
    unsigned i = blockDim.x * (blockIdx.x + decalBlock) + threadIdx.x;
    unsigned sep = blockDim.x * gridDim.x;
    P retValue;

#pragma unroll
    for (unsigned num = 0; num < repeat; num++) {
        if (i < size) {
            retValue = data[i];
            if (i >= objSize)
                retValue = max(retValue, data[i - objSize] + objUtility);

            retour[i] = retValue;
        }

        i += sep;
    }

}

template<typename T>
void fillWith(T* tab, T value, int tabSize) {
    for (int i = 0; i < tabSize; i++) {
        tab[i] = value;
    }
}

std::ostream& operator<<(std::ostream& os, const cudaError_t & err) {
    os << cudaGetErrorString(err);

    return os;
}

template<typename T>
void printTab(T* tab, size_t taille) {
    using namespace std;

    for (size_t i = 0; i < taille; i++) {
        cout << setw(5) << tab[i];
    }
    cout << endl;
}

void HANDLE(cudaError_t err) {
    using namespace std;

    if (err != cudaSuccess)
        cout << err << endl;
}

template<typename P, typename W >
P CudaAcceleratedAlgorithm<P, W>::run(const Instance<P, W>& instance) {
    using namespace std;

    int nbObjects = instance.getNbObjects();

    cudaDeviceProp prop;
    HANDLE(cudaSetDevice(0));
    HANDLE(cudaGetDeviceProperties(&prop, 0));
    int block_max_size = prop.maxGridSize[0];

    size_t dataSize = instance.getKnapsackSize() + 1;

    P* d_retour;
    P* d_data;

    int threadsPerBlock = 1 << min((int) log2((float) dataSize), 8);
    double blocks = (double) dataSize / threadsPerBlock / 8;
    int blocksPerGrid = (int) blocks + 1;

    HANDLE(cudaMalloc(&d_retour, sizeof (P) * dataSize));
    HANDLE(cudaMalloc(&d_data, sizeof (P) * dataSize));

    HANDLE(cudaMemset(d_data, 0, sizeof (P) * dataSize));
    HANDLE(cudaMemset(d_retour, 0, sizeof (P) * dataSize));

    unsigned i = 1;
    for (typename vector<Object<P, W> >::const_iterator iterator = instance.getObjects().begin();
            iterator != instance.getObjects().end(); iterator++) {
        //cout << "For BEGIN " << i << endl;

        const Object<P, W>& o = *iterator;

        unsigned decalBlock = 0;
        while (blocksPerGrid - decalBlock >= block_max_size) {
            kernel<P, W, 8> << <block_max_size, threadsPerBlock >> >(d_data, d_retour, o.getWeight(), o.getUtility(), dataSize, decalBlock);
            decalBlock += block_max_size;
        }
        if (blocksPerGrid > decalBlock)
            kernel<P, W, 8> << <blocksPerGrid - decalBlock, threadsPerBlock >> >(d_data, d_retour, o.getWeight(), o.getUtility(), dataSize, decalBlock);

        P* temp = d_data;
        d_data = d_retour;
        d_retour = temp;

        cout << setw(10) << i << " /" << setw(10) << nbObjects << setw(10) << dataSize << '\r' << flush;
        i++;
    }
    P resultat;
    HANDLE(cudaMemcpy(&resultat, d_data + dataSize - 1, sizeof (P), cudaMemcpyDeviceToHost));

    HANDLE(cudaFree(d_data));
    HANDLE(cudaFree(d_retour));
    cout << endl;


    return resultat;
}
