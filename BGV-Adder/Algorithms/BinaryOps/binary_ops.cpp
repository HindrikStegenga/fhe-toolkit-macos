//
//  binary_ops.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 27/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "binary_ops.hpp"
#include <vector>
#include <array>
#include <helib/helib.h>
#include <helib/FHE.h>

using helib::Ctxt;
using helib::Context;
using std::vector;
using std::array;

bool compare_binary_numbers(array<bool, BIN_OPS_NR_BITS> lhs, array<bool, BIN_OPS_NR_BITS> rhs) {
    
    // Parameters(1, 5, false, 0, 1)
    //
    const long bitsize = BIN_OPS_NR_BITS; // Size in bits of inputs
    bool bootstrap = false;
    
          // { p, phi(m),   m,   d,  m1, m2,  m3,    g1,  g2,  g3, ord1,ord2,ord3, B,  c}
          // {2, 48,       105,  12, 3,  35,  0,     71,  76,  0,  2,    2,   0,   25, 2},
          // {2, 600,      1023, 10, 11, 93,  0,    838,  584, 0,  10,   6,   0,   25, 2},
    long p = 2;
    long phi = 600;
    long m = 1023;
    long d = 10;
    
    // Factorization for bootstrapping process
    vector<long> mvec = { 11, 93, 0 };
    
    // Generators for ZM* group
    vector<long> generators = { 838, 584, 0 };
    
    // Orders of the generators
    vector<long> orders = { 10, 6, 0 };
    
    // Number of levels in mod chain. Depends on bootstrapping.
    // If no bootstrap we just compute a large number which should be big enough.
    long L = bootstrap ? 900 : 30 * (7 + NTL::NumBits(bitsize + 2));
    // Key switch matrix columns
    long c = 2;
    // Hensel
    long r = 1;
    
    // Instantiate context
    Context context = Context(m, p, r);
    
    // Set up mod chain
    buildModChain(context, L, c, bootstrap);
    
    // Bootstrap if enabled
    if (bootstrap) {
        context.makeBootstrappable(helib::convert<NTL::Vec<long>, vector<long>>(mvec), 0);
    }
    
}
