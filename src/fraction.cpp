#include "fraction.h"

// (a/b) * (c/d) = (a*c) / (b*d)
Fraction multiplyFrac(const Fraction& x, const Fraction& y) {
    return { x.first  * y.first,
             x.second * y.second };
}

// (a/b) + (c/d) = (a*d + b*c) / (b*d)
Fraction addFrac(const Fraction& x, const Fraction& y) {
    BigInt num = x.first  * y.second
               + y.first  * x.second;
    BigInt den = x.second * y.second;
    return { num, den };
}

// Reduce a fraction by dividing both parts by their GCD
Fraction normalize(const Fraction& f) {
    // big_gcd is the macro for bigint::_big_gcd
    BigInt g = big_gcd(const_cast<BigInt&>(f.first),
                       const_cast<BigInt&>(f.second));
    return { f.first / g,
             f.second / g };
}
