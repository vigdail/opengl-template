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

include_directories(vendor/stb)

set(IMGUI_WITH_BACKEND TRUE)
set(IMGUI_BACKEND_GLFW TRUE)
set(IMGUI_GLFW_INCLUDE_PATH ${glfw_SOURCE_DIR}/include)
FetchContent_Declare(
        imgui
        GIT_REPOSITORY https://github.com/vigdail/imgui-cmake.git
        GIT_TAG master
)
FetchContent_MakeAvailable(imgui)

add_executable(${EXECUTABLE_NAME} src/main.cpp src/core/camera.cpp src/core/camera.h src/core/shader.h src/core/shader.cpp src/core/texture.h src/core/texture.cpp src/core/window.cpp src/core/window.h src/core/application.cpp src/core/application.h src/core/layer.cpp src/core/layer.h src/core/gui_layer.cpp src/core/gui_layer.h src/util/fps_counter.cpp src/util/fps_counter.h src/example_layer.cpp src/example_layer.h)
target_link_libraries(${EXECUTABLE_NAME} glfw gl glm libglew_static imgui)
