#define CATCH_CONFIG_MAIN

#include <catch.hpp>
#include <eosio/check.hpp>
#include <uint128_t/uint128_t.cpp>

#include "uniswap.hpp"

TEST_CASE( "get_amount_out #1 (pass)" ) {
    // Inputs
    const uint64_t amount_in = 10000;
    const uint64_t reserve_in = 100000000;
    const uint64_t reserve_out = 400000000;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 39876 );
}

TEST_CASE( "get_amount_out #2 (pass)" ) {
    // Inputs
    const uint64_t amount_in = 10000; // 1.0000 EOS
    const uint64_t reserve_in = 100669664; // 10066.9664 EOS
    const uint64_t reserve_out = 3774590382732755; // 37745903.82732755 PINK

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out, 30, 0 );

    REQUIRE( amountOut == 373786282495 ); // 37378.6282495 PINK
}

TEST_CASE( "get_amount_out #3 (pass)" ) {
    // Inputs
    const uint64_t amount_in = 3734534447974; // 37345.34447974 PINK
    const uint64_t reserve_in = 33593153629677144; // 335931536.29677144  PINK
    const uint64_t reserve_out = 899196436; // 89919.6436 EOS

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );
    REQUIRE( amountOut == 99652 ); // 9.9652 EOS
}

TEST_CASE( "get_amount_out #4 (pass)" ) {
    // Inputs
    const uint64_t amount_in = 10000;
    const uint64_t reserve_in = 45851931234;
    const uint64_t reserve_out = 125682033533;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );
    REQUIRE( amountOut == 27328 );
}

TEST_CASE( "get_amount_in #1 (pass)" ) {
    // Inputs
    const uint64_t amount_out = 39876;
    const uint64_t reserve_in = 100000000;
    const uint64_t reserve_out = 400000000;

    // Calculation
    const uint64_t amountIn = uniswap::get_amount_in( amount_out, reserve_in, reserve_out );

    REQUIRE( amountIn == 10000 );
}

TEST_CASE( "get_amount_in #2 (pass)" ) {
    // Inputs
    const uint64_t amount_out = 373786282495;
    const uint64_t reserve_in = 100669664;
    const uint64_t reserve_out = 3774590382732755;

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

TEST_CASE( "get_amount_out Defibox #1 (pass)" ) {
    // Inputs
    const uint64_t amount_in = 1000;
    const uint64_t reserve_in = 47563210;
    const uint64_t reserve_out = 48270636583184845;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 1011809599026  );
}

TEST_CASE( "get_amount_out Defibox #2 (pass)" ) {
    // Inputs
    const uint64_t amount_in = 508947582090;
    const uint64_t reserve_in = 48269624773585819;
    const uint64_t reserve_out = 47564209;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 500  );
}

TEST_CASE( "get_amount_out Defibox RAMS #3 (pass)" ) {
    // https://eos.eosq.eosnation.io/tx/8420cf471010e58c9a152629dd3535aab7cb41f365f43e0855c644acbe7fd035
    // Inputs
    const uint64_t amount_in = 1047;
    const uint64_t reserve_in = 65394;
    const uint64_t reserve_out = 93823580;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 1474206 );
}

TEST_CASE( "get_amount_out Defibox RAMS #4 (pass)" ) {
    // https://eos.eosq.eosnation.io/tx/8420cf471010e58c9a152629dd3535aab7cb41f365f43e0855c644acbe7fd035
    // Inputs
    const uint64_t amount_in = 1500000;
    const uint64_t reserve_in = 92827485;
    const uint64_t reserve_out = 66092;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 1047  );
}

TEST_CASE( "get_amount_out Defibox RAMS #5 (pass)" ) {
    // https://eos.eosq.eosnation.io/tx/8420cf471010e58c9a152629dd3535aab7cb41f365f43e0855c644acbe7fd035
    // Inputs
    const uint64_t amount_in = 212;
    const uint64_t reserve_in = 4779316;
    const uint64_t reserve_out = 553900794;

    // Calculation
    const uint64_t amountOut = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );

    REQUIRE( amountOut == 24403  );
}
