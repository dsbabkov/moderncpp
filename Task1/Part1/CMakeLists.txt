cmake_minimum_required(VERSION 3.21)
project(helloworld)

add_compile_definitions(BUILD_NUMBER=${BUILD_NUMBER})
add_executable(${PROJECT_NAME} main.cpp)
