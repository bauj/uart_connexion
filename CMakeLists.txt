cmake_minimum_required(VERSION 3.10)

# Project name and version
project(uart_connexion VERSION 1.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Find Qt6 libraries
find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_subdirectory(model)
add_subdirectory(GUI)

# Create executable
add_executable(uart_connexion src/main.cpp)

# Add include paths for the main executable
target_include_directories(uart_connexion PRIVATE GUI model/inc)

# Link Qt6 libraries
target_link_libraries(uart_connexion Qt6::Widgets GUI)
