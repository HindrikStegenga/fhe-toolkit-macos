//
//  binary_ops.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "binary_ops.hpp"
#include <vector>
#include <array>
#include <helib/helib.h>
#include <helib/FHE.h>
#include <helib/binaryArith.h>
#include <helib/binaryCompare.h>
#include <helib/intraSlot.h>
#include <algorithm>

using helib::SecKey;
using helib::PubKey;
using helib::Ctxt;
using helib::Context;
using std::vector;
using std::array;

Ctxt gcd(Ctxt p, Ctxt q, Ctxt zero, Ctxt one, helib::Context ctx) {
    if (q == zero) { return q; }
    if (p == zero) { return p; }
    
    Ctxt p_shift_one(p);
    
    p_shift_one.divideBy2();
    
    //Left shift by 1 == mult by 2.
    p_shift_one.multByConstant(NTL::ZZX(2));
    
    
    
    
    return p_shift_one;
    
}

long compute_gcd(u16 lhs, u16 rhs, bool bootstrap) {
    const long bitsize = sizeof(u16); // Size in bits of inputs
    long p = 2; // plaintext prime
    long m = 1023; // modulus
    
    // Factorization for bootstrapping process
    vector<long> mvec = { 11, 93, 0 };
    
    // Generators for ZM* group
    vector<long> generators = { 838, 584, 0 };
    
    // Orders of the generators
    vector<long> orders = { 10, 6, 0 };
    
    // Number of levels in mod chain. Depends on bootstrapping.
    // If no bootstrap we just compute a large number which should be big enough.
    long L = bootstrap ? 900 : 30 * (7 + NTL::NumBits(bitsize + 2));
    // Key switch matrix columns
    long c = 2;
    // Hensel value
    long r = 1;
    
    // Instantiate context
    Context context = Context(m, p, r);
    
    // Set up mod chain
    buildModChain(context, L, c, bootstrap);
    
    // Bootstrap if enabled
    if (bootstrap) {
        context.makeBootstrappable(helib::convert<NTL::Vec<long>, vector<long>>(mvec), 0);
    }
    
    // Setting up unpackslot encoding
    std::vector<helib::zzX> unpackSlotEncoding;
    helib::buildUnpackSlotEncoding(unpackSlotEncoding, *context.ea);
    
    // Generate Secret Key
    SecKey secret_key(context);
    secret_key.GenSecKey(); // Generate a fresh key
    helib::addSome1DMatrices(secret_key); //Compute key switch matrices
    helib::addFrbMatrices(secret_key); //Generate frobenius matrices.
    
    // Generate recryption data if necessary
    if (bootstrap) {
        secret_key.genRecryptData();
    }
    
    const helib::EncryptedArray& ea = *context.ea;
    
    // Convert lhs and rhs into long represenations
    long ptxt_lhs = lhs;
    long ptxt_rhs = rhs;
        
    // Initialize all the cipher text vectors.
    // This is so we can encrypt each bit into ctxt's
    
    NTL::Vec<Ctxt> a_cipher, b_cipher;
    //helib::resize(a_cipher, bitsize);
    //helib::resize(b_cipher, bitsize + 1);
    
    // Encrypt all things
    for (long i = 0; i < bitsize; ++i) {
        secret_key.Encrypt(a_cipher[i], NTL::ZZX((ptxt_lhs >> i) & 1));
        secret_key.Encrypt(b_cipher[i], NTL::ZZX((ptxt_rhs >> i) & 1));
        if (bootstrap) { // put them at a lower level, required for bootstrapping
            a_cipher[i].bringToSet(context.getCtxtPrimes(5));
            b_cipher[i].bringToSet(context.getCtxtPrimes(5));
        }
    }
    
    std::vector<long> slotsA, slotsB;
    //compareTwoNumbers(mu, ni, helib::CtPtrs_VecCt(a_cipher), helib::CtPtrs_VecCt(b_cipher), false, &unpackSlotEncoding);
    
    //ea.decrypt(a_cipher, secret_key, slotsA);
    //ea.decrypt(b_cipher, secret_key, slotsB);
    
    std::cout << "mu (a > b) " << slotsA[0] << std::endl;
    std::cout << "ni (a < b) " << slotsB[0] << std::endl;
    
    return lhs;
}

