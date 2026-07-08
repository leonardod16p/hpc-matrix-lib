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

c_matrix::c_matrix(int a, int b, bool alocar_memoria){
    m = a;
    n = b;
    //se for falso, n vamos alocar memoria a partir daqui
    if (alocar_memoria == false) {
        matrix = nullptr; 
    } else {
        matrix = new double[m * n];
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

c_matrix c_matrix::transpose() {
    c_matrix result(n, m);
    result.null_matrix();
    int a_line = 0;
    int b_line = 0;
    int i = 0;
    int j = 0;
    while (i < m) {
        a_line = i * n;
        j = 0;
        while (j < n) {
            b_line = j * m;
            *(result.matrix + b_line + i) = *(matrix + a_line + j);
            ++j;
        }
        ++i;
    }
    return result;
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


/*

Square Matrix Implementation

*/

double c_square_matrix :: trace() {
    int line = 0;
    int column = 0;
    double sum = 0;
    while (column < m) {
        line = column * m;
        sum = sum + *(matrix + line + column);
        ++column;
    }
    return sum;
}

/*

Implementing lower triangular matrix

*/

//chamamos o construtor com o false para que ele n aloque memoria duas vezes
c_lower_triangular_matrix::c_lower_triangular_matrix(int a) : c_square_matrix{ a, false } {
    //calculate the memory allocation
    int count = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= i; ++j) {
            count = count + 1;
        }
    }
    unsigned int byte_size_vec = count;
        
    // using new to allocate memory

    matrix = new double[count];

    cout << "Created a " << byte_size_vec << " size array that corresponds to a: " << m << " by " << n << " matrix" << endl;
        
    //if (!(matrix = (double*)malloc(byte_size_vec))) {
    //    cout << "No memory" << endl;
    //    exit(1);
    //}
    //cout << "First Element Address: " << matrix << endl;
    //cout << "Last Element Address: " << matrix + m * m - 1 << endl;
    //cout << "Sizeof: " << byte_size_vec << endl;
    //size_t true_length = portable_ish_malloced_size(matrix);
    //printf("%zu\n", true_length);
};



c_lower_triangular_matrix c_lower_triangular_matrix::operator+(c_lower_triangular_matrix const& obj) {
    c_lower_triangular_matrix result(m);
    int line = 0;
    int index = 0;

    for (int i = 1; i - 1 < m; i++) {
        line = (i - 1) * (i) / 2;
        for (int j = 0; j < i; j++) {
            index = line + j;
            *(result.matrix + index) = *(matrix + index) + *(obj.matrix + index);
        }
        cout << endl;
    }
    return result;
}

c_lower_triangular_matrix c_lower_triangular_matrix::operator*(c_lower_triangular_matrix const& obj) {
    c_lower_triangular_matrix result(m);
    int a_line = 0;
    int b_line = 0;
    double sum = 0;
    double a_ik = 0;
    double b_kj = 0;
    int k = 0;

    for (int i = 1; i - 1 < m; ++i) { //iniciei i = 1 e deixei i-1
        a_line = (i - 1) * (i) / 2;
        for (int j = 0; j < i; ++j) {
            k = j;
            sum = 0;
            while  (k < i) {
                b_line = (k) * (k+1) / 2;
                a_ik = *(matrix + a_line + k);
                b_kj = *(obj.matrix + b_line + j);
                sum = sum + a_ik * b_kj;
                ++k;
            }
            *(result.matrix + a_line + j) = sum;
        }
    }
    return result;
}

c_lower_triangular_matrix operator*(c_lower_triangular_matrix A, double lambda){
    int line = 0;
    int index = 0;

    c_lower_triangular_matrix result(A.m);
    for (int i = 1; i - 1 < A.m; i++) {
        line = (i - 1) * (i) / 2;
        for (int j = 0; j < i; j++) {
            index = line + j;
            *(result.matrix + index) = lambda*(*(A.matrix + index));
        }
        cout << endl;
    }
    return result;
}

c_lower_triangular_matrix operator*(double lambda, c_lower_triangular_matrix A){
    int line = 0;
    int index = 0;

    c_lower_triangular_matrix result(A.m);
    for (int i = 1; i - 1 < A.m; i++) {
        line = (i - 1) * (i) / 2;
        for (int j = 0; j < i; j++) {
            index = line + j;
            *(result.matrix + index) = lambda*(*(A.matrix + index));
        }
        cout << endl;
    }
    return result;
}

/*

lower triangular matrix methods

*/


double* c_lower_triangular_matrix :: getmatrix(){
    return matrix;
}


int c_lower_triangular_matrix :: getfirstdimension(){
    return m;
}

int c_lower_triangular_matrix :: getseconddimension(){
    return m;
}


void c_lower_triangular_matrix::define_values() {
    cout << "To enter an element, type the number you want and press enter: " << endl;
    int line = 0;
    int index = 0;

    for (int i = 1; i - 1 < m; i++) {
        line = (i - 1) * (i) / 2;
        for (int j = 0; j < i; j++) {
            index = line + j;
            cin >> *(matrix + index);
        }
        cout << endl;
    }
}

void c_lower_triangular_matrix::show_matrix(){
    int line = 0;
    int index = 0;

    for (int i = 1; i - 1 < m; i++) {
        line = (i - 1) * (i) / 2;
        for (int j = 0; j < i; j++) {
            index = line + j;
            cout <<  *(matrix + index) << " ";
        }
        cout << endl;
    }
}

double c_lower_triangular_matrix::det() {
    double prod = 1;
    int line = 0;
    int diagonal_index = 0;

    for (int i = 0; i < m; i++) {
        line = i * (i + 1) / 2;
        diagonal_index = line + i;
        prod = prod * (*(matrix + diagonal_index));
        }

    return prod;
}

double c_lower_triangular_matrix::trace(){
    double sum = 0;
    int line = 0;
    int diagonal_index = 0;

    for (int i = 0; i < m; i++) {
        line = i * (i + 1) / 2;
        diagonal_index = line + i;
        sum = sum + (*(matrix + diagonal_index));
        }

    return sum;
}

c_square_matrix c_lower_triangular_matrix::converting(){
    double* matrix_result = nullptr;
    c_square_matrix result(m);
    result.null_matrix();
    matrix_result = result.getmatrix();

    int a_line = 0;
    int b_line = 0;
    double value = 0;
    for (int i = 0; i  < m; i++) {
        a_line = i * m;
        b_line = (i + 1) * (i) / 2;
        for (int j = 0; j - 1 < i; j++) {
            *(matrix_result + a_line + j) = *(matrix + b_line + j);
        }
        cout << endl;
    }
    return result;
}

c_matrix c_lower_triangular_matrix::transpose(c_lower_triangular_matrix A) { 

    //Low Quality Code
    c_matrix result(A.getfirstdimension(), A.getfirstdimension());

    result = A.converting();
    result = result.transpose();
    return result;
}

/*
upper triangular matrix
*/


c_upper_triangular_matrix::c_upper_triangular_matrix(int a) : c_square_matrix{ a, false }{
    m = a;
    //calculate the memory allocation
    //The same memory size as the lower
    int count = 0;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j <= i; ++j) {
            count = count + 1;
        }
    }
    unsigned int byte_size_vec = count;
    
    matrix = new double[byte_size_vec];

    cout << "Created a " << byte_size_vec << " size array that corresponds to a: " << m << " by " << n << " matrix" << endl;
    

    //if (!(matrix = (double*)malloc(byte_size_vec))) {
    //    cout << "No memory" << endl;
    //    exit(1);
    //}
    //cout << "First Element Address: " << matrix << endl;
    //cout << "Last Element Address: " << matrix + m * m - 1 << endl;
    //cout << "Sizeof: " << byte_size_vec << endl;
    size_t true_length = portable_ish_malloced_size(matrix);
    //printf("%zu\n", true_length);
};

