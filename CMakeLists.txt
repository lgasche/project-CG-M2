cmake_minimum_required(VERSION 2.8)

project(ImacGL)

add_definitions(-std=c++17)

add_compile_options(-lstdc++fs)

set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake)

find_package(SDL REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

# Pour gérer un bug a la fac, a supprimer sur machine perso:
# set(OPENGL_LIBRARIES /usr/lib/x86_64-linux-gnu/libGL.so.1)

include_directories(${SDL_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} glimac/include third-party/include)

set(ALL_LIBRARIES glimac ${SDL_LIBRARY} ${OPENGL_LIBRARIES} ${GLEW_LIBRARY})

add_subdirectory(glimac)

file(GLOB DIRECTORIE "main")

foreach(TP ${DIRECTORIE})
    add_subdirectory(${TP})
endforeach()
