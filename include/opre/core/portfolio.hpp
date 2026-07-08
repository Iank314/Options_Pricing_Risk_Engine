#pragma once
// ============================================================================
// opre/core/portfolio.hpp — Position and portfolio aggregation
// ============================================================================
// Planned contents:
//   - struct Position: an Option plus a signed quantity (long/short)
//   - class Portfolio: collection of Positions
//   - Aggregate value / aggregate Greeks across positions
//
// The risk layer (VaR, stress tests) operates on a Portfolio rather than
// a single option. Scaffolding only.
// ============================================================================
