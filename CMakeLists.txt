cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME opengl_template)
set(EXECUTABLE_NAME opengl_template)

project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        glfw
        GIT_REPOSITORY https://github.com/glfw/glfw
        GIT_TAG master
)
FetchContent_MakeAvailable(glfw)

FetchContent_Declare(
        glew
        GIT_REPOSITORY https://github.com/Perlmint/glew-cmake.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glew)

FetchContent_Declare(
        gl
        GIT_REPOSITORY https://github.com/acdemiralp/gl.git
        GIT_TAG master
)
FetchContent_MakeAvailable(gl)

FetchContent_Declare(
        glm
        GIT_REPOSITORY https://github.com/g-truc/glm.git
        GIT_TAG master
)
FetchContent_MakeAvailable(glm)

add_executable(${EXECUTABLE_NAME} main.cpp)
target_link_libraries(${EXECUTABLE_NAME} glfw gl glm libglew_static)
