//
// Created by taxis on 2024-04-22.
//

#include "Packet.hpp"

#include <iomanip>
#include <iostream>
#include <fstream>
#include <algorithm>

#include "../utils/Exceptions.hpp"

MinecraftPacket::MinecraftPacket() {
    buffer.reserve(256);
}

MinecraftPacket::MinecraftPacket(std::vector<char> buffer) : buffer(std::move(buffer)) {}

MinecraftPacket::~MinecraftPacket() = default;

/**
 * @brief Variable-length signed 64-bit integer
 * */
void MinecraftPacket::write_long(const uint64_t value) {
    uint32_t remaining = value;
    for (int i = 0; i < 5; i++) {
        if ((remaining & ~(long)SEGMENT_BITS) == 0) {
            buffer.push_back(remaining);
            return;
        }
        buffer.push_back(remaining & (SEGMENT_BITS | SEGMENT_CONTINUATION_BIT));
        remaining >>= 7;
    }
}

/**
 * @brief Variable-length signed 16-bit integer
 * */
void MinecraftPacket::write_short(const uint16_t value) {
    buffer.push_back((value >> 8) & 0xFF);
    buffer.push_back(value & 0xFF);
}

/**
 * @brief Variable-length signed 32-bit integer
 * */
void MinecraftPacket::write_varint(uint32_t value) {
    uint32_t remaining = value;
    for (int i = 0; i < 5; i++) {
        if ((remaining & ~SEGMENT_BITS) == 0) {
            buffer.push_back(remaining);
            return;
        }
        buffer.push_back(remaining & (SEGMENT_BITS | SEGMENT_CONTINUATION_BIT));
        remaining >>= 7;
    }
    throw MinecraftException("VarInt too big");
}

std::vector<char> stringToBytes(const std::string& str) {
    std::vector<char> bytes;
    bytes.reserve(str.size());
    for (char c : str) {
        bytes.push_back(c);
    }
    return bytes;
}

/**
 * @brief UTF-8 string prefixed with its length as a VarInt
 * */
void MinecraftPacket::write_string(const std::string &value) {
    write_varint(value.size());
    std::vector<char> bytes = stringToBytes(value);
    buffer.insert(buffer.end(), bytes.begin(), bytes.end());
}

/**
 * @brief Data buffer/byte array
 * */
void MinecraftPacket::write_buffer(const char* buff, const size_t len) {
    this->buffer.insert(this->buffer.end(), buff, buff + len);
}

void MinecraftPacket::printHex() const {
    const char* p = buffer.data();
    size_t n = buffer.size();
    size_t i;

    for (i = 0; i < n; i++) {
        if (i % 16 == 0) {
            if (i > 0)
                std::cout << "\n";
            std::cout << std::hex << std::setw(8) << std::setfill('0') << i << " : ";
        }
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)(unsigned char)p[i] << " ";
    }

    if (i % 16 != 0)
        std::cout << "\n";
    std::cout << std::endl;
}

char* MinecraftPacket::getBuffer() {
    buffer.insert(buffer.begin(), buffer.size());
    auto* data = new char[buffer.size()];
    for (size_t i = 0; i < buffer.size(); i++) {
        data[i] = buffer[i];
    }
    return data;
}

std::fstream MinecraftPacket::getBufferStream() {
    std::fstream stream;
    stream.write(reinterpret_cast<const char *>(buffer.size()), 1);
    stream.write(buffer.data(), buffer.size());
    return stream;
}

size_t MinecraftPacket::size() const {
    return buffer.size();
}

/**
 * @brief Unsigned 128-bit number (2 unsigned longs in big-endian order)
 * */
void MinecraftPacket::write_UUID(uuids::uuid UUID) {
    auto bytes = UUID.as_bytes();
    __uint128_t uuid;
    std::memcpy(&uuid, bytes.data(), bytes.size());
    char* uuid_bytes = (char*)&uuid;
    buffer.insert(buffer.end(), uuid_bytes, uuid_bytes + 16);
}

/**
 * @brief Either false or true, encoded as 0x00 and 0x01
 * */
void MinecraftPacket::write_bool(bool value) {
    buffer.push_back(value ? 0x01 : 0x00);
}

/**
 * @brief Integer between -128 and 127. Signed 8-bit integer, two's complement
 * */
void MinecraftPacket::write_byte(int8_t value) {
    buffer.push_back(value);
}

/**
 * @brief Integer between 0 and 255. Unsigned 8-bit integer
 * */
void MinecraftPacket::write_ubyte(uint8_t value) {
    write_buffer((char*)&value, sizeof(value));
}

void MinecraftPacket::write_identifier(const std::string &value) {
    if (value.size() > 32767) {
        throw MinecraftException("Too large value for an identifier");
    }
    write_string(value);
}
