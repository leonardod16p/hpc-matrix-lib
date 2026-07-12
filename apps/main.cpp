#include "matrix.hpp"
#include <iostream>

using namespace std;

extern void hello_cuda();

extern c_matrix multiply_CUDA(const c_matrix& obj);



int main (){

    cout << "main.cpp entrando em acao" << std::endl;

    //hello_cuda();

    cout << "main.cpp de novo" << std::endl;
    //c_matrix A(4,4);
    // c_matrix B(4,4);
    // A.define_values(false,10);
    // B.define_values(false,10);
    // // // cout << "Testing c_matrix multiplication and multiplication by scalar: " << endl;
    // A.show_matrix();
    // B.show_matrix();
    // c_matrix C = A * B;
    // (C).show_matrix();
    // (A.multiply_ikj(B)).show_matrix();
    // (A.multiply_SIMD(B)).show_matrix();
    
    // (3*A).show_matrix();
    // (A*B+A*B).show_matrix();
    // c_square_matrix C(3);
    // C.define_values();
    // cout << "Testing c_square_matrix multiplication and multiplication by scalar: " << endl;
    // C.show_matrix();
    // (C+C).show_matrix();
    // (C*C).show_matrix();
    // (3*C).show_matrix();

    // c_lower_triangular_matrix G(3);
    // G.define_values();
    // cout << "Testing c_lower_triangular_matrix multiplication and multiplication by scalar: " << endl;
    // G.show_matrix();
    // (G+G).show_matrix();
    // (G*G).show_matrix();
    // (3*G).show_matrix();

    // c_diagonal_matrix I(3);
    // I.define_values();
    // cout << "Testing c_diagonal_matrix multiplication and multiplication by scalar: " << endl;
    // I.show_matrix();

    // (I+I).show_matrix();
    // (I*I).show_matrix();
    // (3*I).show_matrix();

}