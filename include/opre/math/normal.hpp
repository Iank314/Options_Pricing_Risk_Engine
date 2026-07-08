#pragma once
// ============================================================================
// opre/math/normal.hpp — Normal distribution utilities
// ============================================================================
// Planned contents:
//   - Standard normal PDF phi(x)
//   - Standard normal CDF N(x)  (via std::erfc or Hart/Acklam approximation)
//   - Inverse CDF (quantile) for VaR and quasi-random sampling
//
// These are the workhorses behind Black-Scholes d1/d2 terms and
// parametric VaR. Scaffolding only.
// ============================================================================
