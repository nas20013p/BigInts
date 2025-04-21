#pragma once
#include "bigint.h"
#include <utility>

using BigInt   = bigint;
using Fraction = std::pair<BigInt,BigInt>;

// Operations on fractions of BigInts
Fraction addFrac(Fraction x, Fraction y);
Fraction multiplyFrac(Fraction x, Fraction y);
Fraction normalize(Fraction f);




