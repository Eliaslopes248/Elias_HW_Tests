# include all .h file libraries

add_library(
    TEST_INFRASTRUCTURE
    INTERFACE
    testbase.h
    testregister.h
)

# expose this library to be included
target_include_directories(TEST_INFRASTRUCTURE INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})