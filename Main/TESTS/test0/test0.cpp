#include "../../INCLUDES/TestSelectionInfra/testbase.h"
#include "../../INCLUDES/TestSelectionInfra/testregister.h"
#include <iostream>
class ExampleTest : public TestBase
{

public:
    void SetUp() override;
    void IsSupported() override;
    void Run() override;
    void CleanUp() override;
};

void ExampleTest::SetUp()
{
    printf("Running SetUp function\n");
}
void ExampleTest::IsSupported()
{
    printf("Running IsSupported function\n");
}
void ExampleTest::Run()
{
    printf("Running Run function\n");
}
void ExampleTest::CleanUp()
{
    printf("Running CleanUp function\n");
}

REGISTER_TEST(0, ExampleTest);