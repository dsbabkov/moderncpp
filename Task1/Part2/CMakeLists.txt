cmake_minimum_required(VERSION 3.21)
project(ip_filter)

add_executable(${PROJECT_NAME} main.cpp IpAddress.cpp Split.cpp)
install(TARGETS ${PROJECT_NAME})
