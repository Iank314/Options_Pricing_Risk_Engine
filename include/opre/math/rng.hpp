#pragma once
// ============================================================================
// opre/math/rng.hpp — Random number generation
// ============================================================================
// Planned contents:
//   - Wrapper around std::mt19937_64 with seeding control (reproducibility)
//   - Standard normal draws (std::normal_distribution or Box-Muller)
//   - Room to grow: antithetic variates, Sobol/quasi-random sequences
//
// Used by the Monte Carlo pricer and historical/MC VaR. Scaffolding only.
// ============================================================================
