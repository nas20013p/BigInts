#include "fraction_ops.h" // Include fraction operations
#include <iostream>
#include <vector>
#include <chrono>    // For timing
#include <iomanip>   // For std::setw, std::left
#include <limits>    // For std::numeric_limits
#include <string>    // For std::to_string with bigint
#include <stdexcept> // For exception handling (optional in time_operation)
#include <type_traits> // <<< Added for std::is_same_v >>>

// Function to perform and time operations
template <typename T_Frac, typename Func>
long long time_operation(Func operation, const T_Frac& a, const T_Frac& b, int iterations = 1000) {
    // Prevent division by zero in denominators before starting
     bool is_bigint_type = std::is_same_v<T_Frac, BigFraction>;
     bool den_a_zero = false;
     bool den_b_zero = false;

     if constexpr (is_bigint_type) {
         den_a_zero = (a.second == bigint("0"));
         den_b_zero = (b.second == bigint("0"));
     } else {
         den_a_zero = (a.second == 0);
         den_b_zero = (b.second == 0);
     }

     if (den_a_zero || den_b_zero) {
        std::cerr << "Error: Division by zero in input fraction for timing." << std::endl;
        return -1; // Indicate error
     }


    volatile T_Frac warmup_res;
     try {
          warmup_res = operation(a, b);
     } catch (const std::exception& e) {
          std::cerr << "\nWarning: Exception during timing warmup: " << e.what() << std::endl;
          // Depending on the exception, you might want to return an error code
          // For overflow in int/long, it might proceed but give weird results.
          // For bigint errors (like bad string conversion), it's more serious.
          return -3; // Indicate generic warmup error
     } catch (...) {
          std::cerr << "\nWarning: Unknown exception during timing warmup." << std::endl;
          return -4; // Indicate unknown warmup error
     }
    (void)warmup_res; // Avoid unused variable warning

    auto start = std::chrono::high_resolution_clock::now();
    try {
        for (int i = 0; i < iterations; ++i) {
            // Rerun denominator check inside loop in case operation modifies inputs (though current signature is const&)
             if constexpr (is_bigint_type) {
                 // bigint library might throw if denominator becomes zero during operations
                 // or handle it internally. Assuming internal check or prior validation.
             } else {
                 // For int/long, division by zero is undefined behavior *before* it happens.
                 // If the operation *results* in a zero denominator, that's usually okay
                 // until the next operation uses it. We primarily check inputs.
             }
            volatile T_Frac result = operation(a, b); // Use volatile to prevent optimization
            (void)result; // Avoid unused variable warning
        }
    } catch (const std::exception& e) {
         // Note: Standard integer overflow doesn't throw std::overflow_error by default.
         // This mainly catches potential errors from the bigint library or custom checks.
         std::cerr << "\nWarning: Exception during timing loop: " << e.what() << std::endl;
         return -3; // Indicate generic error during timing
    } catch (...) {
         std::cerr << "\nWarning: Unknown exception during timing loop." << std::endl;
         return -4; // Indicate unknown error
    }
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    if (iterations <= 0) return 0; // Avoid division by zero
    return duration.count() / iterations; // Average time per operation
}


