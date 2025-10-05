// Libs
#include <iostream>
#include "../INCLUDES/TestSelectionInfra/testregister.h"
#include <vector>
#include <string>
// Predefine helper functions here
void PrintFAIL();
void PrintPASS();
void FindTests();

using namespace std;


int main(int argc, char *argv[])
{

    int test_to_run;
    // parse args from command line
    for (int i = 1; i < argc; i++)
    {
        std::cout << "Arg #" << i << ") " << argv[i] << std::endl;

        // checks if single test wants to be ran
        if (string(argv[i]) == "-test" || string(argv[i]) == "-t"){
            if ((i + 1) < argc){
                try{
                    // attempt to extract test number from arg
                    int number = stoi(argv[i+1]);
                    test_to_run = number;
                }catch(...){
                    printf("Invalid Arg: Test number couldnt be parsed");
                    exit(EXIT_FAILURE);
                }
            }
        }


    }

    // get gloabl test manager: std::map<int, std::pair<std::string, Factory>> is returned
    const auto &tests = TestRegistry::Instance().GetTests();

    std::cout << "Running test number:" << test_to_run << std::endl;
    const auto &TEST = tests.at(test_to_run).second();

    TEST->IsSupported();
    TEST->SetUp();
    TEST->Run();
    TEST->CleanUp();
    

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