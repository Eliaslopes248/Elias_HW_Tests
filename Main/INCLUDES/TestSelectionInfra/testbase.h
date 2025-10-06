/**
 * Parent class of all HW test in this
 * code base
 *
 * any new testing class will inherit
 * publically from this base class
 */

#include <iostream>
#include <string>
#include <vector>

#ifndef TESTBASE_H
#define TESTBASE_H

class TestBase
{

private:
    int m_testNumber;
    std::string m_testName;

public:
    // defualt test functions must be overridden
    virtual void ParseArgs(const std::vector<std::string> args) = 0;
    virtual void SetUp() = 0;
    virtual void IsSupported() = 0;
    virtual void Run() = 0;
    virtual void CleanUp() = 0;

    virtual ~TestBase() = default;
};

#endif // TESTBASE_H