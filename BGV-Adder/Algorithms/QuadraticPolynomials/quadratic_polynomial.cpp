//
//  quadratic_polynomial.cpp
//  BGV-Adder
//
//  Created by Andris on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "quadratic_polynomial.hpp"
#include <helib/FHE.h>
#include <NTL/ZZX.h>
#include <NTL/tools.h>

using helib::Ctxt;

long quadratic_polynomial(int16_t aVal, int16_t bVal, int16_t cVal, int16_t xVal) {
    long k = 128; // Security parameter
    long L = 128; // Number of levels in the modulus default is 16
    long c = 3; // Nr of columns in key switch matrix.
    long w = 64; // secret key hamming weight
    
    // Change to 65537 for noise warning. (Always fun times)
    // Compensate for that by setting L = 128. (Increase modchain basically)
    // Set P to 65537 and L to 32 to showcase decryption failures.
    
    long p = 65537; // plaintext base default = 1021
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
    Ctxt aVal_ciphertext = Ctxt(publicKey);
    Ctxt bVal_ciphertext = Ctxt(publicKey);
    Ctxt cVal_ciphertext = Ctxt(publicKey);
    Ctxt xVal_ciphertext = Ctxt(publicKey);

    
    // Plaintext must be encrypted as a polynomial using zzx api.
    publicKey.Encrypt(aVal_ciphertext, NTL::ZZX(aVal));
    publicKey.Encrypt(bVal_ciphertext, NTL::ZZX(bVal));
    publicKey.Encrypt(cVal_ciphertext, NTL::ZZX(cVal));
    publicKey.Encrypt(xVal_ciphertext, NTL::ZZX(xVal));

    
    // Apply operations on the ciphertexts.
    
    aVal_ciphertext *= xVal_ciphertext;
    aVal_ciphertext *= xVal_ciphertext;
    bVal_ciphertext *= xVal_ciphertext;
    
    aVal_ciphertext += bVal_ciphertext;
    aVal_ciphertext += cVal_ciphertext;
    
    Ctxt cipherResult = aVal_ciphertext;

    // Decrypt the results using secret key and convert back from
    // polynomial representation to numeric.
    long return_value = 0;
    NTL::ZZX plaintext_result;
    NTL::ZZX zzx;
    secretKey.Decrypt(zzx, cipherResult);
    conv(return_value, zzx[0]);
    if (return_value > p / 2) {
        return_value += (-1 * p);
    }

    return return_value;
}
