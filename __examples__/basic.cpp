#include <eosio/eosio.hpp>

#include "../uniswap.hpp"

using namespace eosio;

class [[eosio::contract]] basic : public contract {

public:
    using contract::contract;

    [[eosio::action]]
    void getamountout( const uint64_t amountIn, const uint64_t reserveIn, const uint64_t reserveOut ) {
        const uint64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
        print( amountOut );
    }
};