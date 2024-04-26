//
// Created by taxis on 2024-04-22.
//

#ifndef JAVALESSMC_EXCEPTIONS_HPP
#define JAVALESSMC_EXCEPTIONS_HPP
#include <stdexcept>

class MinecraftException final : public std::exception {
  public:
    explicit MinecraftException(const char *message) {
        this->message = message;
    }

    const char *what() {
        return this->message;
    }

  private:
    const char *message;
};

class SocketException final : public std::exception {
  public:
    explicit SocketException(const char *message) {
        this->message = message;
    }

    const char *what() {
        return this->message;
    }

  private:
    const char *message;
};

#endif //JAVALESSMC_EXCEPTIONS_HPP
