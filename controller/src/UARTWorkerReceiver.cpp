#include "UARTWorkerReceiver.hpp"

#include <QDebug>
#include <QThread>
#include <chrono>
#include <thread>

UARTWorkerReceiver::UARTWorkerReceiver(std::shared_ptr<UARTSender> uartSender,
                                       QObject* parent)
    : QObject(parent), uartSender(std::move(uartSender)) {}

UARTWorkerReceiver::~UARTWorkerReceiver() { stopListening(); }

void UARTWorkerReceiver::listenForMessages() {
  std::string accumulatedMessage;

  while (this->isListening) {
    // Receive a chunk from UART
    std::string message = uartSender->receive();
    if (!message.empty()) {
      accumulatedMessage += message;  // Add the new chunk to the buffer
      // Check if the message contains a newline, meaning it's complete
      size_t pos;
      while ((pos = accumulatedMessage.find("\n")) != std::string::npos) {
        // Extract the full message and emit it
        std::string completeMessage = accumulatedMessage.substr(0, pos);
        completeMessage.erase(
            std::remove(completeMessage.begin(), completeMessage.end(), '\n'),
            completeMessage.cend());  // Remove newlines

        accumulatedMessage.erase(
            0, pos + 1);  // Remove the complete message from the buffer

        emit messageReceived(
            QString::fromStdString(completeMessage));  // Emit the full message
      }
    }

    // Sleep briefly to prevent excessive CPU usage
    QThread::msleep(100);
  }
}

void UARTWorkerReceiver::stopListening() {
  this->isListening = false;
}
