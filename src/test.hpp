#if RUN_TEST
#pragma once

#include "commands/impl/login.hpp"

#include "utils/logger.hpp"
#include "config.hpp"

#define boolToString(b) (b ? "true" : "false")

#include "events/eventmanager.hpp"
#include "events/impl/processCommandEvent.hpp"

#include <iostream>
#include <string>

#include "commands/impl/test.hpp"
#include "minecraftapi/utils/vectors.h"
#include <cassert>
#define assertm(exp, msg) assert(((void)msg, exp))

#include "spdlog/stopwatch.h"

int i = 1;

void testConfig() {
    logTest("Test " + std::to_string(i++) + " : saving data");
    assertm(saveData(), "somthing went wrong with the saving logic");

    logTest("Test " + std::to_string(i++) + " : loading data");
    assertm(loadData(), "something went wrong with loading logic");

    logTest("Test " + std::to_string(i++) + " : reading data (1/4)");
    assertm(config.autoconnect, "Reading boolean from config did not work as expected");

    logTest("Test " + std::to_string(i++) + " : reading data (2/4)");
    assertm(config.username == "sbn", "Reading username from config did not work as expected");

    logTest("Test " + std::to_string(i++) + " : reading data (3/4)");
    assertm(config.password == "1234", "Reading password from config did not work as expected");

    logTest("Test " + std::to_string(i++) + " : reading data (4/4)");
    assertm(config.maxfps == 60, "Reading maxfps from config did not work as expected");
}

void testVector() {
    logTest("Test " + std::to_string(i++) + " : adding two vectors together (2i)");

    Vector2I _vec2I, __vec2I;

    _vec2I.x = 2;
    _vec2I.y = -4;

    __vec2I.x = 3;
    __vec2I.y = 5;

    assertm(add(_vec2I, __vec2I).x == 5 && add(_vec2I, __vec2I).y == 1, "This math does not add up !");

    logTest("Test " + std::to_string(i++) + " : adding two vectors together (2f)");

    Vector2F _vec2F, __vec2F;

    _vec2F.x = 1.5f;
    _vec2F.y = 2.95f;

    __vec2F.x = 2.5f;
    __vec2F.y = 5;

    assertm(add(_vec2F, _vec2F).x == 4.0f && add(_vec2F, _vec2F).y == 7.95f, "This math does not add up !");
}

void test() {
    log("test");
    logError("test error");

    initTestConsole();

    // test command system with args
    EventManager::getInstance().fire(new ProcessCommandEvent("login", new char *[2] {"sbn", "1234"}));

    // test save system
    config.autoconnect = true;

    spdlog::stopwatch sw;    

    testConfig();

    testVector();

    logTest("every test passed with success in " + std::to_string(sw.elapsed().count() * 1000.0) + " ms");
}

#endif