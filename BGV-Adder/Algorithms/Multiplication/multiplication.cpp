//
//  multiplication.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 21/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include <NTL/BasicThreadPool.h>
#include "multiplication.hpp"
#include "base_context.hpp"
#include <helib/binaryArith.h>
#include <helib/intraSlot.h>

using std::vector;
using helib::Ctxt;
using helib::CtPtrs_vectorCt;

long compute_bgv_multiply(uint16_t a, uint16_t b) {
    std::cout << "Input: " << a << ", " << b << std::endl;
    
    NTL::SetNumThreads(NTL::AvailableThreads());
    auto context = PreparedContext();
    
    long bitSize = 16;
    long outSize = 2 * bitSize;

    // Create scratch ciphertexts
    Ctxt scratch(context.public_key());
    std::vector<helib::Ctxt> encrypted_a(bitSize, scratch);
    std::vector<helib::Ctxt> encrypted_b(bitSize, scratch);
    std::vector<helib::Ctxt> encrypted_c(bitSize, scratch);
    
    for (long i = 0; i < bitSize; ++i) {
      std::vector<long> a_vec(context.encrypted_array().size());
      std::vector<long> b_vec(context.encrypted_array().size());
      std::vector<long> c_vec(context.encrypted_array().size());
      // Extract the i'th bit of a and b.
      // We can compute with 3 numbers, but we only have two.
      // Set C to 1.
      for (auto& slot : a_vec)
        slot = ((long(a)) >> i) & 1;
      for (auto& slot : b_vec)
        slot = ((long(b)) >> i) & 1;
      for (auto& slot : c_vec)
        slot = ((long(1)) >> i) & 1;
        context.encrypted_array().encrypt(encrypted_a[i], context.public_key(), a_vec);
        context.encrypted_array().encrypt(encrypted_b[i], context.public_key(), b_vec);
        context.encrypted_array().encrypt(encrypted_c[i], context.public_key(), c_vec);
    }
    
    // Multiply the encrypted numbers
    vector<helib::Ctxt> encrypted_product;
    CtPtrs_vectorCt product_wrapper(encrypted_product);
    helib::multTwoNumbers(
      product_wrapper,
      CtPtrs_vectorCt(encrypted_a),
      CtPtrs_vectorCt(encrypted_b),
      false, // Only positive
      outSize,
      &context.unpack_slot_encoding);
    
    vector<long> decrypted_result;
    // Decrypt them
    helib::decryptBinaryNums(decrypted_result, product_wrapper, context.secret_key, context.encrypted_array());
    
    auto result = decrypted_result.back();
    std::cout << "FHE Result: " << result << std::endl;
    std::cout << "Actual: " << a * b << std::endl;
    return result;
}
