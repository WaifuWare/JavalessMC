//
// Created by taxis on 2024-04-23.
//

#include "Socket.hpp"

#include <cstring>

#include "../utils/Exceptions.hpp"
#include "structs.hpp"

#ifdef _WIN32
    #include "../utils/win32stuff.hpp"
#else
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <fcntl.h>
    #include <cerrno>
#endif

Socket::Socket() : m_packet_queue(0) {
    this->err_buffer = new char[256];
#ifdef WIN32
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        DWORD errorId = WSAGetLastError();
        sprintf(this->err_buffer, "Could not initialize Winsock: %s", GetLastErrorString(errorId).c_str());
        throw SocketException(this->err_buffer);
    }
    this->socket = ::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (this->socket == INVALID_SOCKET) {
        WSACleanup();
        DWORD errorId = WSAGetLastError();
        sprintf(this->err_buffer, "Could not create socket: %s", GetLastErrorString(errorId).c_str());
        throw SocketException(this->err_buffer);
    }
#else
    this->socket = ::socket(AF_INET, SOCK_STREAM, 0);
    if (this->socket < 0) {
        sprintf(err_buffer, "Could not create socket. %s (%d)", strerror(errno), errno);
        throw SocketException(err_buffer);
    }
    const int flags = fcntl(this->socket, F_GETFL, 0);
    fcntl(this->socket, F_SETFL, flags | O_NONBLOCK);
    setsockopt(this->socket, SOL_SOCKET, SO_SNDTIMEO, &this->timeout, sizeof(this->timeout));
#endif
}

Socket::~Socket() {
#ifdef _WIN32
    closesocket(this->socket);
    WSACleanup();
#else
    close(this->socket);
#endif
    delete[] this->err_buffer;
}

void Socket::connect(const std::string& ip, const int port) const {
    sockaddr_in server{};
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(port);

    if (::connect(this->socket, reinterpret_cast<sockaddr*>(&server), sizeof(server)) == -1) {
#ifdef _WIN32
        DWORD errorId = WSAGetLastError();
        sprintf(this->err_buffer, "Could not connect to %s:%d. %s", ip.c_str(), port, GetLastErrorString(errorId).c_str());
#else
        sprintf(this->err_buffer, "Could not connect to %s:%d. %s (%d)", ip.c_str(), port, strerror(errno), errno);
#endif
        throw SocketException(this->err_buffer);
    }
}

void Socket::disconnect() const {
#ifdef _WIN32
    closesocket(this->socket);
#else
    close(this->socket);
#endif
}

void Socket::send(const char* buffer, const size_t len) const {
    if (::send(this->socket, buffer, len, 0) == -1) {
#ifdef _WIN32
        DWORD errorId = WSAGetLastError();
        sprintf(this->err_buffer, "Could not send data. %s", GetLastErrorString(errorId).c_str());
#else
        sprintf(this->err_buffer, "Could not send data. %s (%d)", strerror(errno), errno);
#endif
        throw SocketException(this->err_buffer);
    }
}

size_t Socket::receive(char* buffer, const size_t len) const {
    const size_t res = ::recv(this->socket, buffer, len, 0);
    if (res == -1) {
#ifdef _WIN32
        DWORD errorId = WSAGetLastError();
        sprintf(this->err_buffer, "Could not receive data. %s", GetLastErrorString(errorId).c_str());
#else
        sprintf(this->err_buffer, "Could not receive data. %s (%d)", strerror(errno), errno);
#endif
        throw SocketException(this->err_buffer);
    }
    return res;
}

int Socket::recv_varint() const {
    int numRead = 0;
    int result = 0;
    char read;
    do {
        this->receive(&read, 1);
        const int value = (read & 0b01111111);
        result |= (value << (7 * numRead));

        numRead++;
        if (numRead > 5) {
            throw SocketException("VarInt too big");
        }
    } while ((read & 0b10000000) != 0);

    return result;
}

uint8_t Socket::recv_byte() const {
    uint8_t value;
    this->receive(reinterpret_cast<char*>(&value), 1);
    return value;
}

int64_t Socket::recv_varlong() const {
    int64_t value = 0;
    int position = 0;
    uint8_t current_byte;

    while (true) {
        current_byte = this->recv_byte();
        value |= (current_byte & SEGMENT_BITS) << position;

        if ((current_byte & SEGMENT_CONTINUATION_BIT) == 0) break;

        position += 7;

        if (position >= 64) {
            throw SocketException("VarLong too big");
        }
    }
    return value;
}

char *Socket::recv_string(int length) const {
    char* buffer = new char[length];
    this->receive(buffer, length);
    return buffer;
}

int16_t Socket::recv_short() const {
    int16_t value;
    this->receive(reinterpret_cast<char*>(&value), 2);
    return value;
}

uuids::uuid Socket::recv_UUID() const {
    __uint128_t mostSigBits = 0;
    __uint128_t leastSigBits = 0;
    for (int i = 0; i < 8; i++) {
        mostSigBits |= (this->recv_byte() & 0xFF) << (8 * i);
    }
    for (int i = 0; i < 8; i++) {
        leastSigBits |= (this->recv_byte() & 0xFF) << (8 * i);
    }
    std::array<uint8_t, 16> bytes{};
    for (int i = 0; i < 8; i++) {
        bytes[i] = (mostSigBits >> ((7 - i) * 8)) & 0xFF;
    }
    for (int i = 0; i < 8; i++) {
        bytes[i + 8] = (leastSigBits >> ((7 - i) * 8)) & 0xFF;
    }
    auto uuid = uuids::uuid(bytes);
    if (!uuid.is_nil()) {
        return uuid;
    }
    return uuid;
}

uint16_t Socket::recv_ushort() const {
    uint16_t value;
    this->receive(reinterpret_cast<char*>(&value), 2);
    return value;
}

Position Socket::recv_position() const {
    int64_t val = recv_varlong();
    Position pos{};
    pos.x = val >> 38;
    pos.y = val << 52 >> 52;
    pos.z = val << 26 >> 38;
    return pos;
}

std::string Socket::get_ip() const {
    return this->m_ip;
}

int Socket::get_port() const {
    return this->m_port;
}

void Socket::updatePacketQueue() {
    this->m_packet_queue.load();
}
