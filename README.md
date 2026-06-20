# C++ High-Performance Pricing Engine

## Description
A financial options pricing engine developed in C++. The objective of this project is to leverage low-level software engineering (C++) to solve the latency bottleneck associated with intensive stochastic computing, featuring a performance benchmark against Python.

## Features
* **Closed-form Solution:** Black-Scholes model and Greeks calculation.
* **Standard Monte Carlo:** European Call Option (with Antithetic Variates for variance reduction).
* **Path-Dependent Monte Carlo:** Asian Call Option (Arithmetic mean over 252 days).
* **Barrier Monte Carlo:** Up-and-Out Option with conditional deactivation optimization (early-exit) to save CPU cycles.

## Performance Benchmark
A cross-language C++ vs Python script is included to measure execution time on exotic products (requiring up to 252 million iterations). On a 1M-path Asian option (252 steps), the C++ Release build runs in ~8.9s against an estimated ~107s for pure Python — a **~12x speedup** — validating the architectural choice for this type of stochastic load. See `Benchmark.md` for full results.

## Build and Execution
The project uses CMake for the build process.

