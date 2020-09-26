#pragma once

namespace uniswap {
    /**
     * ## STATIC `getAmountOut`
     *
     * Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset
     *
     * ### params
     *
     * - `{uint64_t} amountIn` - amount input
     * - `{uint64_t} reserveIn` - reserve input
     * - `{uint64_t} reserveOut` - reserve output
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t amountIn = 10000;
     * const uint64_t reserveIn = 45851931234;
     * const uint64_t reserveOut = 125682033533;
     *
     * // Calculation
     * const uint64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
     * // => 27328
     * ```
     */
    uint64_t getAmountOut( const uint64_t amountIn, const uint64_t reserveIn, const uint64_t reserveOut )
    {
        eosio::check(amountIn > 0, "UniswapV2Library: INSUFFICIENT_INPUT_AMOUNT");
        eosio::check(reserveIn > 0 && reserveOut > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const uint128_t amountInWithFee = static_cast<uint128_t>(amountIn) * 997;
        const uint128_t numerator = amountInWithFee * reserveOut;
        const uint128_t denominator = reserveIn * 1000 + amountInWithFee;
        const uint64_t amountOut = numerator / denominator;
        return amountOut;
    }

    /**
     * ## STATIC `getAmountIn`
     *
     * Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.
     *
     * ### params
     *
     * - `{uint64_t} amountIn` - amount input
     * - `{uint64_t} reserveIn` - reserve input
     * - `{uint64_t} reserveOut` - reserve output
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t amountOut = 27328;
     * const uint64_t reserveIn = 45851931234;
     * const uint64_t reserveOut = 125682033533;
     *
     * // Calculation
     * const uint64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );
     * // => 10000
     * ```
     */
    uint64_t getAmountIn( uint64_t amountOut, uint64_t reserveIn, uint64_t reserveOut )
    {
        eosio::check(amountOut > 0, "UniswapV2Library: INSUFFICIENT_OUTPUT_AMOUNT");
        eosio::check(reserveIn > 0 && reserveOut > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const uint128_t numerator = static_cast<uint128_t>(reserveIn) * amountOut * 1000;
        const uint128_t denominator = (reserveOut - amountOut) * 997;
        const uint64_t amountIn = (numerator / denominator) + 1;
        return amountIn;
    }

    /**
     * ## STATIC `quote`
     *
     * Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset
     *
     * ### params
     *
     * - `{uint64_t} amountA` - amount A
     * - `{uint64_t} reserveA` - reserve A
     * - `{uint64_t} reserveB` - reserve B
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const uint64_t amountA = 10000;
     * const uint64_t reserveA = 45851931234;
     * const uint64_t reserveB = 125682033533;
     *
     * // Calculation
     * const uint64_t amountB = uniswap::quote( amountA, reserveA, reserveB );
     * // => 27410
     * ```
     */
    uint64_t quote( const uint64_t amountA, uint64_t reserveA, uint64_t reserveB)
    {
        eosio::check(amountA > 0, "UniswapV2Library: INSUFFICIENT_AMOUNT");
        eosio::check(reserveA > 0 && reserveB > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const uint64_t amountB = static_cast<uint128_t>(amountA) * reserveB / reserveA;
        return amountB;
    }
    // computeProfitMaximizingTrade
    // https://github.com/Uniswap/uniswap-v2-periphery/blob/master/contracts/examples/ExampleSwapToPrice.sol#L24
};
