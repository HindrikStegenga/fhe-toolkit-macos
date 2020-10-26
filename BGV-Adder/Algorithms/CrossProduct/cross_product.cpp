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

array<long, CV_SIZE> compute_cross_product(array<i16, CV_SIZE> lhs, array<i16, CV_SIZE> rhs) {
    long k = 128; // Security parameter
    long L = 16; // Number of levels in the modulus default is 16
    long c = 3; // Nr of columns in key switch matrix.
    long w = 64; // secret key hamming weight
    
    // Change to 65537 for noise warning. (Always fun times)
    // Compensate for that by setting L = 128. (Increase modchain basically)
    // Set P to 65537 and L to 32 to showcase decryption failures.
    
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
    // Cross product is vec a x b.
    // 0 => ay * bz - az * by
    // 1 => az * bx - ax * bz
    // 2 => ax * by - ay * bx
    
    // Left hand side of equations
    array<Ctxt, CV_SIZE> lhs_a = {
        lhs_ciphertext[1], //ay
        lhs_ciphertext[2], //az
        lhs_ciphertext[0], //ax
    };
    array<Ctxt, CV_SIZE> lhs_b = {
        rhs_ciphertext[2], //bz
        rhs_ciphertext[0], //bx
        rhs_ciphertext[1], //by
    };
    
    // Compute first set of products
    for (size_t i = 0; i < CV_SIZE; ++i) {
        lhs_a[i] *= lhs_b[i];
    }
    
    // Right hand side of equations
    array<Ctxt, CV_SIZE> rhs_a = {
        lhs_ciphertext[2], //az
        lhs_ciphertext[0], //ax
        lhs_ciphertext[1], //ay
    };
    array<Ctxt, CV_SIZE> rhs_b = {
        rhs_ciphertext[1], //by
        rhs_ciphertext[2], //bz
        rhs_ciphertext[0], //bx
    };
    
    // Compute second set of products
    for (size_t i = 0; i < CV_SIZE; ++i) {
        rhs_a[i] *= rhs_b[i];
    }
    
    // Compute negation of products
    for (size_t i = 0; i < CV_SIZE; ++i) {
        lhs_a[i] -= rhs_a[i];
    }
    
    array<Ctxt, CV_SIZE> cipher_results = lhs_a;
    
    // Decrypt the results using secret key and convert back from
    // polynomial representation to numeric.
    array<long, CV_SIZE> return_values = {0,0,0};
    array<NTL::ZZX, CV_SIZE> plaintext_results;
    for (size_t i = 0; i < 3; ++i) {
        NTL::ZZX zzx;
        secretKey.Decrypt(zzx, cipher_results[i]);
        conv(return_values[i], zzx[0]);
        // Compensate for negative numbers by checking if it's larger than p/2,
        // In such case it wrapped around due to negative numbers
        if (return_values[i] > p / 2) {
            return_values[i] += (-1 * p);
        }
    }

    return return_values;
}

