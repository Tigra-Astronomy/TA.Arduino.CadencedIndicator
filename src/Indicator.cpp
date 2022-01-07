#include "CadencedIndicator.h"

Indicator::Indicator(const CadencePattern &pattern, std::function<void(bool)> stateChanger)
    : pattern(pattern), invokeUserStateChange(stateChanger)
    {
    }

void Indicator::setPattern(const CadencePattern &pattern)
    {
    this->pattern = pattern;
    }
