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
        
        cout << "Square Matrix Created" << endl;
    
    };
    
    double trace();

};