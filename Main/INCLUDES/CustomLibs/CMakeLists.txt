# include all .h file libraries

add_library(
    CUSTOM_LIBS
    STATIC
    platform.h
    ../../SRC/platform.cpp
    ../../SRC/platform.cpp
    rc.h
)

# expose this library to be included
target_include_directories(CUSTOM_LIBS PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})