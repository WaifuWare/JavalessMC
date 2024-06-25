#pragma once
#include "../eventmanager.hpp"

#include <cstring>

class ProcessCommandEvent : public Event {
    public:
        ProcessCommandEvent(char *name, char *argsv[]) : command(name) {
            int numArgs = countArgs(argsv);
            args = new char *[numArgs + 1];
            for (int i = 0; i < numArgs; ++i) {
                args[i] = strdup(argsv[i]);
            }
            args[numArgs] = nullptr;
        }

        ~ProcessCommandEvent() {
            for (int i = 0; args[i] != nullptr; ++i) {
                free(args[i]);
            }
            delete [] args;
        }

        char *getCommand() {
            return command;
        }

        char **getArgs() {
            return args;
        }

    private:
        char *command;
        char **args;

        int countArgs(char *argsv[]) {
            int count = 0;
            while (argsv[count] != nullptr) {
                count++;
            }
            return count;
        }
};