#include "ckks_rotation.hpp"
#include <complex>
#include <helib/helib.h>
#include <helib/norms.h>

using helib::Context;
using helib::Ctxt;
using helib::SecKey;
using helib::PubKey;
using std::vector;
using std::complex;

void rotate(std::vector<std::complex<double>>& rotVec, long amt)
{
  long sz = rotVec.size();
  std::vector<std::complex<double>> tmp(sz);
  for (long i = 0; i < sz; i++)
    tmp[((i + amt) % sz + sz) % sz] = rotVec[i];
    rotVec = tmp;
    
 }

 std::complex<double> ckks_rotation(double a,double ai,long amount) {
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
   
    helib::Ctxt c1(pubKey);
    vector<complex<double>> vd1 = { complex<double>(a,ai) };
    
    std::vector<std::complex<double>> vd2,vd3;
    NTL::xdouble rf, pm;
    NTL::ZZX poly;

    //Initializing the values
    
    encryptedArray.encrypt(c1, pubKey, vd1);
    pm = c1.getPtxtMag();
    encryptedArray.encode(poly, vd1, /*size=*/1.0);
    
    //Rotating the encrypted vector
    encryptedArray.rotate(c1, amount);

    //Decrypting the cipher using the secretKey
    encryptedArray.decrypt(c1, secretKey, vd2);
    
    std::cout<<"Value when performed on encrypted data when rotated by "<<amount<<": "<<double(vd2[0].real())<<" +i"<<double(vd2[0].imag())<<std::endl;
    double result_real = double(vd2[0].real());
    double result_imag = double(vd2[0].imag());
    return std::complex<double>(result_real,result_imag);
 }
