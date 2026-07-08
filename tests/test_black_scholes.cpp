// Tests for the Black-Scholes engine.
// Planned cases:
//   - Known textbook values (e.g. Hull examples) to ~1e-4
//   - Put-call parity: C - P == S*exp(-qT) - K*exp(-rT)
//   - Edge cases: T -> 0 (converges to intrinsic value), sigma -> 0, deep ITM/OTM
//   - Implied vol round-trip: iv(price(sigma)) == sigma
// Scaffolding only — implementation pending.
