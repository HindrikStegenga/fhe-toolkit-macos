//
//  complex_conjugate.cpp
//  BGV-Adder
//
//  Created by Andris on 28/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "complex_conjugate.hpp"
#include <helib/FHE.h>
#include <NTL/ZZX.h>
#include <NTL/tools.h>

using helib::Ctxt;

std::array<long, ARRAY_SIZE> complex_conjugate(int16_t a, int16_t b) {
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
    Ctxt a_ciphertext = Ctxt(publicKey);
    Ctxt b_ciphertext = Ctxt(publicKey);

    
    // Plaintext must be encrypted as a polynomial using zzx api.
    publicKey.Encrypt(a_ciphertext, NTL::ZZX(a));
    publicKey.Encrypt(b_ciphertext, NTL::ZZX(b));

    
    // Apply operations on the ciphertexts.
    
    b_ciphertext *= -1;
    
    std::array<Ctxt, ARRAY_SIZE> cipher_results = {a_ciphertext, b_ciphertext};
    
    // Decrypt the results using secret key and convert back from
    // polynomial representation to numeric.
    std::array<long, ARRAY_SIZE> return_values = {0,0};
    std::array<NTL::ZZX, ARRAY_SIZE> plaintext_results;
    for (size_t i = 0; i < 2; ++i) {
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
