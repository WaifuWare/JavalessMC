#include "events/impl/pluginLoadedEvent.hpp"
#include "loader.hpp"

#include "events/eventmanager.hpp"
#include "events/impl/updateEvent.hpp"
#include "events/impl/processCommandEvent.hpp"

#include "commands/commandmanager.hpp"
#include "commands/impl/test.hpp"
#include "commands/impl/login.hpp"

#include "utils/logger.hpp"

#include <ostream>

#define DEBUG_MODE 0

/**
 * @brief main loop of the program
*/
void onTick(Event *event) {
    if (auto *e = dynamic_cast<UpdateEvent *>(event)) {
        // update command state here
        
        // end update command
    }
}

/**
    @brief manage the plugin load event, but for now it just print the name of the plugin
*/
void onPluginLoad(Event *event) {
    if (auto *e = dynamic_cast<LoadedPluginEvent *>(event)) {
        log(std::string("Loaded plugin ") + e->getName());
    }
}

int main() {
    EventManager::getInstance().registerEventManager(onTick);
    EventManager::getInstance().registerEventManager(onPluginLoad);

    CommandManager::getInstance()->init();
    CommandManager::getInstance()->addCommand(new TestCommand);
    CommandManager::getInstance()->addCommand(new Login);

    initLoader();

#if DEBUG_MODE
    // test logger
    log("test");
    logError("test error");

    // test command system without args
    EventManager::getInstance().fire(new ProcessCommandEvent("test", new char *[0]));

    // test command system with args
    EventManager::getInstance().fire(new ProcessCommandEvent("login", new char *[2] {"sbn", "1234"}));

    // by this point we dont want the rest of the program to execute.
    // @todo : write proper unit testing
    return 0;   
#else
    while (true) {
        EventManager::getInstance().fire(new UpdateEvent);
    }

    return 0;
#endif
}
