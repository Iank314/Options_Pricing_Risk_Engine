#pragma once
// ============================================================================
// opre/pricing/black_scholes.hpp — Black-Scholes-Merton analytic pricer
// ============================================================================
// This header is the *interface* for the analytic European-option pricer.
// The closed-form math (d1/d2, the price formula, the implied-vol solver)
// lives in src/pricing/black_scholes.cpp — declarations here, derivations
// there. That split is intentional: this file says WHAT each function must
// return; deriving HOW is the learning exercise.
//
// Conventions used throughout (assume these unless a doc comment says else):
//   S      spot price of the underlying            (> 0)
//   K      strike price                            (> 0)
//   r      risk-free rate, continuously compounded (annual, decimal: 5% = 0.05)
//   q      continuous dividend yield               (annual, decimal)
//   sigma  volatility of the underlying            (annualized, decimal, > 0)
//   T      time to expiry, in YEARS                (>= 0)
// ============================================================================

#include "opre/core/option.hpp"          // opre::Option, opre::OptionType
#include "opre/core/market_data.hpp"     // opre::MarketData
#include "opre/pricing/pricing_engine.hpp"  // opre::PricingEngine

namespace opre::pricing {

// ---------------------------------------------------------------------------
// Shared building blocks: d1 and d2
// ---------------------------------------------------------------------------
// d1 and d2 are the two standardized arguments that appear inside the normal
// CDF in every Black-Scholes result — price AND all the analytic Greeks. They
// are exposed here (rather than hidden in the .cpp) precisely so the greeks
// module can reuse them instead of recomputing.
//
// Precondition: sigma > 0 and T > 0. Behavior at the sigma*sqrt(T) -> 0 limit
// is handled by the pricing functions below, not here.
double d1(double S, double K, double r, double q, double sigma, double T);
double d2(double S, double K, double r, double q, double sigma, double T);

// ---------------------------------------------------------------------------
// Price (pure-function form)
// ---------------------------------------------------------------------------
// The primitive, textbook-notation entry point. Takes raw doubles so it maps
// one-to-one onto the math and is trivial to unit test against known values.
//
// Returns the present value of a European option with the given parameters.
// Must handle the degenerate edges gracefully:
//   - T == 0      -> intrinsic value (max(S-K,0) for a call, max(K-S,0) for a put)
//   - sigma == 0  -> deterministic discounted forward payoff
// Postcondition: price >= 0, and price >= intrinsic value.
double bs_price(OptionType type,
                double S, double K, double r, double q, double sigma, double T);

// ---------------------------------------------------------------------------
// Implied volatility
// ---------------------------------------------------------------------------
// The inverse problem: given an observed market price, find the sigma that
// makes bs_price() reproduce it. There is no closed form, so this is a
// root-finding routine (plan: Newton-Raphson using vega as the derivative,
// with a bisection fallback for robustness when vega is tiny).

// Tunables for the solver — defaulted so callers can ignore them.
struct ImpliedVolConfig {
    double tolerance     = 1e-8;   // stop when |bs_price - market| < tolerance
    int    max_iterations = 100;   // give up (and report failure) after this many
    double lower_bound   = 1e-6;   // vol search bracket, lower
    double upper_bound   = 5.0;    // vol search bracket, upper (500% vol)
};

// Result of an implied-vol solve. `converged` tells you whether to trust
// `volatility`; a price below intrinsic or above the underlying has no
// solution, so callers must check rather than assume.
struct ImpliedVolResult {
    double volatility = 0.0;
    bool   converged  = false;
    int    iterations = 0;
};

ImpliedVolResult implied_volatility(OptionType type, double market_price,
                                    double S, double K, double r, double q, double T,
                                    const ImpliedVolConfig& cfg = {});

// ---------------------------------------------------------------------------
// Engine form: adapts the pure functions to the shared PricingEngine interface
// ---------------------------------------------------------------------------
// Wraps bs_price() so Black-Scholes is interchangeable with the binomial and
// Monte Carlo engines and can be cross-validated against them in tests.
//
// Note: this engine is only valid for EUROPEAN options. price() should reject
// (or document its behavior on) American-exercise options, since the closed
// form does not apply to early exercise.
class BlackScholesEngine final : public PricingEngine {
public:
    double price(const Option& option, const MarketData& market) const override;
};

}  // namespace opre::pricing
 