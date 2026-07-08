# Options_Pricing_Risk_Engine
Repository meant for building an engine that supports numerous quant/mathematical principles such as Monte Carlo pricing, Black-Scholes pricing, etc

Written in C++ (C++20, CMake). Currently scaffolding only — every file
contains a description of what will live there; implementation comes next.

## Project structure

```
include/opre/          Public headers (library API)
  core/                Option contracts, payoffs, market data, portfolio
  math/                Normal distribution, RNG, statistics helpers
  pricing/             Pricing engines behind one shared interface:
                       Black-Scholes, binomial tree (CRR), Monte Carlo
  greeks/              Analytic + finite-difference sensitivities
  risk/                VaR, Expected Shortfall, scenario stress tests
src/                   Implementations (mirrors include/opre/)
apps/                  CLI entry point (price + risk report demo)
tests/                 Unit tests, one file per module
docs/                  ARCHITECTURE.md — design and implementation order
CMakeLists.txt         Top-level build script
```

See [docs/ARCHITECTURE.md](docs/ARCHITECTURE.md) for the layering and the
suggested order to implement the modules in.
