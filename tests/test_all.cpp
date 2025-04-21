
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "fraction.h"
#include "../src/fraction.cpp"
#include <limits>

//Addition
TEST_CASE("addFrac: 1/2 + 1/3 == 5/6") {
    Fraction a{ BigInt("1"), BigInt("2") };
    Fraction b{ BigInt("1"), BigInt("3") };
    auto r = normalize(addFrac(a,b));
    CHECK(r.first  == BigInt("5"));
    CHECK(r.second == BigInt("6"));
}

//Multiplication
TEST_CASE("multiplyFrac: 1/2 * 1/3 == 1/6") {
    Fraction a{ BigInt("1"), BigInt("2") };
    Fraction b{ BigInt("1"), BigInt("3") };
    auto r = normalize(multiplyFrac(a,b));
    CHECK(r.first  == BigInt("1"));
    CHECK(r.second == BigInt("6"));
}

//Overflow
TEST_CASE("50000*50000 overflows int") {
    int big = 50000;
    int prod = big * big;
    CHECK(prod < 0);
    CHECK(prod == static_cast<int>(2500000000u));
}

//Normalize a non‑reduced fraction
TEST_CASE("normalize: 4/6 == 2/3") {
    Fraction r = normalize({ BigInt("4"), BigInt("6") });
    CHECK(r.first  == BigInt("2"));
    CHECK(r.second == BigInt("3"));
}

//Commutativity of addition
TEST_CASE("addFrac is commutative") {
    Fraction x{ BigInt("2"), BigInt("7") };
    Fraction y{ BigInt("3"), BigInt("5") };
    auto r1 = normalize(addFrac(x, y));
    auto r2 = normalize(addFrac(y, x));
    CHECK(r1.first  == r2.first);
    CHECK(r1.second == r2.second);
}











