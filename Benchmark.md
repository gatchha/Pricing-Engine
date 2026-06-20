## Latency Benchmarks (C++ Release vs Python)
*Test conditions: 1,000,000 paths, 252 time steps (for path-dependent products). C++ compiled with `-O2` (Release).*

| Product            | CPU Iterations       | C++ Time   | Python Time       | Factor    |
|--------------------|----------------------|------------|-------------------|-----------|
| **European Call**  | 1 Million            | ~0.040 sec | ~0.51 sec         | **~10x**  |
| **Asian Call**     | 252 Million          | ~8.58 sec  | ~107 sec (est.)   | **~12x**  |


*Python Asian time extrapolated from 5,000-path sample. A pure Python loop at 252M iterations is impractical at scale, confirming the rationale for the C++ implementation.*

