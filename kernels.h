/* 
 * File:   kernels.h
 * Author: nell
 *
 * Created on 1 juillet 2013, 20:04
 */

#ifndef KERNELS_H
#define	KERNELS_H

//template<typename P, typename W>
//__global__ void kernel(P* data, P* retour, W objSize, P objUtility, W knapsackSize, W wmax);

template<typename P, typename W>
void cudaAcceleratedAlgorithm(dim3 blocksPerGrid, dim3 threadsPerBlock, P* data, P* retour, W objSize, P objUtility, W knapsackSize, W wmax);

#endif	/* KERNELS_H */

