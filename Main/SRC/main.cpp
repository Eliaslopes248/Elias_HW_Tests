// Libs
#include "../INCLUDES/TestSelectionInfra/testregister.h"
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <string>
// Predefine helper functions here
void PrintFAIL();
void PrintPASS();
void FindTests();

using namespace std;

void loadSingleton(char* args[], int start, int end, vector<string>& test_args){
    for (int i = start; i < end; i++){
        test_args.push_back(string(args[i]));
    }
}


int main(int argc, char *argv[])
{
    // uses this variable if we run a single test
    int test_to_run;
    vector<string> test_args;

    // uses this variable if we run a test suite
    vector<int> test_suite(2);
    vector<vector<string>> test_suite_args(2);

    // parse args from command line
    for (int i = 1; i < argc; i++)
    {
        // checks if single test wants to be ran
        if (string(argv[i]) == "-test" || string(argv[i]) == "-t"){
            if ((i + 1) < argc){
                try{
                    // attempt to extract test number from arg
                    int number = stoi(argv[i+1]);
                    test_to_run = number;
                    // load args for single test
                    loadSingleton(argv, (i + 2), argc, test_args);

                }catch(...){
                    printf("Invalid Arg: Test number couldnt be parsed");
                    exit(EXIT_FAILURE);
                }
            }
        }


    }

    // get gloabl test manager: std::map<int, std::pair<std::string, Factory>> is returned
    const auto &tests = TestRegistry::Instance().GetTests();

    std::cout << "Running test number: " << test_to_run << std::endl;
    try {
        const auto &TEST = tests.at(test_to_run).second();
        TEST->IsSupported();

        if (!test_args.empty())
            TEST->ParseArgs(test_args); // some tests may not use args

        TEST->SetUp();
        TEST->Run();
        TEST->CleanUp();

    } catch (const std::out_of_range& e) {
        printf("Test number passed doesnt exist...");
        exit(EXIT_FAILURE);
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