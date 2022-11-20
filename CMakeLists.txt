cmake_minimum_required(VERSION 3.4.1)

project(vim3d CXX)

set(CMAKE_CXX_COMPILER emcc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -Wall -Wextra -g")

set(CMAKE_SOURCE_DIR src)

file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/*.h ${CMAKE_SOURCE_DIR}/primitives/*.h ${CMAKE_SOURCE_DIR}/custom_gl/freeglut_std.h)
file(GLOB SRCFILES 
        ${CMAKE_SOURCE_DIR}/*.cpp
        ${CMAKE_SOURCE_DIR}/primitives/*.cpp
        ${CMAKE_SOURCE_DIR}/custom_gl/freeglut/*.cpp
        ${CMAKE_SOURCE_DIR}/custom_gl/GLU/*.cpp
        ${CMAKE_SOURCE_DIR}/custom_gl/glues/*.cpp
)

# include_directories(emscripten/system/include)
# include_directories(emscripten/system/lib/libcxx/include)
# include_directories(emscripten/system/lib/libc/musl/include)
# include_directories(emscripten/system/lib/libc/musl/arch/emscripten)
# include_directories(emscripten/system/lib/libc/musl/arch/generic)
include_directories(include)

file(COPY objects DESTINATION ${CMAKE_BINARY_DIR})
file(COPY scenes DESTINATION ${CMAKE_BINARY_DIR})
file(COPY lib DESTINATION ${CMAKE_BINARY_DIR})

set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_executable(
        vim3d
        ${HEADERS}
        ${SRCFILES}
)

set(GL_OPTS "-sMAX_WEBGL_VERSION=2 -sFULL_ES2=1")
set(LIB_OPTS "-lGL -lGLU --js-library lib/js/library_glut.js")
set(MEMORY_OPTS "-sALLOW_MEMORY_GROWTH=1")
set(LOAD_FILES "--embed-file objects --embed-file scenes")
set(EMCC_LINK_OPTS "${GL_OPTS} ${MEMORY_OPTS} ${EMRUN_OPTS} ${LOAD_FILES} ${LIB_OPTS}")

get_filename_component(LIBGL_ABS_PATH "lib/c/libGL.a" ABSOLUTE)
target_link_libraries(vim3d ${LIBGL_ABS_PATH})
set_target_properties(
        vim3d
        PROPERTIES
        LINK_FLAGS
        ${EMCC_LINK_OPTS}
)