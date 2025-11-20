#include <string>
#include <iostream>

// macOS System/Kernel level api
#include <sys/types.h>
#include <sys/sysctl.h>
#include <unistd.h>


#ifndef PLATFORM
#define PLATFORM

#include <string>

void GetPlatform(std::string& platform);

#endif