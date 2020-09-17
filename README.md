# `uniswap`

> Uniswap - Price algorithm

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset.

## Quickstart

```c++
#include "uniswap.hpp"

uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
```

## Table of Content

- [STATIC `getAmountOut`](#action-getAmountOut)
- [STATIC `getAmountIn`](#action-getAmountIn)

## STATIC `getAmountOut`

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset

### params

- `{uint64_t} amountIn` - amount input
- `{uint64_t} reserveIn` - reserve input
- `{uint64_t} reserveOut` - reserve output

### example

```c++
// Inputs
const uint64_t amountIn = 10000;
const uint64_t reserveIn = 45851931234;
const uint64_t reserveOut = 125682033533;

// Calculation
const uint64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
// => 27328
```

## STATIC `getAmountIn`

Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.

### params

- `{uint64_t} amountIn` - amount input
- `{uint64_t} reserveIn` - reserve input
- `{uint64_t} reserveOut` - reserve output

### example

```c++
// Inputs
const uint64_t amountOut = 27328;
const uint64_t reserveIn = 45851931234;
const uint64_t reserveOut = 125682033533;

// Calculation
const uint64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );
// => 10000
```