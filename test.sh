#!/bin/bash

# compile
g++ -std=c++11 -Wall -o uniswap.t.out uniswap.t.cpp -I __tests__

# test
./uniswap.t.out --success

