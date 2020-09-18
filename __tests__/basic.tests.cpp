#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "check.hpp"
#include "../uniswap.hpp"

TEST_CASE( "quote (pass)" ) {
    // Inputs
    const int64_t amountA = 10000;
    const int64_t reserveA = 45851931234;
    const int64_t reserveB = 125682033533;

    // Calculation
    const int64_t amountB = uniswap::quote( amountA, reserveA, reserveB );

    REQUIRE( amountB == 27410 );
}

TEST_CASE( "getAmountOut (pass)" ) {
    // Inputs
    const int64_t amountIn = 10000;
    const int64_t reserveIn = 45851931234;
    const int64_t reserveOut = 125682033533;

    // Calculation
    const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );

    REQUIRE( amountOut == 27328 );
}

TEST_CASE( "getAmountIn (pass)" ) {
    // Inputs
    const int64_t amountOut = 27328;
    const int64_t reserveIn = 45851931234;
    const int64_t reserveOut = 125682033533;

    // Calculation
    const int64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );

    REQUIRE( amountIn == 10000 );
}
