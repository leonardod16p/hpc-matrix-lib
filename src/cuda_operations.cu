#include <iostream>
#include <stdio.h>
#include "matrix.hpp"

__global__ void kernel_multiply_CUDA(double* matrix1, double* matrix2, double* matrix3, int m, int n, int p){
    //ao inves de calcular a_line e b_line eu vou usar o int id e a propria arquitetura da gpu
    //instead of calcuting a_line and b_line im going to use int id and the gpu architecture itself
    //so i dont need to create indexes to acess the matrix data
    //i already have blockId, blockDim and threadId 
    //device_matrix1, device_matrix2, device_matrix3
    //coordenada x e y substitui os for
    //usando id global do y como linha conseguimos lancar alem de threads simultaneas, tambem blocos simultaneos

    int linha = blockIdx.y * blockDim.y + threadIdx.y;
    int coluna = blockIdx.x * blockDim.x + threadIdx.x;
    
    if (linha < m && coluna < p){
    //normal ijk sequence loop
        double sum = 0;
        for (int k = 0; k < n; ++k) {
            sum = sum + matrix1[linha * n + k] * matrix2[k * p + coluna];
        }
        matrix3[linha*p + coluna] = sum;
    }

}



c_matrix c_matrix::multiply_CUDA(const c_matrix& obj) const{
    //Two matrices multiplication of size m*n and n*p
    //Resulting matrix must be of m*p size
    //m x n * n x p
    int p = obj.n;
    if (n == obj.m) {
        c_matrix result(m, p); //deveria ser m e nao obj.m
        result.null_matrix();
    
        int matrix1_size = m * n; 
        int matrix2_size = obj.m * p;
        int matrix3_size = m * p;
        
        //a gpu precisa saber a quatidade de memoria a ser reservada
        int byte_matrix1_size = matrix1_size * sizeof(double); 
        int byte_matrix2_size = matrix2_size * sizeof(double); 
        int byte_matrix3_size = matrix3_size * sizeof(double); 
      
        //criamos tres ponteiros vazios na CPU que vao apontar para um endereço VRAM
        double* device_matrix1;
        double* device_matrix2;
        double* device_matrix3;

        //cudamalloc pede o endereço do ponteiro por isso os dois asteriscos 
        cudaMalloc((void**)&device_matrix1, byte_matrix1_size);

        cudaMalloc((void**)&device_matrix2, byte_matrix2_size);

        cudaMalloc((void**)&device_matrix3, byte_matrix3_size);



        //Aqui eu vou ter q copiar as duas para vram
        //copia a primeira matriz p memoria
        cudaMemcpy(device_matrix1, matrix, byte_matrix1_size, cudaMemcpyHostToDevice);
        //copia a segunda memoria p segunda matriz

        cudaMemcpy(device_matrix2, obj.matrix, byte_matrix2_size, cudaMemcpyHostToDevice);
        
        //copying the result matrix to the vram
        cudaMemcpy(device_matrix3, result.matrix, byte_matrix3_size, cudaMemcpyHostToDevice);
 
        //definindo o tamanho do bloco
        dim3 threads_por_bloco(16,16);


        //we need to fit our block into the result matrix
        //this follow Output-Driven Design in GPU algorithms 
        //numero de blocos que precisamos em cada diferecao do grid
        int blocos_x = (p + 16 - 1) / 16;
        int blocos_y = (m + 16 - 1) / 16;

        dim3 numero_de_blocos(blocos_x, blocos_y);


        //chamando o kernel

        kernel_multiply_CUDA<<<numero_de_blocos, threads_por_bloco>>>(device_matrix1, device_matrix2, device_matrix3, m, n, p);
        

        //funcao de debug 
        cudaError_t erro = cudaGetLastError();
        if (erro != cudaSuccess) {
            printf("\n ultimo erro: %s\n", cudaGetErrorString(erro));
        }


        //esperamos a gpu terminar
        cudaDeviceSynchronize();
        
        
        //pegando a operacao terminada loaded in the vram device_matrix and puting in main memory on matrix.result address 
        //armazenando o resultado na matriz construida m x n chamada result
        cudaMemcpy(result.matrix, device_matrix3, byte_matrix3_size, cudaMemcpyDeviceToHost);

 
        //deallocating all the three vram matrix memory
        cudaFree(device_matrix1);
        cudaFree(device_matrix2);   
        cudaFree(device_matrix3);   

        //vendo o resultado na cpu
        //for (int i = 0; i < matrix3_size; i++) {
        //    cout << "resultado " << i << ": " << result.matrix[i] << "\t";
        //}


        // retornamos o objeto matriz 
        return result;
        }
    else {
        cout << "Matrix multiplication Undefined" << endl;
        cout << "First Matrix" << endl;
        cout << "m:  " << m << "\t" << "n:  " << n << "\t" << endl;
        cout << "Second Matrix" << endl;
        cout << "m:  " << obj.m << "\t" << "n:  " << obj.n << "\t" << endl;
        throw "You cannot perform this operation!";
    }

}