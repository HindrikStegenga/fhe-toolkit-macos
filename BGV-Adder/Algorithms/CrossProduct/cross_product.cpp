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
#include <NTL/tools.h>

using helib::Ctxt;

array<long, CV_SIZE> compute_cross_product(array<u16, CV_SIZE> lhs, array<u16, CV_SIZE> rhs) {
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
       
    // Initialize ciphertexts
    array<Ctxt, CV_SIZE> lhs_ciphertext {
        Ctxt(publicKey),
        Ctxt(publicKey),
        Ctxt(publicKey)
    }, rhs_ciphertext {
        Ctxt(publicKey),
        Ctxt(publicKey),
        Ctxt(publicKey)
    };
    
    // Plaintext must be encrypted as a polynomial using zzx api.
    for (size_t i = 0; i < CV_SIZE; ++i) {
        publicKey.Encrypt(lhs_ciphertext[i], NTL::ZZX(lhs[i]));
        publicKey.Encrypt(rhs_ciphertext[i], NTL::ZZX(rhs[i]));
    }
    
    // Apply operations on the ciphertexts.
    array<Ctxt, CV_SIZE> cipher_results = lhs_ciphertext;
    for (size_t i = 0; i < CV_SIZE; ++i) {
        cipher_results[i] *= rhs_ciphertext[i];
    }
    
    // Decrypt the results using secret key and convert back from
    // polynomial representation to numeric.
    array<long, CV_SIZE> return_values = {0,0,0};
    array<NTL::ZZX, CV_SIZE> plaintext_results;
    for (size_t i = 0; i < 3; ++i) {
        NTL::ZZX zzx;
        secretKey.Decrypt(zzx, cipher_results[i]);
        std::cout << zzx << std::endl;
        conv(return_values[i], zzx[0]);
    }

    return return_values;
}
