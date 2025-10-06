/**
 * This script is made to be used as a profiler for
 * what ever system is running our tests
 */

#include "../../INCLUDES/TestSelectionInfra/testbase.h"
#include "../../INCLUDES/TestSelectionInfra/testregister.h"
#include "../../INCLUDES/CustomLibs/rc.h"
#include "../../INCLUDES/CustomLibs/platform.h"
#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sys/sysctl.h>
#include <vector>

using namespace std;
 class SystemProfiler : public TestBase{
      

    public:
        // member variables
        static string platform;

        // test funcions
        void ParseArgs(const std::vector<std::string> args) override;
        void SetUp()        override;
        void IsSupported()  override;
        void Run()          override;
        void CleanUp()      override;
 };

string SystemProfiler::platform = "";

 #define SP SystemProfiler

 // helper functions
void profileMac(){
    printf("\n\n");
    printf("===================================================\n");
    printf("\t\tDEVICE PROFILE\n");
    printf("===================================================\n");
    try{
        // print out HARDWARE INFO FIRST
        char    messageBuffer[100];
        size_t  size = sizeof(messageBuffer);
        if (sysctlbyname("kern.hostname", &messageBuffer, &size, NULL, 0) == 0)
            cout << "Host Name: " << messageBuffer << endl;

        // reset buffer
        memset(messageBuffer, 0, size);

        if (sysctlbyname("machdep.cpu.brand_string", &messageBuffer, &size, NULL, 0) == 0)
            cout << "CPU Brand: " << messageBuffer << endl;

        // reset buffer
        memset(messageBuffer, 0, size);

        if (sysctlbyname("kern.osrelease", &messageBuffer, &size, NULL, 0) == 0)
            cout << "OS Release: " << messageBuffer << endl;

        // reset buffer
        memset(messageBuffer, 0, size);

        if (sysctlbyname("kern.osversion", &messageBuffer, &size, NULL, 0) == 0)
            cout << "OS Version: " << messageBuffer << endl;

        // reset buffer
        memset(messageBuffer, 0, size);

    }catch(...){
        printf("Unable to profile this system...");
        exit (EXIT_FAILURE);
    }

    printf("===================================================\n");
}
void profileLinux(){

}
void profileWindows(int arch){

}


 // implemenetation
 void SP::SetUp(){
    // get platform of running system
    GetPlatform(SystemProfiler::platform);

    // unable to find platform
    if (SystemProfiler::platform.empty() || SystemProfiler::platform == "Unknown") 
        return;

    printf("SYSTEM PLATFROM: %s\n", platform.c_str());
 }

 void SP::ParseArgs(const std::vector<std::string> args){ return; }

 void SP::IsSupported(){}

 void SP::Run(){                                                    // select which system platform to profile using specific API
    if (string(SystemProfiler::platform) == "macOS")                profileMac();
    else if (string(SystemProfiler::platform) == "Windows 64-bit")  profileWindows(64);
    else if (string(SystemProfiler::platform) == "Windows 32-bit")  profileWindows(32);
    else if (string(SystemProfiler::platform) == "Linux")           profileLinux();
    else exit(EXIT_FAILURE); // unsupported system
    
 }

 void SP::CleanUp(){}

 // register test in registry
 REGISTER_TEST(1, SystemProfiler)


