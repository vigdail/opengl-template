cmake_minimum_required(VERSION 3.24)
set(PROJECT_NAME vgl)
set(LIB_NAME vgl)

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

add_library(${LIB_NAME} src/camera.cpp include/vgl/camera.h include/vgl/shader.h src/shader.cpp include/vgl/texture.h src/texture.cpp src/window.cpp include/vgl/window.h src/application.cpp include/vgl/application.h src/layer.cpp include/vgl/layer.h src/gui_layer.cpp include/vgl/gui_layer.h src/fps_counter.cpp include/vgl/fps_counter.h)
target_link_libraries(${LIB_NAME} glfw gl glm libglew_static imgui)

if (VGL_BUILD_EXAMPLES)
    add_executable(example example/main.cpp example/example_layer.cpp example/example_layer.h)
    target_link_libraries(example ${LIB_NAME})
endif ()
