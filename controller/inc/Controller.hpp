#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QThread>
#include <memory>

#include "MainWindow.hpp"
#include "UARTWorker.hpp"

class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(MainWindow *view, QObject *parent = nullptr);
  ~Controller();

 public slots:
  void onTTYConnexionMade();
  void onCommandSent();

 private:
  MainWindow *view;
  std::unique_ptr<UARTWorker> uartWorker;
  QThread uartThread;
};

#endif  // CONTROLLER_HPP
