# Add the executable/library for the UARTSender class
add_library(modelLib
  src/UARTSender.cpp
)

# Include header files from the include directory
target_include_directories(modelLib PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

add_executable(testModel test/testModel.cpp)

target_link_libraries(testModel modelLib)

set_target_properties(testModel PROPERTIES
  RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)
