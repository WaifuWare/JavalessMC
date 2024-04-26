#pragma once

#include <iostream>

#include "../commandmanager.hpp"

class TestCommand : public Command {
    void execute(char **args) override {
        std::cout << "[+] Hello World ! " << std::endl;
    }

    char *getName() override {
        return "test";
    }
};