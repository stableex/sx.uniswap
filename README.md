# **`Uniswap V2`**

[![Build Status](https://travis-ci.org/stableex/sx.uniswap.svg?branch=master)](https://travis-ci.org/stableex/sx.uniswap)

> 🎚 Peripheral EOSIO smart contracts for interacting with Uniswap V2

## Quickstart

```c++
#include "uniswap.hpp"

uniswap::get_amount_out( amountIn, reserveIn, reserveOut );
```

## Table of Content

- [STATIC `get_amount_out`](#action-get_amount_out)
- [STATIC `get_amount_in`](#action-get_amount_in)
- [STATIC `quote`](#action-quote)
- [STATIC `sort_tokens`](#action-sort_tokens)
- [STATIC `double_to_asset`](#action-double_to_asset)
- [STATIC `asset_to_double`](#action-asset_to_double)

## STATIC `get_amount_out`

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset

### params

- `{asset} amountIn` - amount input
- `{asset} reserveIn` - reserve input
- `{asset} reserveOut` - reserve output

### example

```c++
// Inputs
const asset amountIn = asset{10000, symbol{"EOS", 4}};
const asset reserveIn = asset{45851931234, symbol{"EOS", 4}};
const asset reserveOut = asset{125682033533, symbol{"USDT", 4}};

// Calculation
const asset amountOut = uniswap::get_amount_out( amountIn, reserveIn, reserveOut );
// => "2.7328 USDT"
```

## STATIC `get_amount_in`

Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.

### params

- `{asset} amountIn` - amount input
- `{asset} reserveIn` - reserve input
- `{asset} reserveOut` - reserve output

### example

```c++
// Inputs
const asset amountOut = asset{27328, symbol{"USDT", 4}};
const asset reserveIn = asset{45851931234, symbol{"EOS", 4}};
const asset reserveOut = asset{125682033533, symbol{"USDT", 4}};

// Calculation
const asset amountIn = uniswap::get_amount_in( amountOut, reserveIn, reserveOut );
// => "1.0000 EOS"
```

## STATIC `quote`

Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset

### params

- `{asset} amountA` - amount A
- `{asset} reserveA` - reserve A
- `{asset} reserveB` - reserve B

### example

```c++
// Inputs
const asset amountA = asset{10000, symbol{"EOS", 4}};
const asset reserveA = asset{45851931234, symbol{"EOS", 4}};
const asset reserveB = asset{125682033533, symbol{"USDT", 4}};

// Calculation
const asset amountB = uniswap::quote( amountA, reserveA, reserveB );
// => "2.7410 USDT"
```

## STATIC `sort_tokens`

Returns sorted token assets, used to handle return values from pairs sorted in this order

### params

- `{asset} tokenA` - token A
- `{asset} tokenB` - token B

### returns

- `{pair<asset, asset>}` - sorted tokens

### example

```c++
// Inputs
const asset tokenA = asset{10000, symbol{"USDT", 4}};
const asset tokenB = asset{10000, symbol{"EOS", 4}};

// Sort
const auto[ token0, token1 ] = uniswap::sort_tokens( tokenA, tokenB );
// token0 => "1.0000 EOS"
// token1 => "1.0000 USDT"
```

## STATIC `double_to_asset`

Convert double to asset

### params

- `{double} amount` - amount
- `{symbol} symbol` - symbol

### returns

- `{asset}` - token

### example

```c++
const double amount = 1.0;
const symbol sym = symbol{"EOS", 4};
const asset token = uniswap::double_to_asset( amount, sym );
// => "1.0000 EOS"
```

## STATIC `asset_to_double`

Convert asset to double

### params

- `{asset} quantity` - quantity

### returns

- `{double}` - amount

### example

```c++
const asset quantity = asset{10000, symbol{"EOS", 4}};
const double amount = uniswap::asset_to_double( quantity );
// => 1.0
```