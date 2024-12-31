#include <QApplication>
#include "MainWindow.hpp"

int main(int argc, char *argv[])
{
    // Initialize the Qt application
    QApplication a(argc, argv);
    
    // Create and show the main window of the application
    MainWindow w;
    w.show();

    // Start the Qt event loop
    return a.exec();
}