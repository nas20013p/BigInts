#ifndef FRACTION_OPS_H
#define FRACTION_OPS_H

#include "bigint.h" // bigint.h is in the same directory
#include <utility>   // For std::pair
#include <iostream>  // For std::ostream

// Type alias for BigInt fractions
using BigFraction = std::pair<bigint, bigint>;

// Type alias for standard int fractions
using IntFraction = std::pair<int, int>;

// Type alias for long int fractions
using LongFraction = std::pair<long int, long int>;

// --- BigInt Fraction Operations ---
BigFraction product_bigint(const BigFraction& a, const BigFraction& b);
BigFraction sum_bigint(const BigFraction& a, const BigFraction& b);

// Helper to print BigFraction
std::ostream& operator<<(std::ostream& os, const BigFraction& f);

// --- Int Fraction Operations ---
IntFraction product_int(const IntFraction& a, const IntFraction& b);
IntFraction sum_int(const IntFraction& a, const IntFraction& b);

// Helper to print IntFraction
std::ostream& operator<<(std::ostream& os, const IntFraction& f);


// --- Long Int Fraction Operations ---
LongFraction product_long(const LongFraction& a, const LongFraction& b);
LongFraction sum_long(const LongFraction& a, const LongFraction& b);

// Helper to print LongFraction
std::ostream& operator<<(std::ostream& os, const LongFraction& f);


#endif // FRACTION_OPS_H