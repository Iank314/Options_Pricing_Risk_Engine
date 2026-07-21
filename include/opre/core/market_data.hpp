#pragma once
// ============================================================================
// opre/core/market_data.hpp — Market inputs for pricing
// ============================================================================
// Every pricing engine takes (Option, MarketData) so models stay
// interchangeable. Flat volatility for now; a term structure or surface
// can replace `volatility` later without touching the Option side.
// ============================================================================

#include <stdexcept>

namespace opre {

struct MarketData {
    double spot;             // S: current price of the underlying, > 0
    double rate;              // r: continuously-compounded risk-free rate (annual, decimal)
    double dividend_yield;    // q: continuous dividend yield (annual, decimal)
    double volatility;        // sigma: annualized volatility (decimal), >= 0

    MarketData(double spot_, double rate_, double dividend_yield_, double volatility_)
        : spot(spot_), rate(rate_), dividend_yield(dividend_yield_), volatility(volatility_) {
        if (spot <= 0.0) {
            throw std::invalid_argument("MarketData: spot must be positive");
        }
        if (volatility < 0.0) {
            throw std::invalid_argument("MarketData: volatility must be non-negative");
        }
    }
};

}  // namespace opre
