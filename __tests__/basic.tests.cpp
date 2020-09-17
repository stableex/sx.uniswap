#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "check.hpp"
#include "../uniswap.hpp"

TEST_CASE( "getAmountOut (pass)" ) {
    // Inputs
    const uint64_t amountIn = 10000;
    const uint64_t reserveIn = 45851931234;
    const uint64_t reserveOut = 125682033533;

    // Calculation
    const uint64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );

    REQUIRE( amountOut == 27328 );
}

TEST_CASE( "getAmountIn (pass)" ) {
    // Inputs
    const uint64_t amountOut = 27328;
    const uint64_t reserveIn = 45851931234;
    const uint64_t reserveOut = 125682033533;

    // Calculation
    const uint64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );

    REQUIRE( amountIn == 10000 );
}
