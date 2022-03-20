cmake_minimum_required(VERSION 3.21)
project(mordencpp)

set(CMAKE_CXX_STANDARD 23)
set(CXX_STANDARD_REQUIRED YES)
set(CXX_EXTENSIONS NO)

if (BUILD_NUMBER)
    message("Build number: ${BUILD_NUMBER}")
else()
    message("No build number, setting build number to 0")
    set(BUILD_NUMBER 0)
endif()

add_subdirectory(Task1)
add_subdirectory(Task2)

