cmake_minimum_required(VERSION 4.1)
project(obj_software_renderer)
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_EXE_LINKER_FLAGS "-static")

option(USE_SDL "OFF -> will generate an image using STB; ON -> will render using SDL" OFF)
if (USE_SDL)
    set(SRC_FILES src/SDL_impl.cpp)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/SDL)
else ()
    set(SRC_FILES src/STB_impl.cpp)
    set(BIN_DIR ${CMAKE_SOURCE_DIR}/bin/STB)
endif ()

add_executable(obj_software_renderer
    ${SRC_FILES}
    src/main.cpp
    src/load_obj.cpp
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
#    target_link_libraries(obj_software_renderer PRIVATE
#        ${SDL2_LIB}/lib/libSDL2.dll.a
#        ${SDL2_LIB}/lib/libSDL2main.a
#    )
#    add_custom_command(TARGET obj_software_renderer POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy_if_different
#        ${SDL2_LIB}/bin/SDL2.dll
#        $<TARGET_FILE_DIR:obj_software_renderer>
#    )
else ()
    target_include_directories(obj_software_renderer PRIVATE
        lib/stb
    )
endif ()