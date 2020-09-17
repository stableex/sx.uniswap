#include <eosio/eosio.hpp>

using namespace eosio;

namespace uniswap {
    /**
     * Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset
     *
     * // Inputs
     * const int64_t amountIn = 10000;
     * const int64_t reserveIn = 45851931234;
     * const int64_t reserveOut = 125682033533;
     *
     * // Calculation
     * const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
     * // => 27328
     */
    int64_t getAmountOut( const int64_t amountIn, const int64_t reserveIn, const int64_t reserveOut ) {
        check(amountIn > 0, "UniswapV2Library: INSUFFICIENT_INPUT_AMOUNT");
        check(reserveIn > 0 && reserveOut > 0, "UniswapV2Library: INSUFFICIENT_LIQUIDITY");
        const int64_t amountInWithFee = amountIn * 997;
        const int64_t numerator = amountInWithFee * reserveOut;
        const int64_t denominator = reserveIn * 1000 + amountInWithFee;
        const int64_t amountOut = numerator / denominator;
        return amountOut;
    }
};
