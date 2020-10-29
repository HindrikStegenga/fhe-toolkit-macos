//
//  ckks_complex_matrix_product.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 29/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "ckks_complex_matrix_product.hpp"
#include <helib/norms.h>

using helib::Context;
using helib::Ctxt;
using helib::SecKey;
using helib::PubKey;
using std::vector;
using std::complex;


array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> compute_complex_matrix_product(array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> lhs, array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> rhs) {
    
    long m = 128; //Zm*
    long r = 20;  //bit precision
    long L = 150; //number of bits for the mod chain
    
    // Setting up the context. p needs to be -1 for CKKS.
    auto context = Context(m, -1, r);
    // We need to change the scale of the internally used distribution.
    context.scale = 4;
    // Build modulus chain
    helib::buildModChain(context, L, 2);
    //Initialize secret key
    auto secretKey = SecKey(context);
    // Generate secret key
    secretKey.GenSecKey();
    // We need to generate some internal matrices for the ckks scheme.
    helib::addSome1DMatrices(secretKey);
    // Obtain the secret key
    auto pubKey = PubKey(secretKey);
    
    // Obtain encrypted array, Cx variant is specifically for approximate numbers.
    auto encryptedArray = context.ea->getCx();
    
    
    // Encrypt our float values as complex number into our ciphertext
    vector<vector<Ctxt>> lhs_ctxts, rhs_ctxts, result_ctxt;
    
    Ctxt zero(pubKey);
    vector<complex<double>> zerov = { complex<double>() };
    encryptedArray.encrypt(zero, pubKey, zerov);
    
    //Encrypt the values into vectors of ctxt's.
    //Left hand side
    for (auto& row : lhs) {
        vector<Ctxt> new_row;
        for (auto& elem : row) {
            auto ctxt = Ctxt(pubKey);
            vector<complex<double>> v = {elem};
            encryptedArray.encrypt(ctxt, pubKey, v);
            new_row.emplace_back(ctxt);
        }
        lhs_ctxts.emplace_back(new_row);
    }
    //Right hand side
    for (auto& row : rhs) {
        vector<Ctxt> new_row;
        for (auto& elem : row) {
            auto ctxt = Ctxt(pubKey);
            vector<complex<double>> v = {elem};
            encryptedArray.encrypt(ctxt, pubKey, v);
            new_row.emplace_back(ctxt);
        }
        rhs_ctxts.emplace_back(new_row);
    }
    
    // Intialize resulting ctxts with empty
    for (const auto& row : lhs) {
        vector<Ctxt> new_row;
        for (const auto& _ : row) {
            new_row.emplace_back(zero);
        }
        
        result_ctxt.emplace_back(new_row);
    }
    
    // Computing the dot product
    for (size_t x = 0; x < MATRIX_SIZE; x++) {
        for (size_t y = 0; y < MATRIX_SIZE; y++) {
            
            result_ctxt[x][y] = zero;
            for (size_t z = 0; z < MATRIX_SIZE; z++) {
                auto temp = Ctxt(lhs_ctxts[x][z]);
                temp *= rhs_ctxts[z][y];
                result_ctxt[x][y] +=  temp;
            }
        }
    }
    
  
    // Decryption
    array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> return_value = {};
    
    for (size_t i = 0; i < result_ctxt.size(); ++i) {
        auto& row = result_ctxt[i];
        for (size_t j = 0; j < row.size(); ++j) {
            vector<complex<double>> result;
            encryptedArray.decrypt(row[j], secretKey, result);
            return_value[i][j] = result[0];
        }
        
    }
    
    return return_value;
}
