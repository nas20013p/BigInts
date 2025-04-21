#include "fraction.h"
#include "fraction.cpp" 
#include "bigint.h"

#include <iostream>
#include <limits>
#include <chrono>

using namespace std;
using BigInt   = bigint;
using Fraction = pair<BigInt,BigInt>;

// timing helper
template<typename F>
long long timeMany(F fn, int iters = 100000) {
    auto start = chrono::high_resolution_clock::now();
    for(int i = 0; i < iters; ++i) fn();
    auto end   = chrono::high_resolution_clock::now();
    return chrono::duration_cast<chrono::microseconds>(end - start).count();
}

void demoOverflow() {
    int big = 50000;
    cout << "[OVERFLOW] 50000*50000 as int = "
         << (big * big)
         << " (expected 2500000000, max int="
         << numeric_limits<int>::max() << ")\n";
}

int main() {
    demoOverflow();

    Fraction bf1{ BigInt("12345678901234567890"), BigInt("9876543210987654321") };
    Fraction bf2{ BigInt("11111111111111111111"), BigInt("2222222222222222222") };

    int  i1 = 1234567890,     i2 = 987654321;
    long l1 = 12345678901234L, l2 = 9876543210987L;

    auto t_int_add  = timeMany([&]{ volatile int  x = i1 + i2; });
    auto t_long_add = timeMany([&]{ volatile long x = l1 + l2; });
    auto t_big_add  = timeMany([&]{ volatile Fraction f = addFrac(bf1,bf2); });

    cout << "\nTiming (100 k iters):\n"
         << " int add:    " << t_int_add  << " µs\n"
         << " long add:   " << t_long_add << " µs\n"
         << " BigInt add: " << t_big_add  << " µs\n";

    auto t_int_mul  = timeMany([&]{ volatile int  x = i1 * i2; });
    auto t_long_mul = timeMany([&]{ volatile long x = l1 * l2; });
    auto t_big_mul  = timeMany([&]{ volatile Fraction f = multiplyFrac(bf1,bf2); });

    cout << " int mul:    " << t_int_mul  << " µs\n"
         << " long mul:   " << t_long_mul << " µs\n"
         << " BigInt mul: " << t_big_mul  << " µs\n";

    return 0;
}



