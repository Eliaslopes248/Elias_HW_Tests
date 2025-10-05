/**
 * This script is made to be used as a profiler for
 * what ever system is running our tests
 */

#include "../../INCLUDES/TestSelectionInfra/testbase.h"
#include "../../INCLUDES/TestSelectionInfra/testregister.h"
#include "../../INCLUDES/CustomLibs/rc.h"
#include "../../INCLUDES/CustomLibs/platform.h"
#include <iostream>
#include <string>

using namespace std;
 class SystemProfiler : public TestBase{
      

    public:
        // member variables
        static string platform;

        // test funcions
        void SetUp() override;
        void IsSupported() override;
        void Run() override;
        void CleanUp() override;
 };

string SystemProfiler::platform = "";

 #define SP SystemProfiler


 void SP::SetUp(){
    // get platform of running system
    GetPlatform(SystemProfiler::platform);

    // unable to find platform
    if (SystemProfiler::platform.empty() || SystemProfiler::platform == "Unknown") 
        return;

    printf("SYSTEM PLATFROM: %s", platform.c_str());
 }

 void SP::IsSupported(){}

 void SP::Run(){}

 void SP::CleanUp(){}

 // register test in registry
 REGISTER_TEST(1, SystemProfiler)


