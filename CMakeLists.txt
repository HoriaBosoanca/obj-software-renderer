cmake_minimum_required(VERSION 4.1)
project(obj_software_renderer)
set(CMAKE_CXX_STANDARD 23)
add_executable(obj_software_renderer main.cpp)

set(SDL2_DIR "${CMAKE_SOURCE_DIR}/SDL2-2.32.10/x86_64-w64-mingw32")
target_include_directories(obj_software_renderer PRIVATE "${SDL2_DIR}/include/SDL2")
target_link_libraries(obj_software_renderer PRIVATE
        "${SDL2_DIR}/lib/libSDL2.dll.a"
        "${SDL2_DIR}/lib/libSDL2main.a"
)
add_custom_command(TARGET obj_software_renderer POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_DIR}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:obj_software_renderer>
)