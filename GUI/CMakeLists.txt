set(CMAKE_AUTOMOC ON)

# Add GUI source files
add_library(GUI
    CentralPanelWidget.cpp MainWindow.cpp
)

# Include GUI headers
target_include_directories(GUI PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Include Qt headers
target_link_libraries(GUI Qt6::Widgets)
