#include "matrix.hpp"
#include <cmath>
#include <iostream>

double scalar_sigmoid(double x){
    return 1/(1 + std::exp(-x));
}

double* vector_sigmoid(double* x, int size){
    /*
    here it should be interesting to consider parallel operation with CUDA. So here we will call
    gpu kernel 
    */
    double* copy = x;
    for (int i = 0; i < size; i++){
        copy[i] = 1/(1 + std::exp(-x[i]));
    }


    return copy;
}


int main(){
    double x = 0;
    double* vector = 0;
    double* vector_result = 0;
    vector = new double[3];
    vector_result = new double[3]; 

    vector[0] = 0;
    vector[1] = 0.5;
    vector[2] = 1.256;

    //std::cout << "Valor da funcao sigmoid: " << vector_sigmoid(vector) << " avaliada em "<< x << endl;

    vector_result = vector_sigmoid(vector,3);
    
    for (int i = 0; i < 3; i++){
        std::cout << "Valor da funcao sigmoid: " << vector_result[i] << " avaliada em " << vector[i] << endl;
    }

}