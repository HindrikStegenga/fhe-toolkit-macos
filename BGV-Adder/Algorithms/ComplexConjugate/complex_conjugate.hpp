//
//  complex_conjugate.hpp
//  BGV-Adder
//
//  Created by Andris on 28/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef complex_conjugate_hpp
#define complex_conjugate_hpp

#include <stdio.h>
#include <stdio.h>
#include <helib/FHE.h>
#include <array>
#include <stdint.h>
#include <NTL/ZZ.h>
#include <helib/helib.h>

const static size_t ARRAY_SIZE = 2;

std::array<long, ARRAY_SIZE> complex_conjugate(int16_t a, int16_t b);

#endif /* complex_conjugate_hpp */
