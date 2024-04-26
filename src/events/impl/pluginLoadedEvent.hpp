#pragma once
#include "../eventmanager.hpp"

class LoadedPluginEvent : public Event {
  public:
    LoadedPluginEvent(char *name) : name(name) {}

    char *getName() { return name; }

  private:
    char *name;
};
