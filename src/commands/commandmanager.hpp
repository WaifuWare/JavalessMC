#pragma once

#include "../events/eventmanager.hpp"
#include "../events/impl/processCommandEvent.hpp"
#include <vector>
#include <iostream>
#include "../utils/logger.hpp"

class Command {
    public:
        virtual void execute(char **args) = 0;
        virtual char *getName() = 0;
        virtual ~Command() = default;
};

std::vector<Command *> commandList;

class CommandManager {
    public:
        static CommandManager *getInstance() {
            CommandManager *manager;
            return manager;
        }

        void addCommand(Command *instance) {
            log("added new command " + std::string(instance->getName()) + " to command registry");
            commandList.push_back(instance);
        }

        void init() {
            EventManager::getInstance().registerEventListener(processCommand);
        }

        static void processCommand(Event *event) {
            if (auto *e = dynamic_cast<ProcessCommandEvent *>(event)) {
                for (int i = 0; i < commandList.size(); i++) {
                    if (e->getCommand() == commandList.at(i)->getName()) {
                        commandList.at(i)->execute(e->getArgs());
                    }
                }
            }
        }
};