# Architecture

Layered design — each layer depends only on the layers above it:

```
core (option, payoff, market data, portfolio)
  └── math (normal distribution, RNG, statistics)
        └── pricing (Black-Scholes, binomial tree, Monte Carlo — one shared interface)
              └── greeks (analytic + finite-difference sensitivities)
                    └── risk (VaR, Expected Shortfall, stress tests)
```

## Key decisions

- **One pricing interface** (`pricing_engine.hpp`): every model implements
  `price(Option, MarketData)`. Models stay interchangeable, and tests
  cross-validate them against each other (MC and tree vs. analytic BSM).
- **Payoffs separate from contracts**: exotic payoffs can be added without
  touching any pricing model.
- **Finite-difference Greeks work with any engine**, so even models without
  closed forms produce full sensitivities.
- **Risk operates on portfolios**, not single options — positions carry
  signed quantities so long/short books aggregate naturally.

## Suggested implementation order

1. `math/normal` → `pricing/black_scholes` (analytic benchmark first)
2. `greeks` (analytic, then finite-difference)
3. `math/rng` + `math/stats` → `pricing/monte_carlo` (validate vs. BSM)
4. `pricing/binomial_tree` (adds American exercise)
5. `core/portfolio` → `risk/var` → `risk/stress_test`
6. `apps/main.cpp` CLI tying it together
