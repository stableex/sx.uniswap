#define CATCH_CONFIG_MAIN

#include "catch.hpp"

int64_t getAmountOut( const int64_t amountIn, const int64_t reserveIn, const int64_t reserveOut ) {
    const int64_t amountInWithFee = amountIn * 997;
    const int64_t numerator = amountInWithFee * reserveOut;
    const int64_t denominator = reserveIn * 1000 + amountInWithFee;
    const int64_t amountOut = numerator / denominator;
    return amountOut;
}

TEST_CASE( "getAmountOut (pass)" ) {
    // Inputs
    const int64_t amountIn = 10000;
    const int64_t reserveIn = 45851931234;
    const int64_t reserveOut = 125682033533;

    // Calculation
    const int64_t amountOut = getAmountOut( amountIn, reserveIn, reserveOut );

    REQUIRE( amountOut == 27328 );
}
