#include "matrix.hpp"
#include <cmath>
#include <iostream>

extern double* vector_sigmoid_CUDA(double* x, double* y, int size);

//variavel global hardcodada que diz quantas iteracoes do gradient descent step faremos 
int epoch = 6000; 

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


double y_hat (double x, double w0, double w1){
    return w0 + w1*x;
}

void gradient_descent_step(double* novos_pesos, double peso1, double peso2, double* input, double* output, double taxa_de_aprendizado, double sample_size){
    std::cout << "To no passo do gradiente descendente" << std::endl;
    double erro_w0 = 0;
    double erro_w1 = 0;
    
    for (int i = 0; i < sample_size; i++){
        erro_w0 = erro_w0 + (y_hat(input[i], novos_pesos[0], novos_pesos[1]) - output[i]);
        erro_w1 = erro_w1 + (y_hat(input[i], novos_pesos[0], novos_pesos[1]) - output[i]) * input[i];
    }
    double new_w0 = novos_pesos[0] - taxa_de_aprendizado * (1/sample_size) * erro_w0; 
    double new_w1 = novos_pesos[1] - taxa_de_aprendizado * (1/sample_size) * erro_w1;
    //eu tenho que mudar p so passar o valor ao inves do endereco;
    novos_pesos[0] = new_w0;
    novos_pesos[1] = new_w1;
}



// double* simple_gradient_descent(double w_0, double w_1, double taxa_de_aprendizado){
//     unsigned int n = 0;     // numero de iteracoes
//     for (int i = 0; i < n; i++){                            
//         w_0 = w_0 - taxa_de_aprendizado * gradiente_(w_o)   
//         w_1 = w_1 - taxa_de_aprendizado * gradiente_(w_1)
//     }
// }


double mse(double* input, double* output, double peso1, double peso2, double sample_size){
    double custo = 0;
    for (int i = 0; i < sample_size; i++){
        custo = custo + pow((y_hat(input[i], peso1, peso2) - output[i]),2);
        std::cout << "To calculando o erro" << std::endl;
        std::cout << custo << std::endl;

    }
    std::cout << "custo: " << custo << std::endl;
    std::cout << "custo/sample_size: " << custo/sample_size << std::endl;
    
    return custo/sample_size;
}

//receber como parametros matrizes de pesos, as entradas e as saidas
double multiple_variables_mse(c_matrix& weighs, c_matrix& features, c_matrix& output){
    //matriz de erros 
    c_matrix error = features * (weighs.transpose()) + ((-1)*output);
    //i need to sum all over here. sum (error * error)
    c_matrix cost = error * error;

    //return cost/m;
    return 0;
    
}

void multiple_variable_gradient_descent(c_matrix& weighs, c_matrix& features, c_matrix& output, double taxa_de_aprendizado, unsigned int epoch){
    //i need to define matrix dimension 
    //c_matrix cost;
    //i will just call null matrix when the matrix is well defined 
    //cost.null_matrix();

    //size() n parece q ta implementado 
    //weighs = weighs - taxa_de_aprendizado/(features.size()) * //sum ((features * (weighs.transpose()) + (-1)*output) * features

    //preciso implementar a sobrecarga de operador: [][] 
    //cost[i] = multiple_variables_mse(weighs, features, output);

    //return weight and cost;

}

//custo precisa ter o mesmo tamanho da epoca
void gradient_descent(double* custo, double* novos_pesos, double* input, double* output, double peso1, double peso2, double taxa_de_aprendizado, double epoch, double sample_size){
    std::cout << "to no gradiente descendente principal" << std::endl;
    for (int i = 0; i < epoch; i++){
        std::cout << "passo gradiente descente: " << i << std::endl;
    
        //temos um array que guarda dois pesos que sao atualizados a cada chamada
        // a cada eu preciso usar os novos pesos
        gradient_descent_step(novos_pesos, peso1, peso2, input, output, taxa_de_aprendizado, sample_size);
        std::cout << "sai do gradiente step: " << i << std::endl;
        
        //temos um array de custo de tamanho epoch que guarda o erro quadratico de cada iteracao
        custo[i] = mse(input,output, peso1, peso2,sample_size);
        std::cout << "sai da chamada do mse: " << i << std::endl;
        
    }
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

    double* novos_pesos = 0;
    novos_pesos = new double[2];

    gradient_descent_step(novos_pesos, w_0, w_1, input, output, taxa_de_aprendizado, 3);
    
    std::cout << novos_pesos[0] << "\t" << novos_pesos[1] << std::endl;

    double* custo = 0;
    custo = new double[epoch];
    //custo = {0};
    
    //(double* custo, double* novos_pesos, double* input, double* output, double peso1, double peso2, double taxa_de_aprendizado, double epoch, double sample_size)
    
    gradient_descent(custo, novos_pesos, input, output, w_0, w_1, taxa_de_aprendizado, epoch, 3);
    
    std::cout << novos_pesos[0] << "\t" << novos_pesos[1] << std::endl;

    

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