#include "MainWindow.hpp"
#include <QMessageBox>
#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), centralWidget(new CentralPanelWidget(this))
{
    resize(QGuiApplication::primaryScreen()->availableGeometry().size() * 0.5);

    setCentralWidget(centralWidget);

    setWindowTitle("UART LED Control");
}