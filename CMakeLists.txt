cmake_minimum_required(VERSION 3.4.1)

project(vim3d CXX)

# We are using C++ 17 and will make use of C++ exceptions.
set(CMAKE_CXX_COMPILER emcc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")

set(CMAKE_SOURCE_DIR src)

file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/*.h)
file(GLOB_RECURSE SRCFILES ${CMAKE_SOURCE_DIR}/*.cpp)

set(CMAKE_EXECUTABLE_SUFFIX ".html")
add_executable(
        vim3d
        ${HEADERS}
        ${SRCFILES}
)

set_target_properties(
        vim3d
        PROPERTIES
        LINK_FLAGS
        "-gk"
)