//
//  cross_product.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 26/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "cross_product.hpp"
#include <helib/FHE.h>
#include <NTL/ZZX.h>

using helib::Ctxt;

array<u16, 3> compute_cross_product(array<u16, 3> lhs, array<u16, 3> rhs) {
    long k = 128; // Security parameter
    long L = 16; // Number of levels in the modulus
    long c = 3; // Nr of columns in key switch matrix.
    long w = 64; // secret key hamming weight
    long p = 1021; // plaintext base
    long d = 0; // Degree of field extension
    long r = 1; // hensel lifting
    
    // Determine a value for m
    auto m = helib::FindM(k, L, c, p, d, 0, 0);
    // Setup context
    auto context = helib::Context(m, p, r);
    // Build mod chain
    helib::buildModChain(context, L, c);
    
    
    // Generating secret key and public key
    NTL::ZZX encryption_polynomial = context.alMod.getFactorsOverZZ()[0];
    auto secretKey = helib::SecKey(context);
    secretKey.GenSecKey();
    const helib::PubKey& publicKey = secretKey;
    
    // Initialize cipherTexts
    Ctxt lhsc(publicKey), rhsc(publicKey);
    
    // Plaintext must be encrypted as a polynomial using zzx api.
    publicKey.Encrypt(lhsc, NTL::ZZX(10));
    publicKey.Encrypt(rhsc, NTL::ZZX(20));
    
    Ctxt result = lhsc;
    result += rhsc;
    
    NTL::ZZX plaintext_result;
    secretKey.Decrypt(plaintext_result, result);
    std::cout << plaintext_result[0] << std::endl;
}
