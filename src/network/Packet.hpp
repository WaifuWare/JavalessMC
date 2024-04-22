//
// Created by taxis on 2024-04-22.
//

#ifndef JAVALESSMC_PACKET_HPP
#define JAVALESSMC_PACKET_HPP

#include <cstdint>
#include <string>
#include <vector>

#define SEGMENT_BITS 0x7F
#define SEGMENT_CONTINUATION_BIT 0x80

class MinecraftPacket {
public:
    MinecraftPacket();
    explicit MinecraftPacket(std::vector<char> buffer);
    ~MinecraftPacket();
    void write_varint(uint32_t value);
    void write_string(const std::string& value);
    void write_short(uint16_t value);
    void write_long(uint64_t value);
    void write_buffer(const char* buffer, size_t len);
    [[nodiscard]] char* getBuffer() const;
    [[nodiscard]] std::fstream getBufferStream() const;
    [[nodiscard]] size_t size() const;
    void printHex() const;

private:
    std::vector<char> buffer;
};

#endif //JAVALESSMC_PACKET_HPP
