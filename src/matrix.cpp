#include "matrix.hpp"
#include <iostream>
#include <typeinfo>
#include <malloc.h>

size_t portable_ish_malloced_size(const void* p) {
    return malloc_usable_size((void*)p);
}

using namespace std;

c_matrix::c_matrix(int a, int b) {
        m = a;
        n = b;
        //calculate the memory allocation
        unsigned int byte_size_vec = m * n;
        
        matrix = new double[byte_size_vec];

        cout << "Created a " << byte_size_vec << " size array that corresponds to a: " << m << " by " << n << " matrix" << endl;

        //if (!(matrix = (double*)malloc(byte_size_vec))) {
        //    cout << "No memory" << endl;
        //    exit(1);
        //}
        //cout << "First Element Address: " << matrix << endl;
        //cout << "Last Element Address: " << matrix + m * n - 1 << endl;
        //cout << "Sizeof: " << byte_size_vec << endl;
        size_t true_length = portable_ish_malloced_size(matrix);
        printf("%zu\n", true_length);
    };


c_matrix::~c_matrix(){
    if (matrix != nullptr){
        delete[] matrix;
        cout << "Memory deallocation succeed." << endl;
    }

}


// copying matrix

c_matrix::c_matrix(const c_matrix& obj) {
    m = obj.m;
    n = obj.n;
    unsigned int byte_size_vec = m * n;
    matrix = new double[byte_size_vec];
    for (int i = 0; i < byte_size_vec; ++i) {
        *(matrix + i ) = *(obj.matrix + i);
    }
}


c_matrix& c_matrix::operator=(const c_matrix& obj) {
    if (this == &obj) return *this; 

    delete[] matrix; 
    
    m = obj.m;
    n = obj.n;
    unsigned int byte_size_vec = m * n;
    matrix = new double[byte_size_vec];
    for (int i = 0; i < byte_size_vec; ++i) {
        *(matrix + i ) = *(obj.matrix + i);
    }
    return *this;
}


/*

Defining Operations

*/

c_matrix c_matrix::operator+(const c_matrix& obj) const{


        //vou ter q usar o get e set
        //g++ ta reclamando que m e n tao privados
        c_matrix result(obj.m, obj.n);
        int line = 0;
        int column = 0;
        int i = 0;
        while (i < obj.m) {
            column = 0;
            line = i * obj.n;
            while (column < obj.n) {
                //usando um setter provisorio que na vdd eh um get que nos da o endereco
                *(result.matrix + line + column) = *(matrix + line + column) + *(obj.matrix + line + column);
                ++column;
            }
            ++i;
        }
        return result;
    }


c_matrix c_matrix::operator*(const c_matrix& obj) const {
    //Two matrices multiplication of size m*n and n*p
    //Resulting matrix must be of m*p size
    //m x n * n x p
    int p = obj.n;
    if (n == obj.m) {
        c_matrix result(obj.m, p); //deveria ser m e nao obj.m
        result.null_matrix();
        int a_line = 0;
        int b_line = 0;
        int c_line = 0;
        double sum = 0;
        double a_ik = 0;
        double b_kj = 0;
        for (int i = 0; i < m; ++i) {
            a_line = i * n;
            for (int j = 0; j < p; ++j) {
                sum = 0;
                for (int k = 0; k < n; ++k) {
                    b_line = k * p;
                    a_ik = *(matrix + a_line + k);
                    b_kj = *(obj.matrix + b_line + j);
                    sum = sum + a_ik * b_kj;
                }
                *(result.matrix + i*p + j) = sum;
            }
        }
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


 c_matrix operator*(double lambda, c_matrix A){
    int line = 0;
    int column = 0;
    int i = 0;
    int m = A.m;
    int n = A.n;
    c_matrix result(m,n);
    double* matrix = nullptr;
    matrix = A.matrix;
    while (i < m) {
        column = 0;
        line = i * n;
        while (column < n) {
            *(result.matrix + line + column) = lambda*(*(matrix + line + column)) ;
            ++column;
        }
        ++i;
    }
    return result;
};

c_matrix operator*(c_matrix A, double lambda){
    int line = 0;
    int column = 0;
    int i = 0;
    int m = A.m;
    int n = A.n;
    c_matrix result(m,n);
    double* matrix = nullptr;
    matrix = A.matrix;
    while (i < m) {
        column = 0;
        line = i * n;
        while (column < n) {
            *(result.matrix + line + column) = lambda*(*(matrix + line + column)) ;
            ++column;
        }
        ++i;
    }
    return result;
};


/*
c_matrix Methods
*/

int c_matrix :: getfirstdimension(){
    return m;
}

int c_matrix :: getseconddimension(){
    return n;
}

double* c_matrix :: getmatrix(){
    return matrix;
}

void c_matrix :: setmatrix(double value, double* address){
    *address = value;
};


void c_matrix::null_matrix() {
    int line = 0;
    int column = 0;
    int i = 0;
    while (i < m) {
        column = 0;
        line = i * n;
        while (column < n) {
            *(matrix + line + column) = 0;
            ++column;
        }
        ++i;

    }
}

void c_matrix::define_values() {
    cout << "To enter an element, type the number you want and press enter: " << endl;
    int line = 0;
    int column = 0;
    int i = 0;
    while (i < m) {
        column = 0;
        line = i * n;
        while (column < n) {
            cin >> *(matrix + line + column);
            ++column;
        }
        ++i;

    }
}

void c_matrix::show_matrix() const {
    int line = 0;
    int column = 0;
    int i = 0;
    while (i < m) {
        column = 0;
        line = i * n;
        while (column < n) {
            cout << *(matrix + line + column) << "\t";
            ++column;
        }
        cout << endl;
        ++i;

    }
}

