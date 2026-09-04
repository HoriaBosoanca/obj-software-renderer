# obj-software-renderer

A program that takes an .obj file as a command-line argument and renders it
entirely on the CPU. The final result is displayed either using:
- the stb library, as a .png
- the SDL library, in an open window (only on Windows for now)

This project is being made while following the tutorial at https://haqr.eu/tinyrenderer

### config and usage
- precompiled binaries can be found in `build/stb` or `build/SDL`
- .obj files for testing can be found in `build/assets`
- camera zoom can be adjusted by modifying `CAM_SCALE` in global.h
- when compiling with CMAKE, the `USE_SDL` variable in `set(USE_SDL ON)` can be set to `ON` or `OFF` to decide whether to use stb or SDL
- example usage on Windows (from within the `build/stb` directory):\
`./obj_software_renderer.exe ../assets/african_head.obj`

### dependency links
- stb: https://github.com/nothings/stb
- SDL: https://github.com/libsdl-org/SDL

### TODO:
- learn some math and understand `signed_triangle_area()` in draw.cpp
- keep reading/implementing theory from the article;
next up is https://haqr.eu/tinyrenderer/barycentric
- go back to https://haqr.eu/tinyrenderer/bresenham and implement the line optimizations
