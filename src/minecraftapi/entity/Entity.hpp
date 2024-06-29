#pragma once

#include <iostream>
#include <string>

#include "../utils/vectors.h"

#include "../content/BaseItem.hpp"

#include "../../events/eventmanager.hpp"

#define INVENTORY_SIZE 36

#define HELMET_SLOT 37
#define CHESTPLATE_SLOT 38
#define LEGGING_SLOT 39
#define BOOTS_SLOT 40

#define OFFHAND_SLOT 41

struct EntityData {
    int hp;
    std::string uuid;
    Vector3F position;
    Rotation rotation;
};

struct Inventory {
    ItemData items[INVENTORY_SIZE];

    ItemData helmet;
    ItemData chestplate;
    ItemData legging;
    ItemData boots;

    ItemData offhand;
};

bool isInHotbar(int slotId) {
    return slotId >= 0 && slotId <= 8;
}

enum GAMEMODE {
    SURVIVAL = 0,
    CREATIVE = 1,
    ADVENTURE = 2,
    SPECTATOR = 3
};

struct PlayerEntityData {
    std::string displayName;

    GAMEMODE gamemode;

    int latency;

    EntityData data;

    Inventory playerInventory;

    struct PlayerGameProfile {
        std::string uuid;
        std::string accountName;
        bool legacy;
    } gameProfile;

    struct PublicSession {
        std::string publicKey;
    } publicSession;
};

bool wasPlayerCreatedEventRegistered = false;

/**
 * This is a special case;
 * 
 * creating this class in its own event.hpp file would create a circular dependency between it and the entity.hpp file.
*/
class PlayerCreatedEvent : public Event {
    public:
        PlayerCreatedEvent(PlayerEntityData *data) : data(data) {}

        PlayerEntityData *getPlayerData() { return data; }

    private:
        PlayerEntityData *data;
};

void createPlayer(PlayerEntityData* data, const char rawdata[]) {

    

    if(data != nullptr)
        EventManager::getInstance().fire(new PlayerCreatedEvent(data));
}