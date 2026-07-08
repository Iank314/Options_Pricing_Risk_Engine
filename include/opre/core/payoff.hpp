#pragma once
// ============================================================================
// opre/core/payoff.hpp — Payoff functions
// ============================================================================
// Planned contents:
//   - Abstract Payoff interface: double operator()(double spot) const
//   - CallPayoff / PutPayoff (vanilla: max(S-K, 0), max(K-S, 0))
//   - Room to grow: digital/binary, straddle, spread payoffs
//
// Payoffs are kept separate from Option so exotic payoffs can be added
// without touching the pricing models. Scaffolding only.
// ============================================================================
