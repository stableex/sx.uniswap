#!/bin/bash

# compile
g++ -std=c++11 -Wall -o basic.tests.out __tests__/basic.tests.cpp

# test
./basic.tests.out --success

