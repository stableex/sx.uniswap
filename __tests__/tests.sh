#!/bin/bash

# compile
g++ -std=c++11 -Wall -o getAmountOut.out getAmountOut.cpp

# run tests
./getAmountOut.out --success
