# High Performance Library in C++ with CUDA

> Work in Progress: This project is currently under active development

All matrices are implemented as contiguous 1D memory blocks. Memory allocation for triangular and diagonal matrices is optimized to store only the structurally relevant elements, implicitly handling structural zeros without allocating them. This architecture ensures spatial cache locality and eliminates random memory access patterns, aligning with standard High-Performance Computing (HPC) practices.


### Goals


- Memory Optimization
- CPU Parallelism
- GPU Acceleration


### Application: Neural Networks

The ultimate goal of this library is to serve as the mathematical engine for a fully custom Feedforward Neural Network (Multilayer Perceptron) built entirely from scratch, without external dependencies like PyTorch or TensorFlow.


## Benchmarks 

### Benchmarks Environment
- CPU: Intel Core I5-10400f
- GPU: Nvidia RTX 4060 8GB
- RAM: 16GB DDR4 2666mhz
- SO: Arch Linux
- Kernel: 7.1.3-arch1-1
- Compiler and Flags: -fno-tree-vectorize | -march=native
- Cuda Version: 13.3