# High Performance Library in C++ with CUDA

> Work in Progress: This project is currently under active development

All matrices are implemented as contiguous 1D memory blocks. For triangular and diagonal matrices, memory is dynamically mapped to store only the required structural regions (e.g., the lower/upper triangle), avoiding the allocation of implicit zeros. This architecture ensures spatial cache locality and eliminates random memory access patterns, aligning with High-Performance Computing (HPC) standards.


### Goals


- Memory Optimization
- CPU Parallelism
- GPU Acceleration


### Application: Neural Networks

The ultimate goal of this library is to serve as the mathematical engine for a fully custom Feedforward Neural Network (Multilayer Perceptron) built entirely from scratch, without external dependencies like PyTorch or TensorFlow.