
//
//  ckks_mul.cpp
//  ckks-Multiplier
//
//  Created by Rishabh Sawhney.
//  Copyright © 2020 RUG. All rights reserved.
//
#include "ckks_mul.hpp"
#include <complex>
#include <helib/helib.h>
#include <helib/norms.h>

using helib::Context;
using helib::Ctxt;
using helib::SecKey;
using helib::PubKey;
using std::vector;
using std::complex;

std::complex<double> ckks_mul_complex(double a,double ai,double b,double bi) {
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
    vector<complex<double>> vd1 = { complex<double>(a,ai) };
    vector<complex<double>> vd2 = { complex<double>(b,bi) };

    
    helib::Ctxt c1(pubKey), c2(pubKey);
    
    //Encrypt the values
    encryptedArray.encrypt(c1, pubKey, vd1);
    encryptedArray.encrypt(c2, pubKey, vd2);
    c1 *= c2;
  
    // Decryption
     
    vector<complex<double>> result = {};
    encryptedArray.decrypt(c1, secretKey, result);
    
    // Retrieve the result back as double. 
    double return_value_real = result[0].real();
    double return_value_imag = result[0].imag();
    
    //Displaying the encrypted and decrypted values
    std::cout << "Result: " << return_value_real<<" + " << return_value_imag << "i" << std::endl;
    
    return std::complex<double>(return_value_real, return_value_imag);
}



