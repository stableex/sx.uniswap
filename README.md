# `uniswap`

> Uniswap - Price algorithm

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset.

## Quickstart

```c++
#include "uniswap.hpp"

uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
```

## Table of Content

- [STATIC `quote`](#action-quote)
- [STATIC `getAmountOut`](#action-getAmountOut)
- [STATIC `getAmountIn`](#action-getAmountIn)

## STATIC `quote`

Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset

### params

- `{int64_t} amountA` - amount A
- `{int64_t} reserveA` - reserve A
- `{int64_t} reserveB` - reserve B

### example

```c++
// Inputs
const int64_t amountA = 10000;
const int64_t reserveA = 45851931234;
const int64_t reserveB = 125682033533;

// Calculation
const int64_t amountB = uniswap::quote( amountA, reserveA, reserveB );
// => 27410
```

## STATIC `getAmountOut`

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset

### params

- `{int64_t} amountIn` - amount input
- `{int64_t} reserveIn` - reserve input
- `{int64_t} reserveOut` - reserve output

### example

```c++
// Inputs
const int64_t amountIn = 10000;
const int64_t reserveIn = 45851931234;
const int64_t reserveOut = 125682033533;

// Calculation
const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
// => 27328
```

## STATIC `getAmountIn`

Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.

### params

- `{int64_t} amountIn` - amount input
- `{int64_t} reserveIn` - reserve input
- `{int64_t} reserveOut` - reserve output

### example

```c++
// Inputs
const int64_t amountOut = 27328;
const int64_t reserveIn = 45851931234;
const int64_t reserveOut = 125682033533;

// Calculation
const int64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );
// => 10000
```