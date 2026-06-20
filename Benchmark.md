## 1. Latency Benchmarks (C++ Release vs Python)
*Test conditions: 1,000,000 paths, 252 time steps (for path-dependent products). C++ compiled with `-O2` (Release).*

| Product            | CPU Iterations       | C++ Time   | Python Time       | Factor    |
|--------------------|----------------------|------------|-------------------|-----------|
| **European Call**  | 1 Million            | ~0.040 sec | ~0.51 sec         | **~10x**  |
| **Asian Call**     | 252 Million          | ~8.58 sec  | ~107 sec (est.)   | **~12x**  |
| **Up-Out Barrier** | Dynamic (Early-Exit) | ~7.16 sec  | —                 | —         |

*Python Asian time extrapolated from 5,000-path sample. A pure Python loop at 252M iterations is impractical at scale, confirming the rationale for the C++ implementation.*

## 2. Variance Reduction — Control Variate (Asian Call, 1M paths)

| Estimator              | Standard Error | Variance Ratio | Equivalent Paths (same precision) |
|------------------------|----------------|----------------|-----------------------------------|
| **Vanilla MC**         | 0.00800        | 1.00           | 1,000,000                         |
| **Control Variate MC** | 0.00456        | 0.32           | ~330,000                          |

*Control variate: European call payoff on the same simulated path, with E[X] = Black-Scholes closed-form price.*
*Implied correlation between Asian and European payoffs: ρ ≈ 0.82. β* estimated empirically from the simulation.*

## 3. Critical Architectural Decisions

* **State Memory Isolation:** Instantiation of a local price variable copy inside the main stochastic loop to prevent cumulative mutation and guarantee strict statistical independence of the Monte Carlo paths.
* **CPU Optimization (Early-Exit):** Insertion of a premature loop termination instruction as soon as the barrier is breached (Knock-out). This prevents the processor from calculating remaining time steps for an already deactivated contract, drastically reducing computation time.
* **Path-Dependent Resolution:** Although the final payoff of a barrier option is European in nature, evaluating the deactivation risk requires step-by-step discretization (252 days) to avoid invisible barrier breaches occurring between the start and end of the contract.
* **Variance Reduction (Antithetic Variates):** Each European Call simulation generates a paired path `(Z, -Z)`, halving the number of required paths for a given standard error target. Both the vanilla and antithetic standard errors are reported for direct comparison.
* **Variance Reduction (Control Variate):** The Asian Call estimator is corrected using the European Call payoff on the same path as a control. The optimal β* is estimated empirically from the simulation via `Cov(Y,X) / Var(X)`, reducing standard error by 43% (equivalent to a 3x reduction in required paths).
