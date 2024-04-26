#pragma once
#include <string>
#include <iostream>

void log(std::string content) {
    std::cout << "\033[0;0m" << "[log] " << content << std::endl;
}

void logError(std::string content) {
    std::cout << "\033[0;31m" << "[error] " << content << "\033[0;0m" << std::endl;
}