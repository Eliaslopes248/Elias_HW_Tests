#include <string>
#include <iostream>

// macOS System/Kernel level api
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>


#ifndef PLATFORM
#define PLATFORM

using namespace std;

void GetPlatform(string& platform){
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

#endif