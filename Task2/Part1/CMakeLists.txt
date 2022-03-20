cmake_minimum_required(VERSION 3.21)
project(custom_tie)

add_executable(${PROJECT_NAME} main.cpp)
target_compile_definitions(${PROJECT_NAME} PRIVATE BUILD_NUMBER=${BUILD_NUMBER})
install(TARGETS ${PROJECT_NAME})