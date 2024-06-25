#pragma once

#include <iostream>

#include "../commandmanager.hpp"
#include "../../utils/logger.hpp"

class TestCommand : public Command {
    void execute(char **args) override {
        log("From test command : Hello World !");
    }

    char *getName() override {
        return "test";
    }
};