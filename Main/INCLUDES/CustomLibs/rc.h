/**
 * RC == Return Code
 *
 * An emum that represents the
 * error status of a test
 *
 * OK == status code 200 -> PASS
 * != OK == FAIL
 *
 * Different types of failures can
 * help for debugging the test
 *
 * or finding HW issues
 */

#include <iostream>

class RC
{
    enum CODES
    {
        OK,
        BAD_ARGUMENTS_PASSED,
        HW_ERROR,
        MEMORY_OVERFLOW,
        PROGRAM_HUNG,
    };

public:
    CODES rc = CODES::OK;

    // Logs RC message to the console
    void LogMessage()
    {
        switch (rc)
        {
        case CODES::OK:
            std::cout << "No Issues: Error Code 0" << std::endl;
            break;
        case CODES::BAD_ARGUMENTS_PASSED:
            std::cout << "Error: BAD_ARGUMENTS_PASSED" << std::endl;
            break;
        case CODES::HW_ERROR:
            std::cout << "Error: HW_ERROR" << std::endl;
            break;
        case CODES::MEMORY_OVERFLOW:
            std::cout << "Error: MEMORY_OVERFLOW" << std::endl;
            break;
        case CODES::PROGRAM_HUNG:
            std::cout << "Error: PROGRAM_HUNG" << std::endl;
            break;
        default:
            std::cout << "Error: Issue not detected" << std::endl;
            break;
        }
    }
};