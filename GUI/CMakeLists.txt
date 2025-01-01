set(CMAKE_AUTOMOC ON)

qt6_wrap_cpp(GUI_MOC_FILES
    inc/MainWindow.hpp
    inc/CentralPanelWidget.hpp
)

# Add GUI source files
add_library(GUI
    ${GUI_MOC_FILES}
    src/CentralPanelWidget.cpp
    src/MainWindow.cpp
)

# Include GUI headers
target_include_directories(GUI PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/inc
)

# Include Qt headers
target_link_libraries(GUI PUBLIC
    Qt6::Core
    Qt6::Widgets
)