void run_timing_comparison() {
    std::cout << "\n--- Timing Comparison (microseconds per operation) ---" << std::endl;
    std::cout << std::left << std::setw(15) << "Operation"
              << std::setw(15) << "int"
              << std::setw(15) << "long int"
              << std::setw(15) << "bigint" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    // Example set 1: Small numbers
    IntFraction i_a_small = {2, 3};
    IntFraction i_b_small = {2, 5};
    // Use L suffix for long int literals
    LongFraction l_a_small = {2L, 3L};
    LongFraction l_b_small = {2L, 5L};
    BigFraction b_a_small = {bigint("2"), bigint("3")};
    BigFraction b_b_small = {bigint("2"), bigint("5")};

    // Example set 2: Larger numbers
    long int large_val1 = 1000000000L; // 1 billion (L suffix for long)
    long int large_val2 = 2000000000L; // 2 billion (L suffix for long)
    long int large_val3 = 3L;          // Use L suffix for long int literals
    long int large_val4 = 7L;          // Use L suffix for long int literals

    // Use smaller ints to reduce likelihood of *setup* overflow, focus on operation overflow/timing
    IntFraction i_a_large = {int(large_val1 % 100000), int(large_val3)};
    IntFraction i_b_large = {int(large_val2 % 100000), int(large_val4)};
    LongFraction l_a_large = {large_val1, large_val3};
    LongFraction l_b_large = {large_val2, large_val4};
    BigFraction b_a_large = {bigint(std::to_string(large_val1)), bigint(std::to_string(large_val3))};
    BigFraction b_b_large = {bigint(std::to_string(large_val2)), bigint(std::to_string(large_val4))};


    int iterations_fast = 5000; // More iterations for faster ops
    int iterations_slow = 100;  // Fewer iterations for slower ops

    auto print_row = [&](const std::string& op_name, long long t_int, long long t_long, long long t_big) {
        auto format_time = [](long long t) -> std::string {
            if (t < 0) return "Err/Ovflw"; // Simplified error reporting
            return std::to_string(t);
        };
        std::cout << std::left << std::setw(15) << op_name
                  << std::setw(15) << format_time(t_int)
                  << std::setw(15) << format_time(t_long)
                  << std::setw(15) << format_time(t_big) << std::endl;
    };

    // Time Sum (Small)
    long long time_sum_int_s = time_operation(sum_int, i_a_small, i_b_small, iterations_fast);
    long long time_sum_long_s = time_operation(sum_long, l_a_small, l_b_small, iterations_fast);
    long long time_sum_big_s = time_operation(sum_bigint, b_a_small, b_b_small, iterations_slow);
    print_row("Sum (Small)", time_sum_int_s, time_sum_long_s, time_sum_big_s);

    // Time Product (Small)
    long long time_prod_int_s = time_operation(product_int, i_a_small, i_b_small, iterations_fast);
    long long time_prod_long_s = time_operation(product_long, l_a_small, l_b_small, iterations_fast);
    long long time_prod_big_s = time_operation(product_bigint, b_a_small, b_b_small, iterations_slow);
    print_row("Product (Small)", time_prod_int_s, time_prod_long_s, time_prod_big_s);

    // Time Sum (Large)
    long long time_sum_int_l = time_operation(sum_int, i_a_large, i_b_large, iterations_fast);
    long long time_sum_long_l = time_operation(sum_long, l_a_large, l_b_large, iterations_slow);
    long long time_sum_big_l = time_operation(sum_bigint, b_a_large, b_b_large, iterations_slow / 10 > 0 ? iterations_slow/10 : 1);
    print_row("Sum (Large)", time_sum_int_l, time_sum_long_l, time_sum_big_l);

    // Time Product (Large)
    long long time_prod_int_l = time_operation(product_int, i_a_large, i_b_large, iterations_fast);
    long long time_prod_long_l = time_operation(product_long, l_a_large, l_b_large, iterations_slow);
    long long time_prod_big_l = time_operation(product_bigint, b_a_large, b_b_large, iterations_slow / 10 > 0 ? iterations_slow/10 : 1);
    print_row("Product (Large)", time_prod_int_l, time_prod_long_l, time_prod_big_l);


    std::cout << std::string(60, '-') << std::endl;
    std::cout << "(Note: Timings are approximate averages in microseconds.)" << std::endl;
    std::cout << "(Note: 'int'/'long' timings might show 'Err/Ovflw' if overflow occurred or other error.)" << std::endl;
}


void demonstrate_int_failure() {
    std::cout << "\n--- Demonstrating 'int' Failure (Overflow) ---" << std::endl;

    // Use values close to MAX_INT that will cause overflow on multiplication/addition
    int val1 = std::numeric_limits<int>::max() / 2; // Approx MAX/2
    int val2 = 3; // A small multiplier/denominator, ensure non-zero
    int val3 = 5; // Ensure non-zero

    if (val2 == 0 || val3 == 0) { // Basic check, should not happen here
        std::cerr << "Error: Denominator is zero in failure demo setup." << std::endl;
        return;
    }

    IntFraction f1 = {val1, val2}; // (MAX/2) / 3
    IntFraction f2 = {val1, val3}; // (MAX/2) / 5

    // Expected Sum (using bigint for correctness):
    BigFraction b_f1_sum = {bigint(std::to_string(val1)), bigint(std::to_string(val2))};
    BigFraction b_f2_sum = {bigint(std::to_string(val1)), bigint(std::to_string(val3))};
    BigFraction big_sum = sum_bigint(b_f1_sum, b_f2_sum);

    // Expected Product (using bigint):
    BigFraction b_f1_prod = {bigint(std::to_string(val1)), bigint(std::to_string(val2))};
    BigFraction b_f2_prod = {bigint(std::to_string(val1)), bigint(std::to_string(val3))};
    BigFraction big_prod = product_bigint(b_f1_prod, b_f2_prod);


    std::cout << "Using IntFractions that should cause overflow:" << std::endl;
    std::cout << "  f1 = " << f1 << std::endl;
    std::cout << "  f2 = " << f2 << std::endl;

    // Calculate using int (potential overflow)
    // Using try-catch is not standard C++ for integer overflow,
    // behaviour is undefined. We just show the potentially wrong result.
    IntFraction int_sum = sum_int(f1, f2);
    IntFraction int_prod = product_int(f1, f2);


    std::cout << "\nResults Comparison:" << std::endl;
    std::cout << "  Correct Sum (via bigint):     " << big_sum << std::endl;
    std::cout << "  Calculated Sum (int):         " << int_sum << "  <-- Likely incorrect due to overflow" << std::endl;

    std::cout << "  Correct Product (via bigint): " << big_prod << std::endl;
    std::cout << "  Calculated Product (int):     " << int_prod << " <-- Likely incorrect due to overflow" << std::endl;
    std::cout << "----------------------------------------------" << std::endl;
}


int main() {
    // Run the demonstration of integer overflow
    demonstrate_int_failure();

    // Run the timing comparisons
    run_timing_comparison();

    std::cout << "\nLab timing/demo execution finished." << std::endl;

    return 0;
}