c_upper_triangular_matrix c_upper_triangular_matrix::operator+(c_upper_triangular_matrix const& obj) {
    c_upper_triangular_matrix result(m);
    int line = 0;
    int index = 0;
    int discount = 0;
    for (int i = 1; i - 1 < m; i++) {
        for (int j = 0; j < discount + m; j++) {
            *(result.matrix + line + j) = *(matrix + line + j) + *(obj.matrix + line + j);
        }
        line = line + discount + m;
        discount--;
        cout << endl;
    }
    return result;
}


/*
Upper Matrix Methods
*/


double* c_upper_triangular_matrix :: getmatrix(){
    return matrix;
}

int c_upper_triangular_matrix :: getfirstdimension(){
    return m;
}

int c_upper_triangular_matrix :: getseconddimension(){
    return m;
}

void c_upper_triangular_matrix::define_values() {
    cout << "To enter an element, type the number you want and press enter: " << endl;
    int line = 0;
    int index = 0;
    int discount = 0;
    for (int i = 1; i - 1 < m; i++) {
        for (int j = 0; j < discount + m; j++) {
            cin >> *(matrix + line + j);
        }
        line = line + discount + m;
        discount--;
        cout << endl;
    }

}

void c_upper_triangular_matrix::show_matrix() {
    //the formatting would be good only if all the elements of the matrix has size of 1 (in the sense of representation by strings, e.g size(142) = 3)
    //We could implement a better solution by creating an algorithm that checks the maximum size of the elements of the matrix
    //Then, we could use this maximum size to fix the amount of spaces needed
    int line = 0;
    int index = 0;
    int discount = 0;
    string space = "";
    for (int i = 1; i - 1 < m; i++) {
        cout << space;
        for (int j = 0; j < discount + m; j++) {
            cout <<  *(matrix + line + j) << " ";
        }
        space = space + " " + " ";
        line = line + discount + m;
        discount--;
        cout << endl;
    }
}

double c_upper_triangular_matrix::det() {
    int line = 0;
    int index = 0;
    int discount = 0;
    double prod = 1;
    for (int i = 1; i - 1 < m; i++) {
            prod = prod* (*(matrix + line ));
            line = line + discount + m;
            discount--;
        }
    cout << endl;
    return prod;
}

double c_upper_triangular_matrix::trace(){
    int line = 0;
    int index = 0;
    int discount = 0;
    double sum = 0;
    for (int i = 1; i - 1 < m; i++) {
            sum = sum* (*(matrix + line ));
            line = line + discount + m;
            discount--;
        }
    cout << endl;
    return sum;
}

c_matrix c_upper_triangular_matrix :: transpose(c_upper_triangular_matrix A) { 

    //Low Quality code
    c_matrix result(A.getfirstdimension(), A.getfirstdimension());

    result = A.converting();
    result = result.transpose();
    return result;
}


c_square_matrix c_upper_triangular_matrix::converting(){
    double* matrix_result = nullptr;
    c_square_matrix result(m);
    result.null_matrix();
    matrix_result = result.getmatrix();
    int a_line = 0;
    double value = 0;

    int i = 0;
    int j = 0;
    int k = 0;
    while(i < m) {
        a_line = (i) * m;
        while(j < m){
            *(matrix_result + a_line + j) = *(matrix + k);
            j++;
            k++;
        }
        i++;
        j = i;
        cout << endl;
    }

    return result;
}