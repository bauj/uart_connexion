# Add the executable/library for the UARTSender class
add_library(UARTSender
  UARTSender.cpp
)

# Include header files from the include directory
target_include_directories(UARTSender PUBLIC
  ${CMAKE_SOURCE_DIR}/inc
)

add_executable(main main.cpp)
target_link_libraries(main UARTSender)

set_target_properties(main PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)