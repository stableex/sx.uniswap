#include <eosio/eosio.hpp>

#include "../uniswap.hpp"

using namespace eosio;

class [[eosio::contract]] basic : public contract {

public:
    using contract::contract;

    [[eosio::action]]
    void getamountout( const uint64_t amountIn, const uint64_t reserveIn, const uint64_t reserveOut, const uint64_t expect ) {
        const uint64_t amountOut = uniswap::getAmountOut( amountIn, reserveIn, reserveOut );
        print( amountOut );
        check( amountOut == expect, "getAmountOut does not match expect");
    }

    [[eosio::action]]
    void getamountin( const uint64_t amountOut, const uint64_t reserveIn, const uint64_t reserveOut, const uint64_t expect ) {
        const uint64_t amountIn = uniswap::getAmountIn( amountOut, reserveIn, reserveOut );
        print( amountIn );
        check( amountIn == expect, "getAmountIn does not match expect");
    }

    [[eosio::action]]
    void quote( const uint64_t amountA, const uint64_t reserveA, const uint64_t reserveB, const uint64_t expect ) {
        const uint64_t amountB = uniswap::quote( amountA, reserveA, reserveB );
        print( amountB );
        check( amountB == expect, "quote does not match expect");
    }
};