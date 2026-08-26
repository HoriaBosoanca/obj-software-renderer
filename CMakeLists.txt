cmake_minimum_required(VERSION 4.1)
project(obj_software_renderer)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-static")

option(USE_SDL "OFF -> will generate an image using stb; ON -> will render using SDL" OFF)
if (USE_SDL)
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
target_include_directories(obj_software_renderer PRIVATE
    src
)
set_target_properties(obj_software_renderer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${BIN_DIR}
)
if (USE_SDL)
    set(SDL2_LIB ${CMAKE_SOURCE_DIR}/lib/SDL2-2.32.10/x86_64-w64-mingw32)
    target_include_directories(obj_software_renderer PRIVATE
        ${SDL2_LIB}/include/SDL2
    )
    target_link_libraries(obj_software_renderer PRIVATE
        ${SDL2_LIB}/lib/libSDL2main.a
        ${SDL2_LIB}/lib/libSDL2.a
        winmm
        imm32
        version
        setupapi
    )
else ()
    target_include_directories(obj_software_renderer PRIVATE
        lib/stb
    )
endif ()