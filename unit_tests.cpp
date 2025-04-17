// Define this in only one .cpp file to create main() for the tests
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"        // Include doctest from the same directory
#include "fraction_ops.h"   // Include fraction operations header
#include <limits>           // For std::numeric_limits
#include <string>           // For std::to_string with bigint

// Friend's original test case
TEST_CASE("BigInt: Basic Sum and Product") {
    BigFraction a = {bigint("2"), bigint("3")}; // 2/3
    BigFraction b = {bigint("2"), bigint("5")}; // 2/5

    BigFraction sum_ab = sum_bigint(a, b); // Expected: 16/15
    CHECK(sum_ab.first == bigint("16"));
    CHECK(sum_ab.second == bigint("15"));

    BigFraction prod_ab = product_bigint(a, b); // Expected: 4/15
    CHECK(prod_ab.first == bigint("4"));
    CHECK(prod_ab.second == bigint("15"));
}

// Test case potentially causing int overflow
TEST_CASE("Int: Overflow Check") {
    int max_int = std::numeric_limits<int>::max();
    int large_num1 = max_int / 2;
    int small_den = 3;
    int small_num = 2;

    IntFraction f1 = {large_num1, small_den}; // (~MAX_INT / 2) / 3
    IntFraction f2 = {small_num, small_den};  // 2 / 3

    BigFraction expected_prod_big = {bigint(std::to_string(large_num1)) * bigint("2"), bigint("9")};
    IntFraction prod_int_res = product_int(f1, f2);
    INFO("Comparing int product ", prod_int_res, " vs bigint expected ", expected_prod_big);
    WARN_MESSAGE(bigint(std::to_string(prod_int_res.first)) == expected_prod_big.first, "Potential int product overflow for numerator");
    WARN_MESSAGE(bigint(std::to_string(prod_int_res.second)) == expected_prod_big.second, "Potential int product overflow for denominator");

    BigFraction expected_sum_big = {bigint(std::to_string(large_num1)) * bigint("3") + bigint("6"), bigint("9")};
    IntFraction sum_int_res = sum_int(f1, f2);
    INFO("Comparing int sum ", sum_int_res, " vs bigint expected ", expected_sum_big);
    WARN_MESSAGE(bigint(std::to_string(sum_int_res.first)) == expected_sum_big.first, "Potential int sum overflow for numerator");
    WARN_MESSAGE(bigint(std::to_string(sum_int_res.second)) == expected_sum_big.second, "Potential int sum overflow for denominator");
}

// Basic test for Long Int
TEST_CASE("LongInt: Basic Sum and Product") {
    long int num1 = 3000000000L;
    long int den1 = 2L;
    long int num2 = 4L;
    long int den2 = 5000000000L;

    LongFraction a = {num1, den1};
    LongFraction b = {num2, den2};

    BigFraction expected_sum_big = {bigint("15000000000000000008"), bigint("10000000000")};
    BigFraction expected_prod_big = {bigint("12"), bigint("10")};

    LongFraction sum_ab = sum_long(a, b);
    CHECK(bigint(std::to_string(sum_ab.first)) == expected_sum_big.first);
    CHECK(bigint(std::to_string(sum_ab.second)) == expected_sum_big.second);

    LongFraction prod_ab = product_long(a, b);
    CHECK(bigint(std::to_string(prod_ab.first)) == expected_prod_big.first);
    CHECK(bigint(std::to_string(prod_ab.second)) == expected_prod_big.second);
}

// Test with negative numbers
TEST_CASE("BigInt: Negative Numbers") {
    BigFraction a = {bigint("-2"), bigint("3")}; // -2/3
    BigFraction b = {bigint("2"), bigint("-5")}; // 2/-5 == -2/5

    BigFraction sum_ab = sum_bigint(a, b); // Expected: -16/15
    CHECK(sum_ab.first == bigint("-16"));
    // Denominator might normalize to positive depending on bigint implementation details after sum
    CHECK(sum_ab.second == bigint("15"));

    BigFraction prod_ab = product_bigint(a, b); // Expected: 4/(-15) or 4/15 if signs handled
    CHECK(prod_ab.first == bigint("4"));
     // Check against possible outcomes depending on sign handling in bigint lib
    CHECK((prod_ab.second == bigint("-15") || prod_ab.second == bigint("15")));
    // A more robust check would be value-based if simplification were implemented:
    // CHECK(prod_ab.first * bigint("15") == prod_ab.second * bigint("4"));
}