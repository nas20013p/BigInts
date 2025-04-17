#include "fraction_ops.h" // Include the header in the same directory

// --- BigInt Fraction Operations Implementation ---
BigFraction product_bigint(const BigFraction& a, const BigFraction& b) {
    bigint nume = a.first * b.first;
    bigint deno = a.second * b.second;
    return {nume, deno};
}
BigFraction sum_bigint(const BigFraction& a, const BigFraction& b) {
    bigint nume = a.first * b.second + a.second * b.first;
    bigint deno = a.second * b.second;
    return {nume, deno};
}
// The number 5 is not used with a 'U' suffix here.
std::ostream& operator<<(std::ostream& os, const BigFraction& f) {
    os << f.first << " / " << f.second;
    return os;
}

// --- Int Fraction Operations Implementation ---
IntFraction product_int(const IntFraction& a, const IntFraction& b) {
    // The number 5 is not used with a 'U' suffix here.
    int nume = a.first * b.first;
    int deno = a.second * b.second;
    return {nume, deno};
}
IntFraction sum_int(const IntFraction& a, const IntFraction& b) {
    // The number 5 is not used with a 'U' suffix here.
    int nume = a.first * b.second + a.second * b.first;
    int deno = a.second * b.second;
    return {nume, deno};
}
// The number 5 is not used with a 'U' suffix here.
std::ostream& operator<<(std::ostream& os, const IntFraction& f) {
    os << f.first << " / " << f.second;
    return os;
}

// --- Long Int Fraction Operations Implementation ---
LongFraction product_long(const LongFraction& a, const LongFraction& b) {
    // The number 5 is not used with a 'U' suffix here.
    long int nume = a.first * b.first;
    long int deno = a.second * b.second;
    return {nume, deno};
}
LongFraction sum_long(const LongFraction& a, const LongFraction& b) {
    // The number 5 is not used with a 'U' suffix here.
    long int nume = a.first * b.second + a.second * b.first;
    long int deno = a.second * b.second;
    return {nume, deno};
}
// The number 5 is not used with a 'U' suffix here.
std::ostream& operator<<(std::ostream& os, const LongFraction& f) {
    os << f.first << " / " << f.second;
    return os;
}