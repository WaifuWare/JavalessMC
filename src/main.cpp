#include "events/impl/pluginLoadedEvent.hpp"
#include "loader.hpp"

#include "events/eventmanager.hpp"
#include "events/impl/updateEvent.hpp"
#include <ostream>

void onTick(Event *event) {
  if (auto *e = dynamic_cast<UpdateEvent *>(event)) {
  }
}

void onPluginLoad(Event *event) {
  if (auto *e = dynamic_cast<LoadedPluginEvent *>(event)) {
    std::cout << "loaded plugin " << e->getName() << std::endl;
  }
}

int main() {
  EventManager::getInstance().registerEventManager(onTick);
  EventManager::getInstance().registerEventManager(onPluginLoad);
  initLoader();

  while (true) {
    EventManager::getInstance().fire(new UpdateEvent);
  }

  return 0;
}
