# JavalessMC

### THIS PROJECT IS NOT ENDORSED, AFFILIATED, OR OTHERWISE APPROVED BY MOJANG STUDIOS AND/OR MICROSOFT. YOU NEED TO OWN A MINECRAFT ACCOUNT IN ORDER TO USE THIS PROJECT, AND IT DOES NOT ENABLE PIRACY BY ITSELF.

JavalessMC is a Minecraft headless instance that works in C++. Its goal is to provide a fast and memory-efficient Minecraft client library for multiple types of projects, from bots to fully fledged Minecraft clients.

*THIS TOOL IS A WORK IN PROGRESS AND MAY NOT WORK AS EXPECTED. PLEASE BE PATIENT UNTIL WE MAKE A WORKING SOLUTION!*

## Building

Run the `build.sh` batch file in the `scripts` folder. (or build.bat if on windows).

You'll need to have cmake installed, as well as a valid C++ compiler (gcc / clang are recommanded)

## Install Plugins

Depending on your OS, download either a `.dll` or `.so` of the plugin and put it in the `plugins` folder.

If this folder does not exist, create it yourself. JavalessMC alone is useless, as it just creates a player that does nothing.

## Debugging

In `CMakeLists.txt`, change `IS_DEBUG` to `ON` to run tests and have additional debug information.

if you dont want to run tests, change `RUN_TEST` to `OFF`

## Create Plugins

In the future, an API and an example will be published, with documentation. For now, please wait until we get to this part of development.

## Credits

| Contributor | Role |
|-------------|------|
| [SomeBoringNerd (Morgane)](https://github.com/SomeBoringNerd) | Main developer, plugin loader, event system, Minecraft API |
| [TaxMachine](https://github.com/TaxMachine) | Main developer, all of the networking / encryption systems |