//
//  ckks_mat_det.hpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 28/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#ifndef ckks_mat_det_hpp
#define ckks_mat_det_hpp

#include <stdio.h>
#include <helib/helib.h>
#include <array>

using std::array;

double ckks_mat_det_2x2(array<double, 4> mat);
double ckks_mat_det_3x3(array<double, 9> mat);

#endif /* ckks_mat_det_hpp */
