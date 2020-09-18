namespace uniswap {
    /**
     * ## STATIC `quote`
     *
     * Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset
     *
     * ### params
     *
     * - `{int64_t} amountA` - amount A
     * - `{int64_t} reserveA` - reserve A
     * - `{int64_t} reserveB` - reserve B
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const int64_t amountA = 10000;
     * const int64_t reserveA = 45851931234;
     * const int64_t reserveB = 125682033533;
     *
     * // Calculation
     * const int64_t amountB = uniswap::quote( amountA, reserveA, reserveB );
     * // => 27410
     * ```
     */
    int64_t quote( const int64_t amountA, int64_t reserveA, int64_t reserveB)
    {
        eosio::check(amountA > 0, "UniswapV2Library: INSUFFICIENT_AMOUNT");
        eosio::check(reserveA > 0 && reserveB > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const int64_t amountB = amountA * reserveB / reserveA;
        return amountB;
    }

    /**
     * ## STATIC `getAmountOut`
     *
     * Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset
     *
     * ### params
     *
     * - `{int64_t} amountIn` - amount input
     * - `{int64_t} reserveIn` - reserve input
     * - `{int64_t} reserveOut` - reserve output
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const int64_t amountIn = 10000;
     * const int64_t reserveIn = 45851931234;
     * const int64_t reserveOut = 125682033533;
     *
     * // Calculation
     * const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
     * // => 27328
     * ```
     */
    int64_t getAmountOut( const int64_t amountIn, const int64_t reserveIn, const int64_t reserveOut )
    {
        eosio::check(amountIn > 0, "UniswapV2Library: INSUFFICIENT_INPUT_AMOUNT");
        eosio::check(reserveIn > 0 && reserveOut > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const int64_t amountInWithFee = amountIn * 997;
        const int64_t numerator = amountInWithFee * reserveOut;
        const int64_t denominator = reserveIn * 1000 + amountInWithFee;
        const int64_t amountOut = numerator / denominator;
        return amountOut;
    }

    /**
     * ## STATIC `getAmountIn`
     *
     * Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.
     *
     * ### params
     *
     * - `{int64_t} amountIn` - amount input
     * - `{int64_t} reserveIn` - reserve input
     * - `{int64_t} reserveOut` - reserve output
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const int64_t amountOut = 27328;
     * const int64_t reserveIn = 45851931234;
     * const int64_t reserveOut = 125682033533;
     *
     * // Calculation
     * const int64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );
     * // => 10000
     * ```
     */
    int64_t getAmountIn( int64_t amountOut, int64_t reserveIn, int64_t reserveOut )
    {
        eosio::check(amountOut > 0, "UniswapV2Library: INSUFFICIENT_OUTPUT_AMOUNT");
        eosio::check(reserveIn > 0 && reserveOut > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const int64_t numerator = reserveIn * amountOut * 1000;
        const int64_t denominator = (reserveOut - amountOut) * 997;
        const int64_t amountIn = (numerator / denominator) + 1;
        return amountIn;
    }
};
