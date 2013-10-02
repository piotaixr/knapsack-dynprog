


template<typename P, typename W>
__global__ void kernel(P* data, P* retour, W objSize, P objUtility, W knapsackSize, W wmax) {
    unsigned i = blockDim.x * blockIdx.x + threadIdx.x;
    retour[wmax + i] = max(data[wmax + i], data[wmax + i - objSize] + objUtility);
}

template<typename P, typename W>
void cudaAcceleratedAlgorithm(dim3 blocksPerGrid, dim3 threadsPerBlock, P* data, P* retour, W objSize, P objUtility, W knapsackSize, W wmax) {
    kernel<P, W><<<blocksPerGrid, threadsPerBlock >>>(data, retour, objSize, objUtility, knapsackSize, wmax);
}