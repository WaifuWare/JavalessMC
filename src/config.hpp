#pragma once

#include <iostream>
#include <fstream>

#include "utils/logger.hpp"

/**
 * @fixme : config break when reading / writting char* to struct
*/
struct Config
{
    std::string username;
    std::string password;

    std::string ip;
    bool autoconnect;

    int maxfps = 60;
} config;

bool loadData() {
    std::ifstream f("saved.data", std::ios::binary);

    if (!f.is_open())
    {
        logError("could not read save file");
        return 0;
    }

    f.read((char *)&config, sizeof(Config));

    f.close();

    return 1;
}

bool saveData() {
    std::ofstream f("saved.data", std::ios::binary);

    if(!f.is_open())
    {
        return 0;
    }

    f.write((char *)&config, sizeof(Config));

    f.close();

    return 1;
}