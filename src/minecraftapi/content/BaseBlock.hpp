#pragma once

#include <iostream>
#include <string>

#include "../utils/vectors.h"

struct blockData {
    float hardness;
    bool solid;
    Vector3I position;
    std::string identifier;
};