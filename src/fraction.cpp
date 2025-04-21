#include "fraction.h"

// (a/b) * (c/d) = (a*c)/(b*d)
Fraction multiplyFrac(Fraction x, Fraction y) {
    return { x.first  * y.first,
             x.second * y.second };
}

// (a/b) + (c/d) = (a*d + b*c)/(b*d)
Fraction addFrac(Fraction x, Fraction y) {
    BigInt num = x.first * y.second
               + y.first * x.second;
    BigInt den = x.second * y.second;
    return { num, den };
}

// Reduce by GCD
Fraction normalize(Fraction f) {
    BigInt g = big_gcd(f.first, f.second);
    return { f.first / g,
             f.second / g };
}

