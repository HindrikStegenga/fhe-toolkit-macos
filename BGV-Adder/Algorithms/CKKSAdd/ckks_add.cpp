//
//  ckks_add.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 26/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "ckks_add.hpp"
#include <complex>
#include <helib/norms.h>

using helib::Context;
using helib::Ctxt;
using helib::SecKey;
using helib::PubKey;
using std::vector;
using std::complex;

double ckks_add_doubles(double a, double b) {
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
    
    
    Ctxt lhsCtxt(pubKey), rhsCtxt(pubKey);
    // Encrypt our float values as complex number into our ciphertext
    vector<complex<double>> lhs_cx = { complex<double>(a) };
    vector<complex<double>> rhs_cx = { complex<double>(b) };
    encryptedArray.encrypt(lhsCtxt, pubKey, lhs_cx);
    encryptedArray.encrypt(rhsCtxt, pubKey, rhs_cx);
    
    // Perform addition
    lhsCtxt += rhsCtxt;
    
    // Decrypt them
    vector<complex<double>> result = {};
    encryptedArray.decrypt(lhsCtxt, secretKey, result);
    
    // Retrieve the result back as double. (In our case this is the real part since we ignore imaginary one)
    double return_value = result[0].real();
    
    std::cout << "Result: " << return_value << " Actual: " << a + b << std::endl;
    
    return return_value;
}


// Compute the L-infinity distance between two vectors
double calcMaxDiff(const vector<complex<double>>& v1,
                   const vector<complex<double>>& v2)
{
  if (helib::lsize(v1) != helib::lsize(v2)) {
    throw std::runtime_error("Vector sizes differ.");
  }

  double maxDiff = 0.0;
  for (long i = 0; i < helib::lsize(v1); i++) {
    double diffAbs = std::abs(v1[i] - v2[i]);
    if (diffAbs > maxDiff)
      maxDiff = diffAbs;
  }
  return maxDiff;
}
