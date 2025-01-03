#include "Controller.hpp"

#include <QMetaObject>

Controller::Controller(MainWindow *view, QObject *parent)
    : QObject(parent), view(view) {
  // Connect the send button clicked signal to the controller's slot

  // Connect GUI signals to controller slots
  connect(view->getCentralPanelWidget()->getSendButton(), &QPushButton::clicked,
          this, &Controller::onCommandSent);

  connect(view->getCentralPanelWidget()->getConnectButton(),
          &QPushButton::clicked, this, &Controller::onTTYConnexionMade);

  connect(view, &MainWindow::windowClosing, this,
          &Controller::onMainWindowClosing);
}

Controller::~Controller() { cleanUpThreads(); }

void Controller::onTTYConnexionMade() {
  auto ttyCmbBox = view->getCentralPanelWidget()->getTTYComboBox();
  auto baudRateCmbBox = view->getCentralPanelWidget()->getBaudRateComboBox();
  auto ttyDeviceName = ttyCmbBox->itemText(ttyCmbBox->currentIndex());
  auto ttyBaudRate = baudRateCmbBox->itemText(baudRateCmbBox->currentIndex());

  // Initialize UART sender
  uartSender = std::make_shared<UARTSender>(
      "/dev/" + ttyDeviceName.toStdString(), ttyBaudRate.toInt());

  // UART Worker Sender
  uartWorkerSender = std::make_unique<UARTWorkerSender>(uartSender);
  senderThread = std::make_unique<QThread>();
  uartWorkerSender->moveToThread(senderThread.get());
  senderThread->start();

  // UART Worker Receiver
  uartWorkerReceiver = std::make_unique<UARTWorkerReceiver>(uartSender);
  receiverThread = std::make_unique<QThread>();
  uartWorkerReceiver->moveToThread(receiverThread.get());
  connect(receiverThread.get(), &QThread::started, uartWorkerReceiver.get(),
          &UARTWorkerReceiver::listenForMessages);
  connect(uartWorkerReceiver.get(), &UARTWorkerReceiver::messageReceived, this,
          &Controller::onMessageReceived);
  receiverThread->start();

  // Enable the rest of the frames
  this->view->getCentralPanelWidget()->getConnectButton()->setEnabled(false);
  this->view->getCentralPanelWidget()->getCommandFrame()->setEnabled(true);
  this->view->getCentralPanelWidget()->getMonitoringFrame()->setEnabled(true);
}

void Controller::onCommandSent() {
  // Get the command entered in the text input
  QString command = view->getCentralPanelWidget()->getCommandInput()->text();
  qDebug() << "Sending command: " << command;
  if (!command.isEmpty()) {
    QMetaObject::invokeMethod(uartWorkerSender.get(), "sendCommand",
                              Qt::QueuedConnection, Q_ARG(QString, command));
    view->getCentralPanelWidget()->getCommandInput()->clear();
  }
}

void Controller::onMessageReceived(const QString &message) {
  // Append the received message to the monitoring text edit
  view->getCentralPanelWidget()->getMonitoringTextEdit()->append(message);
}

void Controller::cleanUpThreads() {
  if (uartWorkerReceiver) {
    uartWorkerReceiver->stopListening();  // Ensure the receiver stops listening
    qDebug() << " Stopping the listening.";
  }

  // Stop the worker threads and join them
  if (senderThread && senderThread->isRunning()) {
    senderThread->quit();
    senderThread->wait();
    qDebug() << " Stopping the sender thread.";
  }
  if (receiverThread && receiverThread->isRunning()) {
    receiverThread->quit();
    receiverThread->wait();
    qDebug() << " Stopping the receiver thread.";
  }
}

void Controller::onMainWindowClosing() { cleanUpThreads(); }