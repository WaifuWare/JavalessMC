//
// Created by taxis on 2024-04-25.
//

#include "auth.hpp"

#include <iostream>
#include <base64.h>

#include "../impl/C2S/Login.hpp"
#include "aes_cfb.hpp"

void authenticate(Socket* sock) {
    auto handshake = Packet::Handshake(721, sock->get_ip().c_str(), sock->get_port(), HandshakeNextState::Login);
    auto login_start = Packet::LoginStart("DropkickTheChild", "64a7dada-b6d4-433d-9b80-3c96f91ed370");

    sock->send(handshake, sizeof(handshake));

    sock->send(login_start, sizeof(login_start));

    int packet_size = sock->recv_varint();
    std::cout << "Packet size: " << std::to_string(packet_size) << std::endl;
    int serverIDLength = sock->recv_varint();
    std::cout << "Server ID Length: " << std::to_string(serverIDLength) << std::endl;
    const char* serverID = sock->recv_string(serverIDLength);
    std::cout << "Server ID: " << serverID << std::endl;

    int public_key_length = sock->recv_varint();
    const char* public_key = sock->recv_string(public_key_length);
    std::cout << "Public Key Length: " << std::to_string(public_key_length) << std::endl;

    int verify_token_length = sock->recv_varint();
    const char* verify_token = sock->recv_string(verify_token_length);
    std::cout << "Verify token length: " << std::to_string(verify_token_length) << std::endl;

    std::string encoded;
    auto* encoder = new CryptoPP::Base64Encoder(new CryptoPP::StringSink(encoded));
    CryptoPP::StringSource stringSource(public_key, true, encoder);
    std::string pem_pubkey = "-----BEGIN PUBLIC KEY-----\n";
    pem_pubkey += encoded + "\n";
    pem_pubkey += "-----END PUBLIC KEY-----";

    uint8_t shared_secret[16];
    generateSharedSecret(shared_secret);

    auto encryption_response = Packet::EncryptionResponse(sizeof(shared_secret), reinterpret_cast<char *>(shared_secret),
                                                          sizeof(verify_token), const_cast<char *>(verify_token));
    sock->send(encryption_response, sizeof(encryption_response));


}