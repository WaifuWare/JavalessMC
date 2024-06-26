#pragma once
#include <string>
#include <iostream>
#include <spdlog/spdlog.h>

#include "spdlog/sinks/stdout_color_sinks.h"

void log(std::string content) {
    spdlog::info(content.c_str());
//    std::cout << "\033[0;0m" << "[log] " << content << std::endl;
}

void logError(std::string content) {
    spdlog::error(content.c_str());
//  std::cout << "\033[0;31m" << "[error] " << content << "\033[0;0m" << std::endl;
}

#if DEBUG_MODE && RUN_TEST

auto console = spdlog::stdout_color_mt("Test");

void initTestConsole() {
    console.get()->set_pattern("[%H:%M:%S] [%^%n%$] %v");
}

void logTest(std::string content) {
    console.get()->info(content.c_str());
}

#endif