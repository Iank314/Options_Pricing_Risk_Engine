#pragma once
// ============================================================================
// opre/pricing/pricing_engine.hpp — Common pricing interface
// ============================================================================
// Planned contents:
//   - Abstract PricingEngine interface:
//       double price(const Option&, const MarketData&) const
//   - Shared result type (price + optional diagnostics such as std error)
//
// Black-Scholes, binomial tree, and Monte Carlo all implement this
// interface so they can be swapped and cross-validated against each
// other in tests. Scaffolding only.
// ============================================================================
