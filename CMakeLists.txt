cmake_minimum_required(VERSION 3.2)
project(AdvancedScripting2)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp)
add_executable(AdvancedScripting2 ${SOURCE_FILES} EasyBMP/EasyBMP.h EasyBMP/EasyBMP.cpp ImageOutput.h ImageOutput.cpp)