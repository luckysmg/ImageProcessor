cmake_minimum_required(VERSION 3.17)
project(ImageProcessor)

set(CMAKE_CXX_STANDARD 11)

add_executable(ImageProcessor main.cpp Processor.cpp Processor.h Models.h Util.h)