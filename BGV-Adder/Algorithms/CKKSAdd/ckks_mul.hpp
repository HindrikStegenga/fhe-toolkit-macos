//
//  ckks_mul.hpp
//
//  Created by Rishabh Sawhney .
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef ckks_mul_hpp
#define ckks_mul_hpp

#include <stdio.h>
#include <helib/helib.h>

double calcMaxDiff(const std::vector<std::complex<double>>& v1,
                   const std::vector<std::complex<double>>& v2);

double ckks_mul_doubles(double a,double ai, double b,double bi);

#endif /* ckks_mul_hpp */
