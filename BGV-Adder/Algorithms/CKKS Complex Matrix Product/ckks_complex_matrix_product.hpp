//
//  ckks_complex_matrix_product.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 29/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef ckks_complex_matrix_product_hpp
#define ckks_complex_matrix_product_hpp

#include <stdio.h>
#include <helib/helib.h>
#include <array>
#include <complex>

using std::array;
using std::complex;

static const size_t MATRIX_SIZE = 3; //3x3 matrix


array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> compute_complex_matrix_product(array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> lhs, array<array<complex<double>, MATRIX_SIZE>, MATRIX_SIZE> rhs);

#endif /* ckks_complex_matrix_product_hpp */
