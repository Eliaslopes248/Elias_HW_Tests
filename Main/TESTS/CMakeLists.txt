# include all test cpp files in this directory
file(GLOB TEST_SOURCES "test*/*.cpp" "test*/*.h")

add_library(
    TESTS
    STATIC
    ${TEST_SOURCES}
)

# expose library
target_include_directories(TESTS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})