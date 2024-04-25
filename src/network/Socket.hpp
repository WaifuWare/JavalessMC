//
// Created by taxis on 2024-04-23.
//

#ifndef JAVALESSMC_SOCKET_HPP
#define JAVALESSMC_SOCKET_HPP

#include <string>
#include <atomic>
#include <vector>

#ifdef _WIN32
#include <winsock2.h>
#include <windows.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#include "../utils/uuid.h"
#include "structs.hpp"

class Socket {
public:
    Socket();
    ~Socket();
    void connect(const std::string& ip, int port) const;
    void disconnect() const;
    void send(const char* buffer, size_t len) const;
    size_t receive(char* buffer, size_t len) const;

    [[nodiscard]] std::string get_ip() const;
    [[nodiscard]] int get_port() const;

    [[nodiscard]] int32_t recv_varint() const;
    [[nodiscard]] int64_t recv_varlong() const;
    [[nodiscard]] char* recv_string(int length) const;
    [[nodiscard]] int16_t recv_short() const;
    [[nodiscard]] uuids::uuid recv_UUID() const;
    [[nodiscard]] uint16_t recv_ushort() const;
    [[nodiscard]] uint8_t recv_byte() const;
    [[nodiscard]] Position recv_position() const;

private:
    void updatePacketQueue();

    char* err_buffer;
#ifdef _WIN32
    SOCKET socket;
#else
    int socket;
#endif
    int m_port{};
    std::string m_ip;
    int timeout = 5000;
    std::vector<char*> m_packet_queue;
};

#endif //JAVALESSMC_SOCKET_HPP
