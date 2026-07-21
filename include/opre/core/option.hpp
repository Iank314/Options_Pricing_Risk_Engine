#pragma once
// ============================================================================
// opre/core/option.hpp — Option contract definitions
// ============================================================================
// The core contract object consumed by every pricing model. Pure data plus
// validation — no pricing logic belongs here.
// ============================================================================

#include <stdexcept>

namespace opre {

enum class OptionType { Call, Put };
enum class ExerciseStyle { European, American };

class Option {
public:
    Option(OptionType type, ExerciseStyle style, double strike, double expiry_years)
        : type_(type), style_(style), strike_(strike), expiry_(expiry_years) {
        if (strike_ <= 0.0) {
            throw std::invalid_argument("Option: strike must be positive");
        }
        if (expiry_ < 0.0) {
            throw std::invalid_argument("Option: expiry must be non-negative");
        }
    }

    OptionType type() const { return type_; }
    ExerciseStyle style() const { return style_; }
    double strike() const { return strike_; }
    double expiry() const { return expiry_; }  // years

private:
    OptionType type_;
    ExerciseStyle style_;
    double strike_;
    double expiry_;
};

}  // namespace opre
