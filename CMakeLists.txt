cmake_minimum_required(VERSION 3.15)
project(test_wheel)

set(CMAKE_CXX_STANDARD 17)

# Conan dependencies
find_package(pybind11 REQUIRED)
find_package(Ceres REQUIRED)

include_directories(include)

pybind11_add_module(test_wheel src/main.cpp)

target_link_libraries(test_wheel PRIVATE Ceres::ceres)


