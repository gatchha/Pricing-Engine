cmake_minimum_required(VERSION 3.20)
project(Pricing-Engine)

set(CMAKE_CXX_STANDARD 20)


include_directories(Include)

add_executable(Pricing-Engine src/BlackScholes.cpp src/Main.cpp)