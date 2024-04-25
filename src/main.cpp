#include "events/impl/pluginLoadedEvent.hpp"
#include "loader.hpp"

#include "events/eventmanager.hpp"
#include "events/impl/updateEvent.hpp"
#include <ostream>

#include "network/authentication/auth.hpp"
#include "network/Socket.hpp"
#include "utils/Exceptions.hpp"

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
    /*
      EventManager::getInstance().registerEventManager(onTick);
      EventManager::getInstance().registerEventManager(onPluginLoad);
      initLoader();

      while (true) {
        EventManager::getInstance().fire(new UpdateEvent);
      }*/
    auto *sock = new Socket();
    try {
        sock->connect("off-bbs.gl.at.ply.gg", 29872);
        authenticate(sock);
    } catch (SocketException& exception) {
        std::cout << exception.what() << std::endl;
    }
    sock->disconnect();
    delete sock;
    return 0;
}
