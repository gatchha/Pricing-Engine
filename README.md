# C++ High-Performance Pricing Engine

## Description
A financial options pricing engine developed in C++. The objective of this project is to leverage low-level software engineering (C++) to solve the latency bottleneck associated with intensive stochastic computing, featuring a performance benchmark against Python.

## Features
* **Closed-form Solution:** Black-Scholes model and Greeks calculation.
* **Standard Monte Carlo:** European Call Option (with Antithetic Variates for variance reduction).
* **Path-Dependent Monte Carlo:** Asian Call Option (Arithmetic mean over 252 days).
* **Barrier Monte Carlo:** Up-and-Out Option with conditional deactivation optimization (early-exit) to save CPU cycles.

## Performance Benchmark
A cross-language C++ vs Python script is included to measure execution time on exotic products (requiring up to 252 million iterations). The native C++ code demonstrates a massive speedup (x50 factor) compared to the Python implementation, validating the architectural choice for this type of stochastic load.

## Build and Execution
The project uses CMake for the build process.

```bash
# Build the project
mkdir build && cd build
cmake ..
make

# Run the performance benchmark
./Pricing-Engine