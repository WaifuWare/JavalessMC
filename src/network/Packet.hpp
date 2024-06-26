//
// Created by taxis on 2024-04-22.
//

#ifndef JAVALESSMC_PACKET_HPP
#define JAVALESSMC_PACKET_HPP

#include <cstdint>
#include <string>
#include <vector>

#include "../utils/uuid.h"
#include "structs.hpp"

class MinecraftPacket {
public:
    MinecraftPacket();
    explicit MinecraftPacket(std::vector<char> buffer);
    ~MinecraftPacket();
    void write_varint(uint32_t value);
    void write_string(const std::string& value);
    void write_identifier(const std::string& value);
    void write_short(uint16_t value);
    void write_long(uint64_t value);
    void write_byte(int8_t value);
    void write_ubyte(uint8_t value);
    void write_bool(bool value);
    void write_buffer(const char* buffer, size_t len);
    void write_UUID(uuids::uuid UUID);
    void write_position(Position pos);
    void write_array(char** values);
    [[nodiscard]] char* getBuffer();
    [[nodiscard]] std::fstream getBufferStream();
    [[nodiscard]] size_t size() const;
    void printHex() const;

private:
    std::vector<char> buffer;
};

#endif //JAVALESSMC_PACKET_HPP
