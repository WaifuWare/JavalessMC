#include <dlfcn.h> // Dynamic loading functions
#include <filesystem>
#include <iostream>
#include <string>

typedef int (*InitFunction)();

int loadPlugin(const char *name) {
  // Open the dynamic library
  void *libHandle = dlopen(name, RTLD_LAZY);
  if (!libHandle) {
    std::cerr << "Failed to open library: " << dlerror() << std::endl;
    return 1;
  }

  // Get a pointer to the init function
  InitFunction initFunc = (InitFunction)dlsym(libHandle, "_Z4initv");
  if (!initFunc) {
    std::cerr << "Failed to find symbol: " << dlerror() << std::endl;
    dlclose(libHandle);
    return 1;
  }

  int result = initFunc();
  dlclose(libHandle);

  return result;
}

void initLoader() {
  for (const auto &entry : std::filesystem::directory_iterator("./plugins")) {
    std::string path = "./plugins/";
    path += entry.path().filename();

    if (loadPlugin(path.c_str()) != 0) {
      std::cerr << "Failed to load the plugin " << entry.path().filename()
                << std::endl;
    } else {
      std::cout << "Loaded the plugin " << entry.path().filename() << std::endl;
    }
  }
}
