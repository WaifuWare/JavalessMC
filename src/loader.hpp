#ifndef JAVALESSMC_LOADER_HPP
#define JAVALESSMC_LOADER_HPP

#include <cstdlib>
#include <cstring>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include "utils/logger.hpp"

#ifdef _WIN32
#include "utils/win32stuff.hpp"
#include <windows.h>
#else
#include <dlfcn.h>
#endif

#include "events/eventmanager.hpp"
#include "events/impl/pluginLoadedEvent.hpp"

namespace fs = std::filesystem;

typedef int (*InitFunction)();

int loadPlugin(const char *name) {
#ifdef _WIN32
    HINSTANCE hProc = LoadLibrary(name);
    if (!hProc) {
        std::cerr << "Failed to open library: " << GetLastErrorString(GetLastError()) << std::endl;
        return 1;
    }
    auto initFunc = (InitFunction)GetProcAddress(hProc, "init");
    if (!initFunc) {
        std::cerr << "Failed to find symbol: " << GetLastErrorString(GetLastError()) << std::endl;
        FreeLibrary(hProc);
        return 1;
    }
    int result = initFunc();
    FreeLibrary(hProc);
    return result;
#else
    void *libHandle = dlopen(name, RTLD_LAZY);
    if (!libHandle) {
        logError(std::string("Failed to open library: ") + std::string(dlerror()));
        return 1;
    }

    // Get a pointer to the init function
    InitFunction initFunc = (InitFunction)dlsym(libHandle, "_Z4initv");
    if (!initFunc) {
        logError(std::string("Failed to find symbol: ") + std::string(dlerror()));
        dlclose(libHandle);
        return 1;
    }

    int result = initFunc();
    dlclose(libHandle);
    return result;
#endif
}

void initLoader() {
    if (!fs::exists("./plugins")) {
        logError(std::string("folder \"plugins\" does not exist, please create it"));
        return;
    }

    for (const auto &entry : std::filesystem::directory_iterator("./plugins")) {
        std::string path = "./plugins/";
        path += entry.path().filename().string();

        if (loadPlugin(path.c_str()) != 0) {
            logError(std::string("Failed to load the plugin ") + std::string(entry.path().filename()));
        } else {
            char *_name = (char *)malloc(strlen(path.c_str()) + 1);
            strcpy(_name, path.c_str());
            EventManager::getInstance().fire(new LoadedPluginEvent(_name));
            free(_name);
        }
    }
}

#endif // JAVALESSMC_LOADER_HPP
