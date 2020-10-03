#pragma once

#include <eosio/asset.hpp>

#include <math.h>
#include <string>

using namespace eosio;
using namespace std;

namespace uniswap {
    /**
     * ## STATIC `asset_to_double`
     *
     * Convert asset to double
     *
     * ### params
     *
     * - `{asset} quantity` - quantity
     *
     * ### returns
     *
     * - `{double}` - amount
     *
     * ### example
     *
     * ```c++
     * const asset quantity = asset{10000, symbol{"EOS", 4}};
     * const double amount = uniswap::asset_to_double( quantity );
     * // => 1.0
     * ```
     */
    static double asset_to_double( const asset quantity )
    {
        if ( quantity.amount == 0 ) return 0.0;
        return quantity.amount / pow(10, quantity.symbol.precision());
    }

    /**
     * ## STATIC `double_to_asset`
     *
     * Convert double to asset
     *
     * ### params
     *
     * - `{double} amount` - amount
     * - `{symbol} symbol` - symbol
     *
     * ### returns
     *
     * - `{asset}` - token
     *
     * ### example
     *
     * ```c++
     * const double amount = 1.0;
     * const symbol sym = symbol{"EOS", 4};
     * const asset token = uniswap::double_to_asset( amount, sym );
     * // => "1.0000 EOS"
     * ```
     */
    static asset double_to_asset( const double amount, const symbol sym )
    {
        return asset{ static_cast<int64_t>( round(amount * pow(10, sym.precision()))), sym };
    }

    /**
     * ## STATIC `sort_tokens`
     *
     * Returns sorted token assets, used to handle return values from pairs sorted in this order
     *
     * ### params
     *
     * - `{asset} tokenA` - token A
     * - `{asset} tokenB` - token B
     *
     * ### returns
     *
     * - `{pair<asset, asset>}` - sorted tokens
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset tokenA = asset{10000, symbol{"USDT", 4}};
     * const asset tokenB = asset{10000, symbol{"EOS", 4}};
     *
     * // Sort
     * const auto[ token0, token1 ] = uniswap::sort_tokens( tokenA, tokenB );
     * // token0 => "1.0000 EOS"
     * // token1 => "1.0000 USDT"
     * ```
     */
    static pair<asset, asset> sort_tokens( const asset tokenA, const asset tokenB )
    {
        check(tokenA.symbol != tokenB.symbol, "UniswapLibrary: IDENTICAL_ASSETS");
        return tokenA.symbol < tokenB.symbol ? pair<asset, asset>{tokenA, tokenB} : pair<asset, asset>{tokenB, tokenA};
    }

    /**
     * ## STATIC `get_amount_out`
     *
     * Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset
     *
     * ### params
     *
     * - `{asset} amountIn` - amount input
     * - `{asset} reserveIn` - reserve input
     * - `{asset} reserveOut` - reserve output
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset amountIn = asset{10000, symbol{"EOS", 4}};
     * const asset reserveIn = asset{45851931234, symbol{"EOS", 4}};
     * const asset reserveOut = asset{125682033533, symbol{"USDT", 4}};
     *
     * // Calculation
     * const asset amountOut = uniswap::get_amount_out( amountIn, reserveIn, reserveOut );
     * // => "2.7328 USDT"
     * ```
     */
    static asset get_amount_out( const asset amountIn, const asset reserveIn, const asset reserveOut )
    {
        // checks
        check(amountIn.amount > 0, "UniswapLibrary: INSUFFICIENT_INPUT_AMOUNT");
        check(reserveIn.amount > 0 && reserveOut.amount > 0, "UniswapLibrary: INSUFFICIENT_LIQUIDITY");

        // calculations
        const double amountInWithFee = uniswap::asset_to_double(amountIn) * 9970;
        const double numerator = amountInWithFee * uniswap::asset_to_double(reserveOut);
        const double denominator = uniswap::asset_to_double(reserveIn) * 10000 + amountInWithFee;
        const double amountOut = numerator / denominator;

        return uniswap::double_to_asset( amountOut, reserveOut.symbol );
    }

    /**
     * ## STATIC `get_amount_in`
     *
     * Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.
     *
     * ### params
     *
     * - `{asset} amountIn` - amount input
     * - `{asset} reserveIn` - reserve input
     * - `{asset} reserveOut` - reserve output
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset amountOut = asset{27328, symbol{"USDT", 4}};
     * const asset reserveIn = asset{45851931234, symbol{"EOS", 4}};
     * const asset reserveOut = asset{125682033533, symbol{"USDT", 4}};
     *
     * // Calculation
     * const asset amountIn = uniswap::get_amount_in( amountOut, reserveIn, reserveOut );
     * // => "1.0000 EOS"
     * ```
     */
    static asset get_amount_in( const asset amountOut, const asset reserveIn, const asset reserveOut )
    {
        // checks
        check(amountOut.amount > 0, "UniswapLibrary: INSUFFICIENT_OUTPUT_AMOUNT");
        check(reserveIn.amount > 0 && reserveOut.amount > 0, "UniswapLibrary: INSUFFICIENT_LIQUIDITY");

        const double numerator = uniswap::asset_to_double(reserveIn) * uniswap::asset_to_double(amountOut) * 10000;
        const double denominator = (uniswap::asset_to_double(reserveOut) - uniswap::asset_to_double(amountOut)) * 9970;
        const double amountIn = (numerator / denominator);

        return uniswap::double_to_asset( amountIn, reserveIn.symbol );
    }

    /**
     * ## STATIC `quote`
     *
     * Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset
     *
     * ### params
     *
     * - `{asset} amountA` - amount A
     * - `{asset} reserveA` - reserve A
     * - `{asset} reserveB` - reserve B
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset amountA = asset{10000, symbol{"EOS", 4}};
     * const asset reserveA = asset{45851931234, symbol{"EOS", 4}};
     * const asset reserveB = asset{125682033533, symbol{"USDT", 4}};
     *
     * // Calculation
     * const asset amountB = uniswap::quote( amountA, reserveA, reserveB );
     * // => "2.7410 USDT"
     * ```
     */
    static asset quote( const asset amountA, const asset reserveA, const asset reserveB )
    {
        check(amountA.amount > 0, "UniswapLibrary: INSUFFICIENT_AMOUNT");
        check(reserveA.amount > 0 && reserveB.amount > 0, "UniswapLibrary: INSUFFICIENT_LIQUIDITY");
        const double amountB = uniswap::asset_to_double( amountA ) * uniswap::asset_to_double( reserveB ) / uniswap::asset_to_double( reserveA );
        return uniswap::double_to_asset( amountB, reserveB.symbol );
    }
}