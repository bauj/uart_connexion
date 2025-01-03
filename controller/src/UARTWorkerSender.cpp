#include "UARTWorkerSender.hpp"

#include <QDebug>
#include <QThread>

UARTWorkerSender::UARTWorkerSender(std::shared_ptr<UARTSender> uartSender,
                                   QObject* parent)
    : QObject(parent), uartSender(std::move(uartSender)) {}

void UARTWorkerSender::sendCommand(const QString& command) {
  try {
    uartSender->send(command.toStdString());
    emit messageSent(command);
  } catch (const std::exception& e) {
    qInfo() << "Error sending command:" << e.what();
  }
}
