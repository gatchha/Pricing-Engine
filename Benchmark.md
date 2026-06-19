## 1. Latency Benchmarks (C++ Release vs Python)
*Test conditions: 1,000,000 paths, 252 time steps (for path-dependent products). C++ compiled with `-O2` (Release).*

| Product            | CPU Iterations       | C++ Time   | Python Time       | Factor    |
|--------------------|----------------------|------------|-------------------|-----------|
| **European Call**  | 1 Million            | ~0.051 sec | ~0.51 sec         | **~10x**  |
| **Asian Call**     | 252 Million          | ~8.86 sec  | ~107 sec (est.)   | **~12x**  |
| **Up-Out Barrier** | Dynamic (Early-Exit) | ~7.16 sec  | —                 | —         |

*Python Asian time extrapolated from 5,000-path sample. A pure Python loop at 252M iterations is impractical at scale, confirming the rationale for the C++ implementation.*

## 2. Critical Architectural Decisions

* **State Memory Isolation:** Instantiation of a local price variable copy inside the main stochastic loop to prevent cumulative mutation and guarantee strict statistical independence of the Monte Carlo paths.
* **CPU Optimization (Early-Exit):** Insertion of a premature loop termination instruction as soon as the barrier is breached (Knock-out). This prevents the processor from calculating remaining time steps for an already deactivated contract, drastically reducing computation time.
* **Path-Dependent Resolution:** Although the final payoff of a barrier option is European in nature, evaluating the deactivation risk requires step-by-step discretization (252 days) to avoid invisible barrier breaches occurring between the start and end of the contract.
* **Variance Reduction (Antithetic Variates):** Each European Call simulation generates a paired path `(Z, -Z)`, halving the number of required paths for a given standard error target. Both the vanilla and antithetic standard errors are reported in `MCResult` for direct comparison.
