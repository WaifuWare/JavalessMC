#pragma once

#include "BaseBlock.hpp"
#include "../utils/nbt.h"

struct BlockEntityData {
    blockData data;
    NBTTag tags;
};