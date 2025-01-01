#include "Controller.hpp"

#include <QMetaObject>

Controller::Controller(MainWindow *view, QObject *parent)
    : QObject(parent), view(view), uartWorker(nullptr) {
  // Connect the send button clicked signal to the controller's slot

  // Connect GUI signals to controller slots
  connect(view->getCentralPanelWidget()->getSendButton(), &QPushButton::clicked,
          this, &Controller::onCommandSent);

  connect(view->getCentralPanelWidget()->getConnectButton(),
          &QPushButton::clicked, this, &Controller::onTTYConnexionMade);
}

Controller::~Controller() {
  // Make sure the thread finishes and is cleaned up
  if (uartThread.isRunning()) {
    uartThread.quit();  // Stop the worker thread's event loop
    uartThread.wait();  // Wait for the worker thread to finish
  }  
  if (uartWorker) {
    uartWorker->deleteLater();  // Ensures that the worker is deleted when the
                                // thread finishes
  }
}

void Controller::onTTYConnexionMade() {
  auto ttyCmbBox = view->getCentralPanelWidget()->getTTYComboBox();
  auto baudRateCmbBox = view->getCentralPanelWidget()->getBaudRateComboBox();
  auto ttyDeviceName = ttyCmbBox->itemText(ttyCmbBox->currentIndex());
  auto ttyBaudRate = baudRateCmbBox->itemText(baudRateCmbBox->currentIndex());

  // Create the worker and move it to the new thread
  uartWorker = std::make_unique<UARTWorker>("/dev/" + ttyDeviceName,
                                            ttyBaudRate.toInt());

  // Move the worker to a new thread
  uartWorker->moveToThread(&uartThread);

  // Connect the finished signal to delete the worker and stop the thread
  connect(uartWorker.get(), &UARTWorker::finished, uartWorker.get(),
          &QObject::deleteLater);

  // Connect finished signal of worker thread to quit the thread
  connect(uartWorker.get(), &UARTWorker::finished, &uartThread, &QThread::quit);
  connect(&uartThread, &QThread::finished, &uartThread, &QThread::deleteLater);

  // Start the worker thread
  uartThread.start();

  // Enable the rest of the frames
  this->view->getCentralPanelWidget()->getCommandFrame()->setEnabled(true);
  this->view->getCentralPanelWidget()->getMonitoringFrame()->setEnabled(true);
}

void Controller::onCommandSent() {
  // Get the command entered in the text input
  QString command = view->getCentralPanelWidget()->getCommandInput()->text();
  qInfo() << "Sending command: " << command;
  if (uartWorker) {
    // Send the command to the worker via the sendCommand slot
    QMetaObject::invokeMethod(uartWorker.get(), "sendCommand",
                              Qt::QueuedConnection, Q_ARG(QString, command));
  }
}
