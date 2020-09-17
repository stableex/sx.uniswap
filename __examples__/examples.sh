#!/bin/bash

# unlock wallet
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# create accounts
cleos create account eosio basic EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# build
eosio-cpp basic.cpp

# deploy
cleos set contract basic . basic.wasm basic.abi

# push
cleos push action basic getamountout '[10000, 45851931234, 125682033533]' -p basic
# //=> 27328