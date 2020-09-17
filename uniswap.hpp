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
        const uint64_t amountInWithFee = amountIn * 997;
        const uint64_t numerator = amountInWithFee * reserveOut;
        const uint64_t denominator = reserveIn * 1000 + amountInWithFee;
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
        const uint64_t numerator = reserveIn * amountOut * 1000;
        const uint64_t denominator = (reserveOut - amountOut) * 997;
        const uint64_t amountIn = (numerator / denominator) + 1;
        return amountIn;
    }
};
