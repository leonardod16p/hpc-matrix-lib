#include "matrix.hpp"
#include <cmath>
#include <iostream>

extern double* vector_sigmoid_CUDA(double* x, double* y, int size);

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


// gradiente descendente numa reta linear simples 
// w_ 0 = w_0 - taxa_de_aprendizado * gradiente_(w_o)
// w_ 1 = w_1 - taxa_de_aprendizado * gradiente_(w_1)

double gradiente_w0(double estimative_value, double real_value, double x, double sample_size){
    double sum = 0;
    for (int i = 0; i < sample_size; i++){
        sum  = sum + (1/sample_size)*(estimative_value - real_value);
    }
    return sum;
}

double gradiente_w1(double estimative_value, double real_value, double x, double sample_size){
    double sum = 0;
    for (int i = 0; i < sample_size; i++){
        sum  = sum + (1/sample_size)*(estimative_value - real_value) * x;
    }
    return sum;
}

// double* simple_gradient_descent(double w_0, double w_1, double taxa_de_aprendizado){
//     unsigned int n = 0;     // numero de iteracoes
//     for (int i = 0; i < n; i++){                            
//         w_0 = w_0 - taxa_de_aprendizado * gradiente_(w_o)   
//         w_1 = w_1 - taxa_de_aprendizado * gradiente_(w_1)
//     }
// }



int main(){
    double x = 0;
    double* vector = 0;
    double* vector_result = 0;
    vector = new double[3];
    vector_result = new double[3]; 

    vector[0] = 0;
    vector[1] = 0.5;
    vector[2] = 1.256;

    /*a conta da certa, mas se eu tento rodar de novo a funcao que calcula embaixo os valores ja sao outros
    parece que eu to modificando valores que eu n deveria modificar*/
    vector_sigmoid_CUDA(vector, vector_result, 3);


    vector_result = vector_sigmoid(vector,3);
    
    for (int i = 0; i < 3; i++){
        std::cout << "Valor da funcao sigmoid: " << vector_result[i] << " avaliada em " << vector[i] << endl;
    }


    std::cout << "Valor da funcao sigmoid: " << scalar_sigmoid(1/4+1/2-1) << " avaliada em "<< 1/4+1/2-1 << endl;

    vector_sigmoid_CUDA(vector, vector_result, 3);

}