//
//  multiply.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "multiply.hpp"
#include <helib/FHE.h>
#include <NTL/ZZX.h>
#include <NTL/tools.h>

using helib::Ctxt;

long compute_multiplication(i16 lhs, i16 rhs) {
    long k = 128; // Security parameter
    long L = 16; // Number of levels in the modulus default is 16
    long c = 3; // Nr of columns in key switch matrix.
    long w = 64; // secret key hamming weight
        
    long p = 1021; // plaintext base default = 1021
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
       
    // Initialize ciphertexts
    Ctxt lhs_ciphertext(publicKey), rhs_ciphertext(publicKey);
    
    // Encrypt them using the public key
    publicKey.Encrypt(lhs_ciphertext, NTL::ZZX(lhs));
    publicKey.Encrypt(rhs_ciphertext, NTL::ZZX(rhs));
    
    
    // Compute multiplication of a and b
    lhs_ciphertext *= rhs_ciphertext;
    
    Ctxt cipher_result = lhs_ciphertext;
    
    // Decrypt the results using secret key and convert back from
    // polynomial representation to numeric.
    long return_value = 0;
    NTL::ZZX plaintext_result;
    // Decrypt using secret key
    secretKey.Decrypt(plaintext_result, cipher_result);
    
    // Compensate for negative numbers by checking if it's larger than p/2,
    // In such case it wrapped around due to negative numbers
    conv(return_value, plaintext_result[0]);
    if (return_value > p / 2) {
        return_value += (-1 * p);
    }

    return return_value;
}

