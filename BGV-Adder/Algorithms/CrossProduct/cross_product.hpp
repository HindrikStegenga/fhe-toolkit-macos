//
//  cross_product.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 26/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef cross_product_hpp
#define cross_product_hpp

#include <stdio.h>
#include <helib/FHE.h>
#include <array>
#include <stdint.h>

using std::array;
typedef int16_t i16;
const static size_t CV_SIZE = 3;

array<long, CV_SIZE> compute_cross_product(array<i16, CV_SIZE> lhs, array<i16, CV_SIZE> rhs);

#endif /* cross_product_hpp */
