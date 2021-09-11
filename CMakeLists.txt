cmake_minimum_required(VERSION 3.9)

project(LineRen)

# Require C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED)

# Use SDL2 for opening window and initializing GL context
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})

# Use globbing to find source files.
file(GLOB_RECURSE SOURCE_FILES ${CMAKE_SOURCE_DIR}/src/*.cpp)

add_executable(lineren ${SOURCE_FILES})
target_link_libraries(lineren ${SDL2_LIBRARIES})

# Enable all warnings except for no-sign-compare, which Clang disables
# by default.
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-sign-compare")

option(WERROR "Turn warnings into errors" OFF)
if (WERROR)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror")
endif ()
