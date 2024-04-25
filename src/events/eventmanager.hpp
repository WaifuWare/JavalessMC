#pragma once
#include <functional>
#include <vector>

class Event {
public:
  virtual ~Event() = default;
};

using EventHandler = std::function<void(Event *)>;

class EventManager {
public:
  static EventManager &getInstance() {
    static EventManager instance; // Static instance of EventManager
    return instance;
  }

  void registerEventManager(const EventHandler& handler) {
    handlers.push_back(handler);
  }

  void fire(Event *event) {
    for (auto &handler : handlers) {
      handler(event);
    }
    delete event;
  }

private:
  std::vector<EventHandler> handlers;
};
