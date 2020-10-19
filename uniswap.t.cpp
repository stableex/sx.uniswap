#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <eosio/check.hpp>
#include <uint128_t/uint128_t.cpp>

#include "uniswap.hpp"

TEST_CASE( "get_amount_out (pass)" ) {
    // Inputs
    const uint64_t amount_in = 10000;
    const uint64_t reserve_in = 100000000;
    const uint64_t reserve_out = 400000000;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 39876 );
}

TEST_CASE( "get_amount_in (pass)" ) {
    // Inputs
    const uint64_t amount_out = 39876;
    const uint64_t reserve_in = 100000000;
    const uint64_t reserve_out = 400000000;

    // Calculation
    const uint64_t amountIn = uniswap::get_amount_in( amount_out, reserve_in, reserve_out );

    REQUIRE( amountIn == 10000 );
}

TEST_CASE( "quote (pass)" ) {
    // Inputs
    const uint64_t amount_a = 10000;
    const uint64_t reserve_a = 100000000;
    const uint64_t reserve_b = 400000000;

    // Calculation
    const uint64_t amount_b = uniswap::quote( amount_a, reserve_a, reserve_b );

    REQUIRE( amount_b == 40000 );
}