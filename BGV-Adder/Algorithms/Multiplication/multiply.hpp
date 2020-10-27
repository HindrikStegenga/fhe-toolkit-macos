//
//  multiply.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef multiply_hpp
#define multiply_hpp

#include <stdio.h>
#include <helib/FHE.h>
#include <array>
#include <stdint.h>

using std::array;
typedef int16_t i16;

long compute_multiplication(i16 lhs, i16 rhs);

#endif /* multiply_hpp */
