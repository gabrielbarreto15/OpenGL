cmake_minimum_required(VERSION 3.15)
project(SpectroSDL)

set(CMAKE_CXX_STANDARD 17)

add_executable(spectrosdl spectrosdl.cpp)

# Pacotes fornecidos pelo vcpkg
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(FFTW3 CONFIG REQUIRED)
find_package(OpenGL REQUIRED)
find_package(FreeGLUT CONFIG REQUIRED)  # FreeGLUT oferece GLUT::GLUT também

# Link com os targets das bibliotecas
target_link_libraries(spectrosdl
    PRIVATE
    SDL2::SDL2main
    SDL2::SDL2
    SDL2_mixer::SDL2_mixer
    FFTW3::fftw3
    OpenGL::GL
    FreeGLUT::freeglut
)
