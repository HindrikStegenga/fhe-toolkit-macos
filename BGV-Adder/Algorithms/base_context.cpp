//
//  base_context.cpp
//  BGV-Adder
//
//  Created by Hindrik Stegenga on 21/10/2020.
//  Copyright © 2020 RUG. All rights reserved.
//

#include "base_context.hpp"
#include <helib/binaryArith.h>
#include <helib/intraSlot.h>

using std::cout;
using std::endl;
using helib::convert;
using helib::PubKey;
using helib::EncryptedArray;

BaseContext::BaseContext() : context(
                                     Context(this->m, this->p, this->r, this->generators, this->orders)) {
    cout << "Generating modulus chain..." << endl;
    buildModChain(this->context, this->modulus_bits, this->c);
    cout << "Making bootstrappable..." << endl;
    context.makeBootstrappable(
                               convert<NTL::Vec<long>, vector<long>>(mvec));
    context.zMStar.printout();
    cout << endl;
    cout << "Security: " << context.securityLevel() << endl;
    cout << "Creating secret key..." << endl;
}

PreparedContext::PreparedContext() : secret_key(helib::SecKey(this->context)) {
    cout << "Generating bootrstrapping data.." << endl;
    secret_key.genRecryptData();
    cout << "Building unpack slot encoding..." << endl;
    buildUnpackSlotEncoding(this->unpack_slot_encoding, this->encrypted_array());
    cout << "Number of slots: " << this->encrypted_array().size() << endl;
}


const PubKey& PreparedContext::public_key() {
    return static_cast<const PubKey&>(this->secret_key);
}

const EncryptedArray& PreparedContext::encrypted_array() {
    return static_cast<const EncryptedArray&>(*(this->context.ea));
}
