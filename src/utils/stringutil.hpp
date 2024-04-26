#pragma once

#include <cstddef>

size_t getSize(char **a_char) {
    size_t size = 0;
    while (a_char[size] != nullptr) {
        size++;
    }
    return size;
}