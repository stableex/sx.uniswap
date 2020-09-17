#include <eosio/eosio.hpp>
#include "../uniswap.hpp"

using namespace eosio;

class [[eosio::contract]] basic : public contract {

public:
    using contract::contract;

    [[eosio::action]]
    void getamountout( const int64_t amountIn, const int64_t reserveIn, const int64_t reserveOut ) {
        const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
        print( amountOut );
    }
};