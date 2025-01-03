#ifndef CONTROLLER_HPP
#define CONTROLLER_HPP

#include <QObject>
#include <QString>
#include <QThread>
#include <memory>

#include "MainWindow.hpp"
#include "UARTWorkerReceiver.hpp"
#include "UARTWorkerSender.hpp"

class Controller : public QObject {
  Q_OBJECT

 public:
  Controller(MainWindow *view, QObject *parent = nullptr);
  ~Controller();

 private:
  // Ensure threads are joined properly on exit
  void cleanUpThreads();

 public slots:
  void onTTYConnexionMade();
  void onCommandSent();
  void onMainWindowClosing();
  void onMessageReceived(
      const QString &message);  // Slot to handle incoming message

 private:
  MainWindow *view;

  std::shared_ptr<UARTSender> uartSender;

  // Sender Worker
  std::unique_ptr<UARTWorkerSender> uartWorkerSender;
  std::unique_ptr<QThread> senderThread;

  // Receiver Worker
  std::unique_ptr<UARTWorkerReceiver> uartWorkerReceiver;
  std::unique_ptr<QThread> receiverThread;
};

#endif  // CONTROLLER_HPP
