# Pricing Engine 

## Overview

A C++ options pricing engine implementing closed-form and Monte Carlo methods, with variance reduction techniques and an implied volatility solver. Benchmarked against a pure Python implementation.

**Stack:** C++20 · CMake · Python 3

---

## 1. Implemented Models

### 1.1 Black-Scholes (Closed-Form)
Prices a European call and computes all first-order Greeks analytically.

| Output | Formula |
|--------|---------|
| Price  | `S·N(d1) - K·e^{-rT}·N(d2)` |
| Delta  | `N(d1)` |
| Gamma  | `N'(d1) / (S·σ·√T)` |
| Vega   | `S·N'(d1)·√T` |
| Theta  | `-(S·N'(d1)·σ) / (2√T) - r·K·e^{-rT}·N(d2)` |
| Rho    | `K·T·e^{-rT}·N(d2)` |

### 1.2 Monte Carlo — European Call
Standard Monte Carlo with **antithetic variates**: each simulation generates a paired path `(Z, -Z)`, halving variance for a given path count. Both vanilla and antithetic standard errors are reported.

### 1.3 Monte Carlo — Asian Call (Arithmetic)
Path-dependent pricing over 252 daily steps. Implements **control variate** using the European call payoff on the same simulated path, with `E[X]` = Black-Scholes closed-form price.

### 1.4 Monte Carlo — Up-and-Out Barrier Call
Discrete barrier monitoring with **early-exit optimization**: the inner loop terminates immediately upon barrier breach, avoiding unnecessary computation for knocked-out paths.

---

## 2. Variance Reduction Results (Asian Call, 1M paths)

| Estimator          | Standard Error | Variance Ratio | Equivalent Paths |
|--------------------|----------------|----------------|------------------|
| Vanilla MC         | 0.00800        | 1.00           | 1,000,000        |
| Control Variate MC | 0.00456        | 0.32           | ~330,000         |

*Implied correlation between Asian and European payoffs: ρ ≈ 0.82. β* estimated empirically via `Cov(Y,X) / Var(X)`. Standard error reduced by 43% — equivalent to a 3x reduction in required paths.*

---

## 3. Implied Volatility Solver

Given an observed market price, recovers the implied volatility σ such that `BS(σ) = market_price`.

Two algorithms implemented and benchmarked:

| Algorithm | Method | Convergence |
|-----------|--------|-------------|
| **Bisection** | Binary search on `[0.001, 5.0]` | Linear (~50 iterations) |
| **Newton-Raphson** | `σ_new = σ_old - f(σ) / vega(σ)` | Quadratic (~5 iterations) |

*Both solvers use `ε = 1e-8` as convergence threshold. Newton-Raphson leverages the analytically computed Vega as the derivative, achieving significantly faster convergence from σ₀ = 0.2.*

---

## 4. Performance Benchmarks (C++ Release vs Python)

*Test conditions: 1,000,000 paths, 252 time steps. C++ compiled in Release mode.*

| Product           | CPU Iterations       | C++ Time   | Python Time     | Factor   |
|-------------------|----------------------|------------|-----------------|----------|
| European Call     | 1 Million            | ~0.040 sec | ~0.51 sec       | **~10x** |
| Asian Call        | 252 Million          | ~8.58 sec  | ~107 sec (est.) | **~12x** |
| Up-and-Out Barrier| Dynamic (Early-Exit) | ~7.16 sec  | —               | —        |

*Python Asian time extrapolated from a 5,000-path sample.*

---

## 5. Architectural Decisions

**State isolation:** `Current_S` is declared as a local variable inside the simulation loop, guaranteeing strict path independence and preventing cumulative drift across iterations.

**Early-exit on barrier breach:** The inner time-step loop terminates immediately when the barrier is hit. This avoids computing the remaining steps of an already knocked-out path, significantly reducing average iteration count.

**Single `calculate_bs` call per Newton iteration:** The `BSResult` struct is computed once per iteration and both `.price` and `.vega` are read from the same object, avoiding redundant evaluations.

**Empirical β* estimation:** The control variate coefficient is estimated from the simulation itself via `Cov(Y,X) / Var(X)`, requiring no prior knowledge of the correlation structure.

---


