//
// Created by taxis on 2024-04-25.
//

#include "aes_cfb.hpp"
#include "filters.h"
#include "osrng.h"

#include <aes.h>
#include <modes.h>

using CryptoPP::CFB_Mode;
using CryptoPP::AES;

/**
 * @brief Generates a random shared secret of 16 bytes
 * */
void generateSharedSecret(uint8_t *shared_secret) {
    CryptoPP::AutoSeededRandomPool rng;
    rng.GenerateBlock(shared_secret, sizeof(shared_secret));
}

std::string CFBMode_Encrypt(const std::string& text, uint8_t key[], int keySize, uint8_t iv[]) {
    std::string cipher;
    CFB_Mode<AES>::Encryption e;
    e.SetKeyWithIV(key, keySize, iv);
    auto *streamTrans = new CryptoPP::StreamTransformationFilter(e, new CryptoPP::StringSink(cipher));
    CryptoPP::StringSource s(text, true, streamTrans);
    return cipher;
}

std::string CFBMode_Decrypt(const std::string& cipher, uint8_t key[], int keySize, uint8_t iv[]) {
    std::string recovered;
    CFB_Mode< AES >::Decryption d;
    d.SetKeyWithIV(key, keySize, iv);
    auto* streamTrans = new CryptoPP::StreamTransformationFilter(d,new CryptoPP::StringSink(recovered));
    CryptoPP::StringSource s(cipher, true, streamTrans);
    return recovered;
}