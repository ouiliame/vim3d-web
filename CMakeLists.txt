cmake_minimum_required(VERSION 3.4.1)

project(vim3d CXX)

set(CMAKE_CXX_COMPILER emcc)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -g")

set(CMAKE_SOURCE_DIR src)

file(GLOB HEADERS ${CMAKE_SOURCE_DIR}/*.h ${CMAKE_SOURCE_DIR}/primitives/*.h)
file(GLOB SRCFILES ${CMAKE_SOURCE_DIR}/*.cpp ${CMAKE_SOURCE_DIR}/primitives/*.cpp ${CMAKE_SOURCE_DIR}/custom_gl/freeglut_std.cpp ${CMAKE_SOURCE_DIR}/custom_gl/glu.cpp)

# include_directories(emscripten/system/include)
# include_directories(emscripten/system/lib/libcxx/include)
# include_directories(emscripten/system/lib/libc/musl/include)
# include_directories(emscripten/system/lib/libc/musl/arch/emscripten)
# include_directories(emscripten/system/lib/libc/musl/arch/generic)
# include_directories(gl4es/include)


set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_executable(
        vim3d
        ${HEADERS}
        ${SRCFILES}
)

# get_filename_component(LIBGL_ABS_PATH "gl4es/lib/libGL.a" ABSOLUTE)
# get_filename_component(LIBREGAL_ABS_PATH "libRegallib.a" ABSOLUTE)
# get_filename_component(LIBREGALGLU_ABS_PATH "libRegalGLUlib.a" ABSOLUTE)
target_link_libraries(vim3d ${LIBREGAL_ABS_PATH} ${LIBREGALGLU_ABS_PATH})
set_target_properties(
        vim3d
        PROPERTIES
        LINK_FLAGS
        "-sUSE_PTHREADS=1 -lpthread -sUSE_REGAL=1 -sLLD_REPORT_UNDEFINED"
)