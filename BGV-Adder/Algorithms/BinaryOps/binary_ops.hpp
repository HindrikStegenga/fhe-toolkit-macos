//
//  binary_ops.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef binary_ops_hpp
#define binary_ops_hpp

#include <stdio.h>
#include <array>

using std::array;

static const size_t BIN_OPS_NR_BITS = 5;


std::pair<long,long> compare_binary_numbers(array<bool, BIN_OPS_NR_BITS> lhs, array<bool, BIN_OPS_NR_BITS> rhs, bool bootstrap = false);

#endif /* binary_ops_hpp */
