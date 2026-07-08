#pragma once
#include <iostream>

using namespace std;

/*
Classes Definitions
*/


class c_matrix {
    protected:
        int m, n;
        double* matrix;
        //Isso previni que aloquemos memoria duas vezes nas matrizes com alocacao personalizada
        //antes alocava no construtor da classe filha e novamente na classe c_matrix
        c_matrix(int a, int b, bool alocar_memoria);

    public:

        c_matrix(int a, int b);
        virtual ~c_matrix();

        c_matrix(const c_matrix& obj);
        c_matrix& operator=(const c_matrix& obj);


        c_matrix operator+(const c_matrix& obj) const;
        c_matrix operator*(const c_matrix& obj) const;
        c_matrix transpose();

        friend c_matrix operator*(double, c_matrix);
        friend c_matrix operator*(c_matrix, double);


        int getfirstdimension();
        int getseconddimension();
        int setfirstdimension(int a);


        double* getmatrix();
        void setmatrix(double value, double* address);
        //if isInput == true, them input from IO to the user. Else fullfill with all elements to value_to_fill
        void define_values(bool isInput, double value_to_fill);

        void show_matrix() const;
        void null_matrix();
        
        c_matrix multiply_ikj(const c_matrix& obj) const;
        c_matrix multiply_SIMD(const c_matrix& obj) const;
        c_matrix multiply_CUDA(const c_matrix& obj) const;
};


class c_square_matrix : public c_matrix {

    protected:
        //como as matrizes filhas herdam da matriz quadrada, precisamos repassar a 
        //mensagem de alocacao por ela 
        c_square_matrix(int a, bool alocar_memoria) : c_matrix(a, a, alocar_memoria) {}
    public:

    using c_matrix::c_matrix;
    c_square_matrix(int a) :c_matrix(a,a) {

        //se tiver mais parametros ele vai criar uma matriz com colunas e linhas de tamanhos diferentes
        //exemplo: c_square_matrix teste2(2,3); eh permitido. pq ele ta simplesmente usando construtor de 
        //c_matrix
        
        cout << "Square Matrix Created" << endl;
    
    };
    
    double trace();

};


class c_lower_triangular_matrix : public c_square_matrix {
    
public:
    int getfirstdimension();
    int getseconddimension();

    /*
    Method to convert any type of matrix to c_square_matrix. 
    We are going to use this to overload operators on classes of different hierarchies
    */

    c_square_matrix converting();
    double* getmatrix();

    c_lower_triangular_matrix(int a);

    c_lower_triangular_matrix operator+(c_lower_triangular_matrix const& obj);
    c_lower_triangular_matrix operator*(c_lower_triangular_matrix const& obj);
    

    friend c_lower_triangular_matrix operator*(double, c_lower_triangular_matrix);
    friend c_lower_triangular_matrix operator*(c_lower_triangular_matrix, double);

    void define_values(bool isInput, double value_to_fill);
    void show_matrix();
    c_matrix transpose(c_lower_triangular_matrix);
    double det();
    double trace();
};

class c_upper_triangular_matrix : public c_square_matrix {
public:

    int getfirstdimension();
    int getseconddimension();
    
    /*
    Method to convert any type of matrix to c_square_matrix. 
    We are going to use this to overload operators on classes of different hierarchies
    */
    c_square_matrix converting();
    
    double* getmatrix();

    c_upper_triangular_matrix(int a);


    c_upper_triangular_matrix operator+(c_upper_triangular_matrix const& obj);
    c_upper_triangular_matrix operator*(c_upper_triangular_matrix const& obj);

    friend c_upper_triangular_matrix operator*(double, c_upper_triangular_matrix);
    friend c_upper_triangular_matrix operator*(c_upper_triangular_matrix, double);
    
    void define_values(bool isInput, double value_to_fill);;
    void show_matrix();
    
    c_matrix transpose(c_upper_triangular_matrix);
    
    double det();
    double trace();
};

class c_diagonal_matrix : public c_square_matrix {
public:

    /*
    Method to convert any type of matrix to c_square_matrix. 
    We are going to use this to overload operators on classes of different hierarchies
    */
    c_square_matrix converting();

    c_diagonal_matrix(int a);

    int getfirstdimension();
    int getseconddimension();
    double* getmatrix();
    void setmatrix(double value, double* address);
    
    friend c_diagonal_matrix operator*(double, c_diagonal_matrix);
    friend c_diagonal_matrix operator*(c_diagonal_matrix, double);

    void define_values(bool isInput, double value_to_fill);;
    void show_matrix();
    double det();
    double trace();
    void null_matrix();

};