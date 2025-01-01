#pragma once

#include <QMainWindow>
#include <QWidget>

#include "CentralPanelWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

  CentralPanelWidget *getCentralPanelWidget() const { return centralWidget.get(); }

 private:
  std::unique_ptr<CentralPanelWidget> centralWidget;
};