# set up minimum cmake version to run program
cmake_minimum_required(VERSION 4.0)
# name of target executable
project(my_sys_tests)

# set standard C++ verison
set(CMAKE_CXX_STANDARD 17)

# sets the target cpp file to be built to project exe
add_executable(${PROJECT_NAME} SRC/main.cpp)

# add subdirectories
add_subdirectory(INCLUDES/CustomLibs)
add_subdirectory(INCLUDES/TestSelectionInfra)
add_subdirectory(TESTS)

# link libraries
target_link_libraries(${PROJECT_NAME} CUSTOM_LIBS)
target_link_libraries(${PROJECT_NAME} TEST_INFRASTRUCTURE)
# Force load TESTS library to include registration code
if(APPLE)
    target_link_options(${PROJECT_NAME} PRIVATE -Wl,-force_load,$<TARGET_FILE:TESTS>)
else()
    target_link_libraries(${PROJECT_NAME} -Wl,--whole-archive TESTS -Wl,--no-whole-archive)
endif()