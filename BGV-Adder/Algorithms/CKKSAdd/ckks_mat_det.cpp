//
//  ckks_mat_det.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 28/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "ckks_mat_det.hpp"
#include <complex>
#include <helib/norms.h>

using helib::Context;
using helib::Ctxt;
using helib::SecKey;
using helib::PubKey;
using std::vector;
using std::complex;

double ckks_mat_det_2x2(array<double, 4> mat){
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
    
    
    Ctxt a_Ctxt(pubKey), b_Ctxt(pubKey), c_Ctxt(pubKey), d_Ctxt(pubKey);
    // Encrypt our float values as complex number into our ciphertext
    vector<complex<double>> a_cpx = { complex<double>(mat[0]) };
    vector<complex<double>> b_cpx = { complex<double>(mat[1]) };
    vector<complex<double>> c_cpx = { complex<double>(mat[2]) };
    vector<complex<double>> d_cpx = { complex<double>(mat[3]) };
    
    encryptedArray.encrypt(a_Ctxt, pubKey, a_cpx);
    encryptedArray.encrypt(b_Ctxt, pubKey, b_cpx);
    encryptedArray.encrypt(c_Ctxt, pubKey, c_cpx);
    encryptedArray.encrypt(d_Ctxt, pubKey, d_cpx);
    
    // Perform the computation required to get the matrix determinant
    
    a_Ctxt *= d_Ctxt;
    b_Ctxt *= c_Ctxt;
    a_Ctxt -= b_Ctxt;
    // Decrypt it
    vector<complex<double>> result = {};
    encryptedArray.decrypt(a_Ctxt, secretKey, result);
    
    // Retrieve the result back as double. (In our case this is the real part since we ignore imaginary one)
    double return_value = result[0].real();
    
    std::cout << "Result: " << return_value << std::endl;
    
    return return_value;
}

double ckks_mat_det_3x3(array<double, 3> mat){
    
}
