cmake_minimum_required(VERSION 3.8)    
set (CMAKE_CXX_STANDARD 11)    
project(PlayCompiler)    
    
# Find and include all source .cpp files    
file(GLOB SOURCES "src/*.cpp")    
include_directories(src)    
    
add_definitions("-fPIC")    
    
add_executable(playCompiler ${SOURCES})    
