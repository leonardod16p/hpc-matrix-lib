#include <iostream>
#include <stdio.h>
#include "matrix.hpp"


__global__ void kernel_hello_cuda() {
    printf("thread %d do bloco %d\n", threadIdx.x, blockIdx.x);
}

__global__ void multiply(int* vetor_na_gpu) {
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    int* resultado = 0;
    printf("thread %d do bloco %d\n", threadIdx.x, blockIdx.x);
    printf("id global: %d\n", id);
    printf("id global: %d\n", vetor_na_gpu[id]);
    vetor_na_gpu[id] = vetor_na_gpu[id] * vetor_na_gpu[id]; 

}

__global__ void multiply_CUDA(double* matrix1, double* matrix2){
    int id = blockIdx.x * blockDim.x + threadIdx.x;
    matrix[id]; 
}



void hello_cuda() {
    kernel_hello_cuda<<<2, 4>>>();
    
    cudaDeviceSynchronize();
}


