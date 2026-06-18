cmake_minimum_required(VERSION 3.20)
project(Pricing-Engine)

set(CMAKE_CXX_STANDARD 20)

add_executable(Pricing-Engine src/BlackScholes.cpp src/Main.cpp src/mc_engine.cpp)

target_include_directories(Pricing-Engine PRIVATE Include)