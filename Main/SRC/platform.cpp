#include "../INCLUDES/CustomLibs/platform.h"

void GetPlatform(std::string& platform){
    #ifdef _WIN64
        platform = "Windows 64-bit";
    #elif defined(_WIN32)
        platform = "Windows 32-bit";
    #elif defined(__linux__)
        platform = "Linux";
    #elif defined(__APPLE__)
        platform = "macOS";
    #else
        platform = "Unknown";
    #endif
}

 