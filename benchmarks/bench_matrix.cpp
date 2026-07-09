#include <benchmark/benchmark.h>
#include "matrix.hpp" 

static void BM_MultiplicacaoMatriz_default(benchmark::State& state) {
    //A 10000x10000 array of doubles is the largest memory allocation my computer can handle safely
    c_matrix A(1000, 1000);
    c_matrix B(1000, 1000);

    A.define_values(false, 10000000000000);
    B.define_values(false, 10000000000000);

    for (auto _ : state) {
        c_matrix C = A * B;
        benchmark::DoNotOptimize(C);
    }
}

BENCHMARK(BM_MultiplicacaoMatriz_default);


static void BM_MultiplicacaoMatriz_ikj(benchmark::State& state) {
    //A 10000x10000 array of doubles is the largest memory allocation my computer can handle safely
    c_matrix A(1000, 1000);
    c_matrix B(1000, 1000);

    A.define_values(false, 10000000000000);
    B.define_values(false, 10000000000000);

    for (auto _ : state) {
        c_matrix C = A.multiply_ikj(B);
        benchmark::DoNotOptimize(C);
    }
}

BENCHMARK(BM_MultiplicacaoMatriz_ikj);



static void BM_MultiplicacaoMatriz_SIMD(benchmark::State& state) {
    //A 10000x10000 array of doubles is the largest memory allocation my computer can handle safely
    c_matrix A(1000, 1000);
    c_matrix B(1000, 1000);

    A.define_values(false, 10000000000000);
    B.define_values(false, 10000000000000);

    for (auto _ : state) {
        c_matrix C = A.multiply_SIMD(B);
        benchmark::DoNotOptimize(C);
    }
}

BENCHMARK(BM_MultiplicacaoMatriz_SIMD);


// int main (){
    
//     c_matrix A(2,3);
//     c_matrix B(3,2);
//     A.define_values();
//     B.define_values();
//     cout << "Testing c_matrix multiplication and multiplication by scalar: " << endl;
//     A.show_matrix();
//     B.show_matrix();
//     (A*B).show_matrix();
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
//}