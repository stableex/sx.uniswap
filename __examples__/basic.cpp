#include <eosio/eosio.hpp>

#include "../uniswap.hpp"

using namespace eosio;

class [[eosio::contract]] basic : public contract {

public:
    using contract::contract;

    [[eosio::action]]
    void quote( const int64_t amountA, const int64_t reserveA, const int64_t reserveB ) {
        const int64_t amountB = uniswap::quote( amountA, reserveA, reserveB );
        print( amountB );
    }

    [[eosio::action]]
    void getamountout( const int64_t amountIn, const int64_t reserveIn, const int64_t reserveOut ) {
        const int64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
        print( amountOut );
    }

    [[eosio::action]]
    void getamountin( const int64_t amountOut, const int64_t reserveIn, const int64_t reserveOut ) {
        const int64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );
        print( amountIn );
    }
};