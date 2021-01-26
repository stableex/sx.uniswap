#!/bin/bash

git clone https://github.com/stableex/sx.safemath ./__tests__/sx.safemath

# compile
g++ -std=c++11 -o uniswap.t.out uniswap.t.cpp -I __tests__

# test
./uniswap.t.out --success

