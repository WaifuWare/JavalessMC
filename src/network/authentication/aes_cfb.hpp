//
// Created by taxis on 2024-04-25.
//

#ifndef JAVALESSMC_AES_CFB_HPP
#define JAVALESSMC_AES_CFB_HPP

#include <string>
#include <aes.h>

void generateSharedSecret(uint8_t *shared_secret);
std::string CFBMode_Encrypt(const std::string& text, uint8_t key[], int keySize, uint8_t iv[]);
std::string CFBMode_Decrypt(const std::string& cipher, uint8_t key[], int keySize, uint8_t iv[]);

#endif //JAVALESSMC_AES_CFB_HPP
