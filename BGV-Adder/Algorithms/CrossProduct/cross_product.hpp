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
typedef uint16_t u16;

array<u16, 3> compute_cross_product(array<u16, 3> lhs, array<u16, 3> rhs);

#endif /* cross_product_hpp */
