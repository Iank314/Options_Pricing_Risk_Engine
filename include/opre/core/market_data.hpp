#pragma once
// ============================================================================
// opre/core/market_data.hpp — Market inputs for pricing
// ============================================================================
// Planned contents:
//   - struct MarketData: spot price, risk-free rate, dividend yield,
//     volatility (flat vol to start; term structure / surface later)
//   - Validation helpers (non-negative vol, sane rates)
//
// Every pricing engine takes (Option, MarketData) so models stay
// interchangeable. Scaffolding only.
// ============================================================================
