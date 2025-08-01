

/**
 * This class is used to hold
 * and register all new tests
 * that are made
 *
 */

#include "testbase.h"
#include <iostream>
#include <map>
#include <functional>
#include <memory>
#include <string>

class TestRegistry
{

public:
    // smart ptr to a test
    using Factory = std::function<std::unique_ptr<TestBase>()>;

    // static instance for other files to use
    static TestRegistry &Instance()
    {
        // singleton created and always used
        static TestRegistry instance;
        return instance;
    }

    std::map<int, std::pair<std::string, Factory>> m_tests;

    // return ptrs to all test
    std::map<int, std::pair<std::string, Factory>> GetTests() { return m_tests; };

    // add test to test map
    void registerTest(int testNumber, std::string testName, Factory factory)
    {
        m_tests[testNumber] = {testName, std::move(factory)};
    }
};

// Global helper for running tests
#define REGISTER_TEST(TEST_NUM, TEST_CLASS)                                                                                    \
    namespace                                                                                                                  \
    {                                                                                                                          \
        struct TEST_CLASS##Registration                                                                                        \
        {                                                                                                                      \
            TEST_CLASS##Registration()                                                                                         \
            {                                                                                                                  \
                TestRegistry::Instance().registerTest(TEST_NUM, #TEST_CLASS, []() { return std::make_unique<TEST_CLASS>(); }); \
            }                                                                                                                  \
        };                                                                                                                     \
        static TEST_CLASS##Registration global_##TEST_CLASS##Registration;                                                     \
    }
