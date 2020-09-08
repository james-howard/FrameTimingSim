cmake_minimum_required(VERSION 3.1...3.17)

project(FrameTimingSim VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

file(GLOB FRAME_SINKS "FrameSinks/*.hpp" "FrameSinks/*.cpp")

add_executable(FrameTimingSim
               ${FRAME_SINKS}
               "main.cpp")
