#pragma once

#include "../commandmanager.hpp"
#include "../../utils/stringutil.hpp"
#include "../../utils/logger.hpp"
#include <cstddef>
#include <string>

class Login : public Command {
public:
    void execute(char **args) override {
        size_t size = getSize(args);

        if(size != 2) {
            logError("Expected only 2 arguments, but got " + std::to_string(size) + " instead");
            return;
        }
        char* username = args[0];
        char* password = args[1];
        log("Test. username : " + std::string(username) + ", password : " + std::string(password));
    }

    char *getName() override {
        return "login";
    }
};