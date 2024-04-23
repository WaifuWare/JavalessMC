//
// Created by TaxMachine on 2024-04-22.
//

#ifndef JAVALESSMC_LOGIN_HPP
#define JAVALESSMC_LOGIN_HPP

#include "../../Packet.hpp"
#include "../../../utils/uuid.h"
#include "../../../utils/Exceptions.hpp"

enum HandshakeNextState {
    Status = 1,
    Login
};

char* Handshake(int protocol_version, const char* ip, uint16_t port, HandshakeNextState next_state) {
    MinecraftPacket packet{};
    packet.write_varint(0x00);
    packet.write_varint(protocol_version);
    packet.write_string(ip);
    packet.write_short(port);
    packet.write_varint((int)next_state);
    return packet.getBuffer();
}

char* StatusRequest() {
    MinecraftPacket packet{};
    packet.write_varint(0x00);
    return packet.getBuffer();
}

char* PingRequest(uint64_t payload) {
    MinecraftPacket packet{};
    packet.write_varint(0x01);
    packet.write_long(payload);
    return packet.getBuffer();
}

char* LoginStart(const char* name, const char* UUID) {
    MinecraftPacket packet{};
    auto id = uuids::uuid::from_string(UUID);
    if (!id.has_value()) {
        throw MinecraftException("Invalid UUID");
    }
    packet.write_varint(0x00);
    packet.write_string(name);
    packet.write_UUID(id.value());
    return packet.getBuffer();
}

char* EncryptionResponse(int shared_secret_length, char* shared_secret, int verify_token_length, char* verify_token) {
    MinecraftPacket packet{};
    packet.write_varint(0x01);
    packet.write_varint(shared_secret_length);
    packet.write_buffer(shared_secret, shared_secret_length);
    packet.write_varint(verify_token_length);
    packet.write_buffer(verify_token, verify_token_length);
    return packet.getBuffer();
}

char* LoginPluginResponse(int messageId, bool successful, char* data = nullptr) {
    MinecraftPacket packet{};
    packet.write_varint(0x02);
    packet.write_varint(messageId);
    packet.write_bool(successful);
    if (data != nullptr) {
        packet.write_buffer(data, sizeof(data));
    }
    return packet.getBuffer();
}

char* LoginAcknowledged() {
    MinecraftPacket packet{};
    packet.write_varint(0x03);
    return packet.getBuffer();
}

#endif //JAVALESSMC_LOGIN_HPP