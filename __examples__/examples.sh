#!/bin/bash

# unlock wallet
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# create accounts
cleos create account eosio basic EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# build
eosio-cpp basic.cpp

# deploy
cleos set contract basic . basic.wasm basic.abi

# quote
cleos push action basic quote '[10000, 45851931234, 125682033533]' -p basic
# //=> 27410

# getAmountOut
cleos push action basic getamountout '[10000, 45851931234, 125682033533]' -p basic
# //=> 27328

# getAmountIn
cleos push action basic getamountin '[27328, 45851931234, 125682033533]' -p basic
# //=> 10000