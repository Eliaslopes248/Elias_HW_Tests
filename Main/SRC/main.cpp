// Libs
#include <iostream>
#include "../INCLUDES/TestSelectionInfra/testregister.h"

// Predefine helper functions here
void PrintFAIL();
void PrintPASS();
void FindTests();

int main(int argc, char *argv[])
{

    // parse args from command line
    for (int i = 1; i < argc; i++)
    {
        /**
         * Locate Test number (should be first arg after main.exe)
         * Example) -test test#
         *
         * Locate test args
         * Example) -testargs [argName1=argVal1, argName2=argVal2]
         *
         * Locate background test
         * Example -bgtest [-test test# -testargs [args...], ...more test and args]
         */

        std::cout << "Arg #" << i << ") " << argv[i] << std::endl;
    }

    // get gloabl test manager
    const auto &tests = TestRegistry::Instance().GetTests();

    for (const auto &[testNum, pair] : tests)
    {
        std::cout << "Running test number:" << testNum << std::endl;
        const auto &TEST = pair.second();

        TEST->IsSupported();
        TEST->SetUp();
        TEST->Run();
        TEST->CleanUp();
    }

    PrintPASS();

    return 0;
}

// implement helper functions here

void PrintFAIL()
{
    std::cout << R"(
██                     
██      
██      
██      
███████╗
╚══════╝

)" << std::endl;
}

void PrintPASS()
{
    std::cout << R"(

██     ██
██     ██
██  █  ██
██ ███ ██
███ ███ 

)" << std::endl;
}