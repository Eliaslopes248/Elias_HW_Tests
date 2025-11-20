#include "../../INCLUDES/TestSelectionInfra/testbase.h"
#include "../../INCLUDES/TestSelectionInfra/testregister.h"
#include "../../INCLUDES/CustomLibs/platform.h"
#include "../../INCLUDES/CustomLibs/rc.h"
#include <algorithm>
#include <chrono>
#include <climits>
#include <ctime>
#include <ostream>
#include <sys/types.h>
#include <iostream>
#include <unistd.h>
#include <ctime>


using namespace std;

class ProcCreateTime : public TestBase{
public:
    static string platform;
    void ParseArgs(const std::vector<std::string> args) override;
    void SetUp() override;
    void IsSupported() override;
    void Run() override;
    void CleanUp() override;

};

#define PCT ProcCreateTime

//================================================================
// TEST IMPLEMENTATION
//================================================================
string ProcCreateTime::platform = "";
void PCT::IsSupported()
{
    // check if platform is supported
    GetPlatform(ProcCreateTime::platform);

    if ((ProcCreateTime::platform == "macOS") ||
        (ProcCreateTime::platform == "Linux")
    ){
        cout << "Platform is Supported: " << ProcCreateTime::platform << "\n";
    }

}

void PCT::ParseArgs(const std::vector<std::string> args){}

void PCT::SetUp(){}

void compute(bool freeMem=true)
{
    // large loop to stress cpu during process
    int n=2000;
    int* a = new int[n];
    for (int i=0;i<n;i++){
        a[i] = i;
    }
    // free up memory
    if (freeMem) delete [] a;
}

void PCT::Run()
{
    //===========================================
    // CUSTOM STRUCT WITH PROCESS TIME TRACKING
    //===========================================
    struct{
        long long   min_t=INT_MAX;
        long long   max_t=INT_MIN;
        long long   sum_t=0;
        double               avg_t=0;
    }testInfo;

    int num_loops = 1800;

    for(int i = 0; i < num_loops; i++)
    {
        // record start time
        auto start_time = chrono::high_resolution_clock::now();

        // make child process
        int pid = fork();

        // handle pid
        if (pid < 0){
            std::cout << "Fork() error: " << pid << std::endl; 
            _exit(-1);
        }else if (pid == 0) {
            compute();
            _exit(0);
        }else{
            // get end time stamp
            auto end_time = chrono::high_resolution_clock::now();
            auto elapse_time = chrono::duration_cast<chrono::microseconds>( end_time - start_time).count();
            // update testInfo
            testInfo.max_t = max(testInfo.max_t, elapse_time);
            testInfo.min_t = min(testInfo.max_t, elapse_time);
            testInfo.sum_t += elapse_time;
        }
        
    }

    testInfo.avg_t = (double) testInfo.sum_t / num_loops;

    // print out results
    std::cout << "\n=============TEST 2 RESULTS=============" << std::endl;

    std::cout << "Test runs: " << num_loops << std::endl;
    std::cout << "Min time: " << testInfo.min_t << std::endl;
    std::cout << "Max time: " << testInfo.max_t << std::endl;
    std::cout << "Avg time: " << testInfo.avg_t << std::endl;

}

void PCT::CleanUp(){}




//================================================================
// REGISTER TEST
//================================================================
REGISTER_TEST(2, ProcCreateTime);