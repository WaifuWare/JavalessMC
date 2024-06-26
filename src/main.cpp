#include <spdlog/spdlog.h>
#include <ostream>

#include "events/impl/pluginLoadedEvent.hpp"
#include "loader.hpp"

#include "events/eventmanager.hpp"
#include "events/impl/updateEvent.hpp"
#include "events/impl/processCommandEvent.hpp"

#include "commands/commandmanager.hpp"

#if DEBUG_MODE && RUN_TEST
    #include "test.hpp"
#endif
#include "commands/impl/login.hpp"

#include "utils/logger.hpp"
#include "config.hpp"

#define boolToString(b) (b ? "true" : "false")

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

    spdlog::set_pattern("[%H:%M:%S] [%^%l%$] %v");

    bool loaded = loadData();

    EventManager::getInstance().registerEventListener(onTick);
    EventManager::getInstance().registerEventListener(onPluginLoad);

    CommandManager::getInstance()->init();
    CommandManager::getInstance()->addCommand(new Login);

#if DEBUG_MODE
    CommandManager::getInstance()->addCommand(new TestCommand);
#endif

    initLoader();

#if DEBUG_MODE && RUN_TEST
    test();
    return 0;   
#else

    while (true) {
        EventManager::getInstance().fire(new UpdateEvent);
    }

    return 0;
#endif
}
