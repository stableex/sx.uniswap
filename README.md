# `uniswap`

> Uniswap - Price algorithm

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset.

## Quickstart

```c++
#include "uniswap.hpp"

// Inputs
const int64_t amountIn = 10000;
const int64_t reserveIn = 45851931234;
const int64_t reserveOut = 125682033533;

// Calculation
const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
// => 27328
```
