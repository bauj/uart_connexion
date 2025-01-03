set(CMAKE_AUTOMOC ON)

qt6_wrap_cpp(CONTROLLER_MOC_FILES
  inc/UARTWorkerSender.hpp
  inc/UARTWorkerReceiver.hpp
  inc/Controller.hpp
)

# Add Controller source files
add_library(controller
  ${CONTROLLER_MOC_FILES}
  src/UARTWorkerSender.cpp
  src/UARTWorkerReceiver.cpp
  src/Controller.cpp
)

# Include Controller headers
target_include_directories(controller PUBLIC
  ${CMAKE_CURRENT_SOURCE_DIR}/inc
  ${CMAKE_SOURCE_DIR}/model/inc
  ${CMAKE_SOURCE_DIR}/GUI/inc
)

# Include Qt headers
target_link_libraries(controller PUBLIC
  modelLib
  GUI
  Qt6::Core
  Qt6::Widgets)
