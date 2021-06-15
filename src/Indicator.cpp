#include "CadencedIndicator.h"

Indicator::Indicator(const int &pin, const CadencePattern &pattern) : pin(pin), pattern(pattern)
{
}

void Indicator::setPattern(const CadencePattern &pattern)
{
    this->pattern = pattern;
}
