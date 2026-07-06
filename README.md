# High Performance Library in C++ with CUDA

> Work in Progress: This project is currently under active development

Every matrix is treated as a contiguous 1D memory block under the hood. This architecture favors cache locality, minimizes random memory access, and acts as the perfect foundation for High-Performance Computing (HPC).


### Goals


- Memory Optimization
- CPU Parallelism
- GPU Acceleration


### Application: Neural Networks

The ultimate goal of this library is to serve as the mathematical engine for a fully custom Feedforward Neural Network (Multilayer Perceptron) built entirely from scratch, without external dependencies like PyTorch or TensorFlow.