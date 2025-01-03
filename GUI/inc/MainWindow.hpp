#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QCloseEvent>

#include "CentralPanelWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow() = default;

  CentralPanelWidget *getCentralPanelWidget() const {
    return centralWidget.get();
  }

 signals:
  void windowClosing();  // Signal emitted when the window is closing

 protected:
  void closeEvent(
      QCloseEvent *event) override;  // Override closeEvent to emit the signal

 private:
  std::unique_ptr<CentralPanelWidget> centralWidget;
};