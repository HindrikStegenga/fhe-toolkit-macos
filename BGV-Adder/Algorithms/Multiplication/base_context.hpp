//
//  base_context.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 21/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef base_context_hpp
#define base_context_hpp

#include <stdio.h>
#include <iostream>
#include <vector>
#include <helib/helib.h>

using std::vector;
using helib::Context;
using helib::zzX;

class BaseContext {
public:
    // plaintext prime modulus
    long p = 2;
    // Cyclotomic polynomial - defines phi(m).
    long m = 4095;
    // hensel lifting
    long r = 1;
    // modulus chain bits
    long modulus_bits = 500;
    // key switch matrix columns
    long c = 2;
    // factorization of m for bootstrap process
    vector<long> mvec = {7, 5, 9, 13};
    // Generating set for the Zm* group
    vector<long> generators = {2341, 3277, 911};
    // Orders of generators
    vector<long> orders = {6, 4, 6};
    // context
    Context context;
public:
    BaseContext();
};


class PreparedContext : public BaseContext {
public:
    // secret key
    helib::SecKey secret_key;
    // unpack slot encoding
    vector<zzX> unpack_slot_encoding;
    
public:
    PreparedContext();
    
    const helib::PubKey& public_key();
    const helib::EncryptedArray& encrypted_array();
};


#endif /* base_context_hpp */
