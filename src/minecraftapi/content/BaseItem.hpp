#pragma once

#include "../utils/nbt.h"

struct ItemData {
    int damage; // not the damage tag, but the durability left on an item
    int quantity;
    NBTTag tags;
    std::string identifier;
};