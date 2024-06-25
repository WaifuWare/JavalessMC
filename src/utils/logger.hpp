#pragma once
#include <string>
#include <iostream>
#include <spdlog/spdlog.h>

void log(std::string content) {
    spdlog::info(content.c_str());
//    std::cout << "\033[0;0m" << "[log] " << content << std::endl;
}

void logError(std::string content) {
    spdlog::error(content.c_str());
//  std::cout << "\033[0;31m" << "[error] " << content << "\033[0;0m" << std::endl;
}
