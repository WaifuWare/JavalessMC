//
// Created by TaxMachine on 2024-04-22.
//

#ifndef JAVALESSMC_WIN32STUFF_HPP
#define JAVALESSMC_WIN32STUFF_HPP

#ifdef _WIN32
#include <string>
#include <windows.h>

/**
 * @brief Gets the last Win32 error as a string instead of a DWORD
 * @note Taken from https://stackoverflow.com/questions/1387064/how-to-get-the-error-message-from-the-error-code-returned-by-getlasterror
 * */
std::string GetLastErrorString(DWORD msgId) {
    if (msgId == 0) {
        return "";
    }
    LPSTR msgBuffer = nullptr;
    size_t size = FormatMessageA(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                                 nullptr, msgId, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&msgBuffer, 0, nullptr);
    std::string message(msgBuffer, size);
    LocalFree(msgBuffer);
    return message;
}
#endif
#endif //JAVALESSMC_WIN32STUFF_HPP
