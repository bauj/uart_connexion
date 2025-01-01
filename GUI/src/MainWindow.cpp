#include "MainWindow.hpp"

#include <QGuiApplication>
#include <QScreen>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      centralWidget(std::make_unique<CentralPanelWidget>(this)) {
  resize(QGuiApplication::primaryScreen()->availableGeometry().size().width() *
             0.3,
         QGuiApplication::primaryScreen()->availableGeometry().size().height() *
             0.4);

  setCentralWidget(centralWidget.get());

  setWindowTitle("UART LED Control");
}