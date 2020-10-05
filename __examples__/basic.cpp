
#include <eosio/eosio.hpp>
#include "../uniswap.hpp"

using namespace eosio;

class [[eosio::contract]] basic : public contract {

public:
    using contract::contract;

    [[eosio::action]]
    void getamountout( const asset amount_in, const asset reserve_in, const asset reserve_out, const asset expect ) {
        const asset amount_out = uniswap::get_amount_out( amount_in, reserve_in, reserve_out );
        print( amount_out );
        check( amount_out == expect, "get_amount_out does not match expect");
    }

    [[eosio::action]]
    void getamountin( const asset amount_out, const asset reserve_in, const asset reserve_out, const asset expect ) {
        const asset amount_in = uniswap::get_amount_in( amount_out, reserve_in, reserve_out );
        print( amount_in );
        check( amount_in == expect, "get_amount_in does not match expect");
    }

    [[eosio::action]]
    void quote( const asset amount_a, const asset reserve_a, const asset reserve_b, const asset expect ) {
        const asset amount_b = uniswap::quote( amount_a, reserve_a, reserve_b );
        print( amount_b );
        check( amount_b == expect, "quote does not match expect");
    }
};