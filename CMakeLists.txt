cmake_minimum_required(VERSION 3.20...4.0)
project(PuffBlock)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(outside/glfw)
add_subdirectory(outside/glm)
add_subdirectory(outside/spdlog)

add_library(glad STATIC
    common/gl.c
)
target_include_directories(glad PUBLIC
    headers
)

add_library(FastNoiseSIMD STATIC
    noise/FastNoiseSIMD_avx2.cpp
    noise/FastNoiseSIMD_avx512.cpp
    noise/FastNoiseSIMD_internal.cpp
    noise/FastNoiseSIMD_internal.h
    noise/FastNoiseSIMD_neon.cpp
    noise/FastNoiseSIMD_sse2.cpp
    noise/FastNoiseSIMD_sse41.cpp
    noise/FastNoiseSIMD.cpp
    noise/FastNoiseSIMD.h
)
if(MSVC)
target_compile_options(FastNoiseSIMD PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:/arch:AVX2>")
else()
target_compile_options(FastNoiseSIMD PRIVATE "$<$<COMPILE_LANGUAGE:CXX>:-mavx2>")
endif()

add_library(ImGUI STATIC
    imgui/imconfig.h
    imgui/imgui_demo.cpp
    imgui/imgui_draw.cpp
    imgui/imgui_impl_glfw.cpp
    imgui/imgui_impl_glfw.h
    imgui/imgui_impl_opengl3.cpp
    imgui/imgui_impl_opengl3.h
    imgui/imgui_internal.h
    imgui/imgui_tables.cpp
    imgui/imgui_widgets.cpp
    imgui/imgui.cpp
    imgui/imgui.h
    imgui/imstb_rectpack.h
    imgui/imstb_textedit.h
    imgui/imstb_truetype.h
)
target_include_directories(ImGUI PUBLIC
    headers
    headers/glad
)
target_link_libraries(ImGUI PRIVATE glad glfw)

add_library(PuffEngine STATIC
    engine/filesys.cpp
    engine/filesys.hpp

    engine/shaders.cpp
    engine/shaders.hpp
    
    engine/texsys.cpp
    engine/texsys.hpp
    
    engine/renderer.hpp
    engine/renderer.cpp
    
    engine/vertexbuf.hpp
    engine/vertexbuf.cpp
    
    engine/indexbuf.hpp
    engine/indexbuf.cpp
    
    engine/vertexarray.hpp
    engine/vertexarray.cpp

    engine/window.hpp
    engine/window.cpp
    
    engine/stb_image.h
)
target_include_directories(PuffEngine PUBLIC
    headers
    headers/glad
)
target_link_libraries(PuffEngine PRIVATE glad glfw spdlog glm)

add_executable(Game
    src/chunk.cpp
    src/chunk.hpp

    src/input.cpp
    src/input.hpp
    
    src/imgui.cpp
    src/imgui.hpp
    
    src/shapes.hpp
    src/shapes.cpp
    
    src/Holder.cpp
    src/Holder.hpp

    src/main.cpp
    src/Camera.hpp
)

target_include_directories(Game PUBLIC
    headers
    engine
    imgui
)
target_link_libraries(Game PRIVATE glfw glad glm spdlog PuffEngine ImGUI)