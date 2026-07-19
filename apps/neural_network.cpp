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

double y_hat (double x, double w0, double w1){
    return w0 + w1*x;
}

double mse(double* input, double* output, double peso1, double peso2, double sample_size){
    double custo = 0;
    for (int i = 0; i < sample_size; i++){
        custo = custo + pow((y_hat(input[i], peso1, peso2) - output[i]),2);
        std::cout << custo << std::endl;

    }
    return custo/sample_size;
}

int main(){
    double x = 0;
    double* input = 0;
    double* output = 0;
    
    input = new double[3];
    output = new double[3]; 

    input[0] = 0.5;
    input[1] = 2.2;
    input[2] = 2;

    output[0] = 2.0;
    output[1] = 2.5;
    output[2] = 1.4;
    
    
    double taxa_de_aprendizado = 0.01;
    
    double w_0 = 0.1;
    double w_1 = 0.1;

    std::cout << y_hat(1.5,w_0, w_1) << std::endl;

    std::cout << mse(input,output, w_0, w_1,3) << std::endl;


    /*a conta da certa, mas se eu tento rodar de novo a funcao que calcula embaixo os valores ja sao outros
    parece que eu to modificando valores que eu n deveria modificar*/
    //vector_sigmoid_CUDA(vector, vector_result, 3);


    //vector_result = vector_sigmoid(vector,3);
    
    // for (int i = 0; i < 3; i++){
    //     std::cout << "Valor da funcao sigmoid: " << vector_result[i] << " avaliada em " << vector[i] << endl;
    // }


    // std::cout << "Valor da funcao sigmoid: " << scalar_sigmoid(1/4+1/2-1) << " avaliada em "<< 1/4+1/2-1 << endl;

    // vector_sigmoid_CUDA(vector, vector_result, 3);



}