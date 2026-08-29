# obj-software-renderer

A program that takes a .obj file as a command-line argument and renders it
entirely on the CPU. The final result is displayed either using:
- the stb library, as a .png
- the SDL library, in an open window (only on Windows for now)

### config and usage
- precompiled binaries can be found in `build/stb` or `build/SDL`
- .obj files for testing can be found in `build/assets`
- camera zoom can be adjusted by modifying `CAM_SCALE` in global.h
- when compiling with CMAKE, set the `USE_SDL` option to decide whether to use stb or SDL; ex: `-DUSE_SDL=OFF`
- example usage (from within the `build/stb` directory):\
`./obj_software_renderer ../assets/african_head.obj`

### dependency links
- stb: https://github.com/nothings/stb
- SDL: https://github.com/libsdl-org/SDL