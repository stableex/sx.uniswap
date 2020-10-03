#include <eosio/eosio.hpp>

#include "../uniswap.hpp"

using namespace eosio;

class [[eosio::contract]] basic : public contract {

public:
    using contract::contract;

    [[eosio::action]]
    void getamountout( const asset amountIn, const asset reserveIn, const asset reserveOut, const asset expect ) {
        const asset amountOut = uniswap::get_amount_out( amountIn, reserveIn, reserveOut );
        print( amountOut );
        check( amountOut == expect, "get_amount_out does not match expect");
    }

    [[eosio::action]]
    void getamountin( const asset amountOut, const asset reserveIn, const asset reserveOut, const asset expect ) {
        const asset amountIn = uniswap::get_amount_in( amountOut, reserveIn, reserveOut );
        print( amountIn );
        check( amountIn == expect, "get_amount_in does not match expect");
    }

    [[eosio::action]]
    void quote( const asset amountA, const asset reserveA, const asset reserveB, const asset expect ) {
        const asset amountB = uniswap::quote( amountA, reserveA, reserveB );
        print( amountB );
        check( amountB == expect, "quote does not match expect");
    }
};