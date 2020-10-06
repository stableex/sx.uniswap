#define CATCH_CONFIG_MAIN

#include "catch.hpp"

uint64_t get_amount_out( const uint64_t amount_in, const uint64_t reserve_in, const uint64_t reserve_out, const uint8_t fee = 30 )
{
    const uint64_t amount_in_with_fee = amount_in * (10000 - fee);
    const uint64_t numerator = amount_in_with_fee * reserve_out;
    const uint64_t denominator = reserve_in * 10000 + amount_in_with_fee;
    const uint64_t amount_out = numerator / denominator;

    return amount_out;
}

uint64_t get_amount_in( const uint64_t amount_out, const uint64_t reserve_in, const uint64_t reserve_out, const uint8_t fee = 30 )
{
    const uint64_t numerator = reserve_in * amount_out * 10000;
    const uint64_t denominator = (reserve_out - amount_out) * (10000 - fee);
    const uint64_t amount_in = numerator / denominator;

    return amount_in;
}

uint64_t quote( const uint64_t amount_a, const uint64_t reserve_a, const uint64_t reserve_b )
{
    const uint64_t amount_b = amount_a * reserve_b / reserve_a;
    return amount_b;
}

TEST_CASE( "get_amount_out (pass)" ) {
    // Inputs
    const uint64_t amount_in = 10000;
    const uint64_t reserve_in = 100000000;
    const uint64_t reserve_out = 400000000;

    // Calculation
    const uint64_t amountOut = get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 39876 );
}

TEST_CASE( "get_amount_in (pass)" ) {
    // Inputs
    const uint64_t amount_out = 39876;
    const uint64_t reserve_in = 100000000;
    const uint64_t reserve_out = 400000000;

    // Calculation
    const uint64_t amountIn = get_amount_in( amount_out, reserve_in, reserve_out );

    REQUIRE( amountIn == 9999 );
}

TEST_CASE( "quote (pass)" ) {
    // Inputs
    const uint64_t amount_a = 10000;
    const uint64_t reserve_a = 100000000;
    const uint64_t reserve_b = 400000000;

    // Calculation
    const uint64_t amount_b = quote( amount_a, reserve_a, reserve_b );

    REQUIRE( amount_b == 40000 );
}