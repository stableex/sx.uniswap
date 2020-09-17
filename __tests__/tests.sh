#!/bin/bash

# compile
g++ -std=c++11 -Wall -o basic.tests.out basic.tests.cpp

# run tests
./basic.tests.out --success
