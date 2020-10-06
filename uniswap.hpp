#pragma once

#include <eosio/asset.hpp>

#include <math.h>

namespace uniswap {

    using eosio::asset;
    using eosio::symbol;

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
        return asset{ static_cast<int64_t>( amount * pow(10, sym.precision())), sym };
    }

    /**
     * ## STATIC `sort_tokens`
     *
     * Returns sorted token assets, used to handle return values from pairs sorted in this order
     *
     * ### params
     *
     * - `{asset} a` - token A
     * - `{asset} b` - token B
     *
     * ### returns
     *
     * - `{pair<asset, asset>}` - sorted tokens
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset a = asset{10000, symbol{"USDT", 4}};
     * const asset b = asset{10000, symbol{"EOS", 4}};
     *
     * // Sort
     * const auto[ token0, token1 ] = uniswap::sort_tokens( a, b );
     * // token0 => "1.0000 EOS"
     * // token1 => "1.0000 USDT"
     * ```
     */
    static std::pair<asset, asset> sort_tokens( const asset a, const asset b )
    {
        eosio::check(a.symbol != b.symbol, "UniswapLibrary: IDENTICAL_ASSETS");
        return a.symbol < b.symbol ? std::pair<asset, asset>{a, b} : std::pair<asset, asset>{b, a};
    }

    /**
     * ## STATIC `get_amount_out`
     *
     * Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset
     *
     * ### params
     *
     * - `{asset} amount_in` - amount input
     * - `{asset} reserve_in` - reserve input
     * - `{asset} reserve_out` - reserve output
     * - `{uint8_t} [fee=30]` - (optional) trading fee (pips 1/100 of 1%)
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset amount_in = asset{10000, symbol{"EOS", 4}};
     * const asset reserve_in = asset{45851931234, symbol{"EOS", 4}};
     * const asset reserve_out = asset{125682033533, symbol{"USDT", 4}};
     * const uint8_t fee = 30;
     *
     * // Calculation
     * const asset amount_out = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );
     * // => "2.7328 USDT"
     * ```
     */
    static asset get_amount_out( const asset amount_in, const asset reserve_in, const asset reserve_out, const uint8_t fee = 30 )
    {
        // checks
        eosio::check(amount_in.amount > 0, "UniswapLibrary: INSUFFICIENT_INPUT_AMOUNT");
        eosio::check(reserve_in.amount > 0 && reserve_out.amount > 0, "UniswapLibrary: INSUFFICIENT_LIQUIDITY");

        // calculations
        const double amount_in_with_fee = uniswap::asset_to_double(amount_in) * (10000 - fee);
        const double numerator = amount_in_with_fee * uniswap::asset_to_double(reserve_out);
        const double denominator = uniswap::asset_to_double(reserve_in) * 10000 + amount_in_with_fee;
        const double amount_out = numerator / denominator;

        return uniswap::double_to_asset( amount_out, reserve_out.symbol );
    }

    /**
     * ## STATIC `get_amount_in`
     *
     * Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.
     *
     * ### params
     *
     * - `{asset} amount_out` - amount input
     * - `{asset} reserve_in` - reserve input
     * - `{asset} reserveOut` - reserve output
     * - `{uint8_t} [fee=30]` - (optional) trading fee (pips 1/100 of 1%)
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset amount_out = asset{27328, symbol{"USDT", 4}};
     * const asset reserve_in = asset{45851931234, symbol{"EOS", 4}};
     * const asset reserve_out = asset{125682033533, symbol{"USDT", 4}};
     * const uint8_t fee = 30;
     *
     * // Calculation
     * const asset amount_in = uniswap::get_amount_in( amount_out, reserve_in, reserve_out, fee );
     * // => "1.0000 EOS"
     * ```
     */
    static asset get_amount_in( const asset amount_out, const asset reserve_in, const asset reserve_out, const uint8_t fee = 30 )
    {
        // checks
        eosio::check(amount_out.amount > 0, "UniswapLibrary: INSUFFICIENT_OUTPUT_AMOUNT");
        eosio::check(reserve_in.amount > 0 && reserve_out.amount > 0, "UniswapLibrary: INSUFFICIENT_LIQUIDITY");

        const double numerator = uniswap::asset_to_double(reserve_in) * uniswap::asset_to_double(amount_out) * 10000;
        const double denominator = (uniswap::asset_to_double(reserve_out) - uniswap::asset_to_double(amount_out)) * (10000 - fee);
        const double amount_in = numerator / denominator;

        return uniswap::double_to_asset( amount_in, reserve_in.symbol );
    }

    /**
     * ## STATIC `quote`
     *
     * Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset
     *
     * ### params
     *
     * - `{asset} amount_a` - amount A
     * - `{asset} reserve_a` - reserve A
     * - `{asset} reserve_b` - reserve B
     *
     * ### example
     *
     * ```c++
     * // Inputs
     * const asset amount_a = asset{10000, symbol{"EOS", 4}};
     * const asset reserve_a = asset{45851931234, symbol{"EOS", 4}};
     * const asset reserve_b = asset{125682033533, symbol{"USDT", 4}};
     *
     * // Calculation
     * const asset amount_b = uniswap::quote( amount_a, reserve_a, reserve_b );
     * // => "2.7410 USDT"
     * ```
     */
    static asset quote( const asset amount_a, const asset reserve_a, const asset reserve_b )
    {
        eosio::check(amount_a.amount > 0, "UniswapLibrary: INSUFFICIENT_AMOUNT");
        eosio::check(reserve_a.amount > 0 && reserve_b.amount > 0, "UniswapLibrary: INSUFFICIENT_LIQUIDITY");
        const double amount_b = uniswap::asset_to_double( amount_a ) * uniswap::asset_to_double( reserve_b ) / uniswap::asset_to_double( reserve_a );
        return uniswap::double_to_asset( amount_b, reserve_b.symbol );
    }
}