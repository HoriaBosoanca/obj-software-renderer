cmake_minimum_required(VERSION 4.1)
project(obj_software_renderer)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-static")

option(USE_SDL "OFF -> will generate an image using STB; ON -> will render using SDL" OFF)
if (USE_SDL)
    set(SDL2_LIB ${CMAKE_SOURCE_DIR}/lib/SDL2-2.32.10/x86_64-w64-mingw32)
    set(SRC_FILES
        src/main_SDL.cpp
    )
    set(INCLUDE_FILES
        ${SDL2_LIB}/include/SDL2
    )
else ()
    set(SRC_FILES
        src/main_STB.cpp
        src/draw_STB/draw.cpp
    )
    set(INCLUDE_FILES
        lib/stb
        src/draw_STB
    )
endif ()

add_executable(obj_software_renderer
    ${SRC_FILES}
    src/load_obj.cpp
)
target_include_directories(obj_software_renderer PRIVATE
    ${INCLUDE_FILES}
    src
)

if (USE_SDL)
    target_link_libraries(obj_software_renderer PRIVATE
        ${SDL2_LIB}/lib/libSDL2.dll.a
        ${SDL2_LIB}/lib/libSDL2main.a
    )
    add_custom_command(TARGET obj_software_renderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${SDL2_LIB}/bin/SDL2.dll
        $<TARGET_FILE_DIR:obj_software_renderer>
    )
endif ()