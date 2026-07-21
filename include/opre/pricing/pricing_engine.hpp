#pragma once
// ============================================================================
// opre/pricing/pricing_engine.hpp — Common pricing interface
// ============================================================================
// Black-Scholes, binomial tree, and Monte Carlo all implement this
// interface so they can be swapped and cross-validated against each
// other in tests.
// ============================================================================

#include "opre/core/option.hpp"
#include "opre/core/market_data.hpp"

namespace opre::pricing {

class PricingEngine {
public:
    virtual ~PricingEngine() = default;
    virtual double price(const Option& option, const MarketData& market) const = 0;
};

}  // namespace opre::pricing
