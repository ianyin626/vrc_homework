#include "devices.h"

#include <iostream>
#include <cstdio>

void logMessage(const char* format, ...) {
    if (DEBUG_MODE) {
        // Format the message
        char buffer[1024];
        va_list args;
        va_start(args, format);
        vsnprintf(buffer, sizeof(buffer), format, args);
        va_end(args);

        // Print the formatted message
        std::cout << "[" << Brain.timer(vex::msec) << "] ";
        std::cout << buffer << std::endl;
    }
}