//
//  ckks_add.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 26/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef ckks_add_hpp
#define ckks_add_hpp

#include <stdio.h>
#include <helib/helib.h>

double calcMaxDiff(const std::vector<std::complex<double>>& v1,
                   const std::vector<std::complex<double>>& v2);

double ckks_add_doubles(double a, double b);

#endif /* ckks_add_hpp */
