cmake_minimum_required(VERSION 3.31)
project(ParticlesWIthOpenCV)

set(CMAKE_CXX_STANDARD 20)

find_package(OpenCV REQUIRED)
find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

add_executable(ParticlesWIthOpenCV src/main.cpp
        src/Game.cpp
        headers/Game.hpp
        headers/Constants.hpp)

target_link_libraries(ParticlesWIthOpenCV ${OpenCV_LIBS})
target_link_libraries(ParticlesWIthOpenCV sfml-graphics sfml-window sfml-system)
include_directories(${OpenCV_INCLUDE_DIRS})


