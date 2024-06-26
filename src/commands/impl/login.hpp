#pragma once

#include "../commandmanager.hpp"
#include "../../utils/stringutil.hpp"
#include "../../utils/logger.hpp"
#include <cstddef>
#include <string>

#include "../../config.hpp"

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

        config.username = std::string(username);
        config.password = std::string(password);

#if 0
        log("Argument passed :");
        log("Test. username : " + std::string(username) + ", password : " + std::string(password));
        log("Data saved to config struct :");
        log("Test. username : " + std::string(config.username) + ", password : " + std::string(config.password));
#endif
    }

    char *getName() override {
        return "login";
    }
};