std::pair<long,long> compare_binary_numbers(array<bool, BIN_OPS_NR_BITS> lhs, array<bool, BIN_OPS_NR_BITS> rhs, bool bootstrap) {
    const long bitsize = BIN_OPS_NR_BITS; // Size in bits of inputs
    long p = 2; // plaintext prime
    long m = 1023; // modulus
    
    // Factorization for bootstrapping process
    vector<long> mvec = { 11, 93, 0 };
    
    // Generators for ZM* group
    vector<long> generators = { 838, 584, 0 };
    
    // Orders of the generators
    vector<long> orders = { 10, 6, 0 };
    
    // Number of levels in mod chain. Depends on bootstrapping.
    // If no bootstrap we just compute a large number which should be big enough.
    long L = bootstrap ? 900 : 30 * (7 + NTL::NumBits(bitsize + 2));
    // Key switch matrix columns
    long c = 2;
    // Hensel value
    long r = 1;
    
    // Instantiate context
    Context context = Context(m, p, r);
    
    // Set up mod chain
    buildModChain(context, L, c, bootstrap);
    
    // Bootstrap if enabled
    if (bootstrap) {
        context.makeBootstrappable(helib::convert<NTL::Vec<long>, vector<long>>(mvec), 0);
    }
    
    // Setting up unpackslot encoding
    std::vector<helib::zzX> unpackSlotEncoding;
    helib::buildUnpackSlotEncoding(unpackSlotEncoding, *context.ea);
    
    // Generate Secret Key
    SecKey secret_key(context);
    secret_key.GenSecKey(); // Generate a fresh key
    helib::addSome1DMatrices(secret_key); //Compute key switch matrices
    helib::addFrbMatrices(secret_key); //Generate frobenius matrices.
    
    // Generate recryption data if necessary
    if (bootstrap) {
        secret_key.genRecryptData();
    }
    
    const helib::EncryptedArray& ea = *context.ea;
    
    // Convert lhs and rhs into long represenations
    long ptxt_lhs = std::accumulate(lhs.rbegin(), lhs.rend(), 0, [](int x, int y) { return (x << 1) + y; });
    long ptxt_rhs = std::accumulate(rhs.rbegin(), rhs.rend(), 0, [](int x, int y) { return (x << 1) + y; });
        
    // Initialize all the cipher text vectors.
    // This is so we can encrypt each bit into ctxt's
    
    // mu and ni are indicator bits. These are what we calculate in cipherspace.
    // mu => a > b
    // ni => a < b
    helib::Ctxt mu(secret_key), ni(secret_key);
    NTL::Vec<Ctxt> a_cipher, b_cipher;
    helib::resize(a_cipher, bitsize, mu);
    helib::resize(b_cipher, bitsize, ni);
    
    // Encrypt all things
    for (long i = 0; i < bitsize; ++i) {
        secret_key.Encrypt(a_cipher[i], NTL::ZZX((ptxt_lhs >> i) & 1));
        secret_key.Encrypt(b_cipher[i], NTL::ZZX((ptxt_rhs >> i) & 1));
        if (bootstrap) { // put them at a lower level, required for bootstrapping
            a_cipher[i].bringToSet(context.getCtxtPrimes(5));
            b_cipher[i].bringToSet(context.getCtxtPrimes(5));
        }
    }
    
    std::vector<long> slotsMu, slotsNi;
    compareTwoNumbers(mu,
                        ni,
                        helib::CtPtrs_VecCt(a_cipher),
                        helib::CtPtrs_VecCt(b_cipher),
                        false, //No 2 complement, (i.e. negative numbers)
                        &unpackSlotEncoding);
    
    ea.decrypt(mu, secret_key, slotsMu);
    ea.decrypt(ni, secret_key, slotsNi);
    
    std::cout << "mu (a > b) " << slotsMu[0] << std::endl;
    std::cout << "ni (a < b) " << slotsNi[0] << std::endl;
    
    return std::make_pair(slotsMu[0], slotsNi[0]);
}
