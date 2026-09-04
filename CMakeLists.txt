cmake_minimum_required(VERSION 4.1)
project(obj_software_renderer)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-static")
option(USE_SDL "whether to generate an image using stb or render using SDL" ON)
if (USE_SDL)
    if (NOT WIN32)
        # remove -static flag for linux since SDL won't compile
        set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
    endif ()
    set(BACKEND src/backends/SDL.cpp)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/build/SDL)
else ()
    set(BACKEND src/backends/stb.cpp)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/build/stb)
endif ()
add_executable(obj_software_renderer
    ${BACKEND}
    src/main.cpp
    src/model.cpp
    src/draw.cpp
)
set_target_properties(obj_software_renderer PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR})
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL
    GIT_TAG release-3.4.14
    GIT_SHALLOW TRUE
)
FetchContent_Declare(
    stb
    GIT_REPOSITORY https://github.com/nothings/stb.git
    GIT_TAG master
    GIT_SHALLOW TRUE
)
if (USE_SDL)
    set(SDL_SHARED OFF CACHE BOOL "" FORCE)
    set(SDL_STATIC ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(SDL3)
    target_link_libraries(obj_software_renderer PRIVATE SDL3::SDL3-static)
    if (WIN32)
        target_link_libraries(obj_software_renderer PRIVATE
            winmm
            imm32
            version
            setupapi
        )
    endif ()
else ()
    FetchContent_MakeAvailable(stb)
    target_include_directories(obj_software_renderer PRIVATE
        ${stb_SOURCE_DIR}
    )
endif ()