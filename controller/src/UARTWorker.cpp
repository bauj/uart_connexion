#include "UARTWorker.hpp"

#include <QDebug>
#include <QThread>

UARTWorker::UARTWorker(const QString &device, int baudRate, QObject *parent)
    : QObject(parent), uartSender(device.toStdString(), baudRate) {}

UARTWorker::~UARTWorker() { qInfo() << "UARTWorker is being destroyed"; }

void UARTWorker::sendCommand(const QString &command) {
  // Sending the command through UART
  uartSender.send(command.toStdString());
  emit messageSent("Sent: " + command);
}

void UARTWorker::start() {
  // This could be a continuous operation (if needed), such as listening for
  // incoming data For now, it just keeps the thread alive
  qInfo() << "UARTWorker started";
  emit messageSent("Worker started.");
}
