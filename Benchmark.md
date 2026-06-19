## 1. Latency Benchmarks (C++ vs Python)
*Test conditions: 1,000,000 paths, 252 time steps (for path-dependent products).*

| Product           | CPU Iterations | C++ Time | Python Time | Factor |
| **European Call** | 1 Million      | ~0.0x sec | ~x.xx sec | **x...** |
| **Asian Call**    | 252 Million       | ~x.xx sec | DNF / Timeout | **> x50** |
| **Up-Out Barrier** | Dynamic (Optimized) | ~0.xx sec | - | - |

## 2. Critical Architectural Decisions

* **State Memory Isolation:** Instantiation of a local price variable copy inside the main stochastic loop to prevent cumulative mutation and guarantee strict statistical independence of the Monte Carlo paths.
* **CPU Optimization (Early-Exit):** Insertion of a premature loop termination instruction as soon as the barrier is breached (Knock-out). This prevents the processor from calculating remaining time steps for an already deactivated contract, drastically reducing computation time.
* **Path-Dependent Resolution:** Although the final payoff of a barrier option is European in nature, evaluating the deactivation risk requires step-by-step discretization (252 days) to avoid invisible barrier breaches occurring between the start and end of the contract.
* **Safe Storage:** Use of standard dynamically sized containers (`std::vector`) for exporting empirical convergence data to demonstrate the Law of Large Numbers.