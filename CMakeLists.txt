cmake_minimum_required(VERSION 3.10)

# Project name and version
project(uart_connexion VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include the src directory
add_subdirectory(src)