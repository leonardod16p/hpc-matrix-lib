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
        void define_values();

        void show_matrix() const;
        void null_matrix();
        
};


class c_square_matrix : public c_matrix {
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
    c_square_matrix converting();
    double* getmatrix();

    c_lower_triangular_matrix(int a);

    c_lower_triangular_matrix operator+(c_lower_triangular_matrix const& obj);
    c_lower_triangular_matrix operator*(c_lower_triangular_matrix const& obj);
    

    friend c_lower_triangular_matrix operator*(double, c_lower_triangular_matrix);
    friend c_lower_triangular_matrix operator*(c_lower_triangular_matrix, double);

    void define_values();
    void show_matrix();
    c_matrix transpose(c_lower_triangular_matrix);
    double det();
    double trace();
};