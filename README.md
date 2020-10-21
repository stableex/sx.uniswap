# **`Uniswap`**

[![Build Status](https://travis-ci.org/stableex/sx.uniswap.svg?branch=master)](https://travis-ci.org/stableex/sx.uniswap)

> Peripheral EOSIO smart contracts for interacting with Uniswap V2

## Quickstart

```c++
#include "uniswap.hpp"

// Inputs
const uint64_t amount_in = 10000;
const uint64_t reserve_in = 45851931234;
const uint64_t reserve_out = 125682033533;
const uint8_t trade_fee = 20;
const uint8_t protocol_fee = 10;

// Calculation
const uint64_t out = uniswap::get_amount_out( amount_in, reserve_in, reserve_out, trade_fee, protocol_fee );
// => 27328
```

## Pseudocode Price Formula

```c++
function get_amount_out( amount_in, reserve_in, reserve_out, fee ) {
    amount_in_with_fee = amount_in * (10000 - fee);
    numerator = amount_in_with_fee * reserve_out;
    denominator = reserve_in * 10000 + amount_in_with_fee;
    amount_out = numerator / denominator;
    return amount_out;
}
```

## Table of Content

- [STATIC `get_amount_out`](#static-get_amount_out)
- [STATIC `get_amount_in`](#static-get_amount_in)
- [STATIC `quote`](#static-quote)

## STATIC `get_amount_out`

Given an input amount of an asset and pair reserves, returns the maximum output amount of the other asset

### params

- `{uint64_t} amount_in` - amount input
- `{uint64_t} reserve_in` - reserve input
- `{uint64_t} reserve_out` - reserve output
- `{uint8_t} [trade_fee=20]` - (optional) trade fee (pips 1/100 of 1%)
- `{uint8_t} [protocol_fee=10]` - (optional) protocol fee (pips 1/100 of 1%)

### example

```c++
// Inputs
const uint64_t amount_in = 10000;
const uint64_t reserve_in = 45851931234;
const uint64_t reserve_out = 125682033533;
const uint8_t trade_fee = 20;
const uint8_t protocol_fee = 10;

// Calculation
const uint64_t amount_out = uniswap::get_amount_out( amount_in, reserve_in, reserve_out, trade_fee, protocol_fee );
// => 27328
```

## STATIC `get_amount_in`

Given an output amount of an asset and pair reserves, returns a required input amount of the other asset.

### params

- `{uint64_t} amount_in` - amount input
- `{uint64_t} reserve_in` - reserve input
- `{uint64_t} reserve_out` - reserve output
- `{uint8_t} [trade_fee=20]` - (optional) trade fee (pips 1/100 of 1%)
- `{uint8_t} [protocol_fee=10]` - (optional) protocol fee (pips 1/100 of 1%)

### example

```c++
// Inputs
const uint64_t amount_out = 27328;
const uint64_t reserve_in = 45851931234;
const uint64_t reserve_out = 125682033533;
const uint8_t trade_fee = 20;
const uint8_t protocol_fee = 10;

// Calculation
const uint64_t amount_in = uniswap::get_amount_in( amount_out, reserve_in, reserve_out, trade_fee, protocol_fee );
// => 10000
```

## STATIC `quote`

Given some amount of an asset and pair reserves, returns an equivalent amount of the other asset

### params

- `{uint64_t} amount_a` - amount A
- `{uint64_t} reserve_a` - reserve A
- `{uint64_t} reserve_b` - reserve B

### example

```c++
// Inputs
const uint64_t amount_a = 10000;
const uint64_t reserve_a = 45851931234;
const uint64_t reserve_b = 125682033533;

// Calculation
const uint64_t amountB = uniswap::quote( amount_a, reserve_a, reserve_b );
// => 27410
```
