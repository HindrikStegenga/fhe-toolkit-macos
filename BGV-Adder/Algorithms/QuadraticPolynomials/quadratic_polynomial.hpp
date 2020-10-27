//
//  quadratic_polynomial.hpp
//  BGV-Adder
//
//  Created by Andris on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef quadratic_polynomial_hpp
#define quadratic_polynomial_hpp

#include <stdio.h>
#include <helib/FHE.h>
#include <array>
#include <stdint.h>

using std::array;

long quadratic_polynomial(int16_t aVal, int16_t bVal, int16_t cVal, int16_t xVal);

#endif /* quadratic_polynomial_hpp */
